/*
  Project: iPhone OpenGL ES Water Effect like Koi-Pond
  Date: 7-Jul-2008
  Author: zveriu (zveriu@gmail.com, http://andreicostin.com)
  License: GPL v3 (
  Notes: Please keep and reference these comments and notes. Original framework
         of the application is from DSAqua
*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include <time.h>



// OPENGL stuff

/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glut.h>
*/
#include <GLES/gl.h>

/*
#ifdef XMESA
#include "GL/xmesa.h"
#endif
*/


// custom objects



/////////////////////////////////////////////////
// fluid object definition                     //
/////////////////////////////////////////////////

#include "flotte.h"



//-----------------------------------
// constructor
//
// define aSize X aSize columns of
// fluid
//-----------------------------------

dmFlotte::dmFlotte(int rez)
{

   // allocate texture (3/4 RBBA components)

   _TexBuff[0] = new GLubyte[TEX_WIDTH1*TEX_HEIGHT1*TEX_COMP1];
   _TexBuff[1] = new GLubyte[TEX_WIDTH2*TEX_HEIGHT2*TEX_COMP2];


   _texwidth[0]  = TEX_WIDTH1;
   _texheight[0] = TEX_HEIGHT1;

   _texwidth[1]  = TEX_WIDTH2;
   _texheight[1] = TEX_HEIGHT2;


   // initialize some fields

   _angle = 0;


   // initial conditions

   _p1 = &_Flot1; // FRONT MAP
   _p2 = &_Flot2; // BACK MAP

   dmFlotte::init_Flot();

   // by default high tesselation

   //_lowtesselation = false;
   //_hightesselation = true;

    // andreico
   _lowtesselation = true;
   _hightesselation = false;

   if (rez == FLOT_MEDIUMRES)
     _hightesselation = false;
   else if (rez == FLOT_LOWRES)
     _lowtesselation = true;


   // prebuild geometric model

   dmFlotte::_prebuild_Flot();

   // read textures files ...

   // DS improve datas
	enableEnv = false;
    image = new M3D::ImageTGA ();
    texture_bg = image->loadTexture ("/data/mobile3d/androidgldemos/water/rocks.tga");
	if (enableEnv)
    	texture_env = image->loadTexture ("/data/mobile3d/androidgldemos/water/env.tga");

	model = new M3D::Model ();
	model->setMeshCount (1);
	model->setRenderPrimitivesMode (GL_TRIANGLE_STRIP, 0);



   _textured = TRUE;


   // by default multitextured
   _multitex = false;
   //_multitex = true;
   _freezemultitex = false;



   // current clock
   _last_msTime = ( (clock() * 1000) / CLOCKS_PER_SEC ) - 100.0f;
   _cur_msTime = _last_msTime + 100.0f;

}

//-----------------------------------
// destructor
//-----------------------------------

dmFlotte::~dmFlotte(void)
{

   if (_textured)
   {
       GLuint deltex[] = {1,2};
       glDeleteTextures(2, deltex);  // delete textures ...
   }

   if (_TexBuff[0])
   {
      delete[] _TexBuff[0];
   }

   if (_TexBuff[1])
   {
      delete[] _TexBuff[1];
   }

	if (texture_bg)
		FREEANDNULL (texture_bg);

	if (texture_env)
		FREEANDNULL (texture_env);

	if (model)
		FREEANDNULL (model);
}



//-----------------------------------
// initial conditions : every heights
// at zero
//-----------------------------------

void dmFlotte::init_Flot(void)
{
    memset((unsigned char*)(*_p1), 0, sizeof(int)*(FLOTSIZE+2)*(FLOTSIZE+2));
    memset((unsigned char*)(*_p2), 0, sizeof(int)*(FLOTSIZE+2)*(FLOTSIZE+2));
}

//-----------------------------------
// trace a hole at normalized
// coordinates
//-----------------------------------

//aVal for amplitude
void dmFlotte::setWave(float aX, float aY, int aVal)
{
    int x = FLOT_MILX + (int)(2.0f*(aX - 0.5f)*FLOT_LARG);
    int y = FLOT_MILY + (int)(2.0f*(aY - 0.5f)*FLOT_LARG);

    // check periodicity
    while (x > FLOTSIZE)  x -= FLOTSIZE;
    while (y > FLOTSIZE)  y -= FLOTSIZE;
    while (x < 0) x += FLOTSIZE;
    while (y < 0) y += FLOTSIZE;


    (*_p1)[x][y] -= aVal;
}

//-----------------------------------
// trace a hole following parametric
// curves
//-----------------------------------

void dmFlotte::runWave(float aPhase, float aCos, float aSin, int aVal)
{
    float r = (_angle*M_PI)/1024.0f;

    int x = FLOT_MILX + ((int) (cos(aCos*r + aPhase)*FLOT_LARG));
    int y = FLOT_MILY + ((int) (sin(aSin*r + aPhase)*FLOT_LARG));

    if (x > FLOTSIZE)  x = FLOTSIZE;
    if (y > FLOTSIZE)  y = FLOTSIZE;
    if (x < 0) x = 0;
    if (y < 0) y = 0;


    (*_p1)[x][y] -= aVal;
}

//-----------------------------------
// trace a random hole
//-------------------------------

void dmFlotte::randomWave(void)
{
    (*_p1)[random()%FLOTSIZE+1][random()%FLOTSIZE+1] -= random()%128;
}


//-----------------------------------
// measure elapsed time ...
//-----------------------------------
bool dmFlotte::bench(float rate)
{
    _cur_msTime = (clock() * 1000) / CLOCKS_PER_SEC;

    // don't run to quick otherwise it doesn't look like water
    return (_cur_msTime - _last_msTime) >= rate;
}

void dmFlotte::nexttime(void)
{
    _last_msTime = _cur_msTime;
}

//-----------------------------------
// update to next state of fluid
// model
//-----------------------------------

void dmFlotte::update(void)
{

    // new angle for parametric curves
    _angle = (_angle+2) & 1023;


    // fluid update
    dmFlotte::_new_Flot();

    // smoothing
    dmFlotte::_Lisse_Flot();

}

//----------------------------------------
// build geometric model
//----------------------------------------

void dmFlotte::build(void)
{

    dmFlotte::_build_Flot();
}

//----------------------------------------
// physical calculus for fluid model
//----------------------------------------


void dmFlotte::_new_Flot(void)
{

     register int x,y, step;
     register int *ptr;
     int (*q)[FLOTSIZE+2][FLOTSIZE+2];


     // discretized differential equation

     for(x=1; x<=FLOTSIZE; x++)
     {
        for(y=0; y<=FLOTSIZE; y ++)
        {
           (*_p1)[x][y] = (((*_p2)[x-1][y]+(*_p2)[x+1][y]+(*_p2)[x][y-1]+(*_p2)[x][y+1]) >> 1) - (*_p1)[x][y];
           (*_p1)[x][y] -= (*_p1)[x][y] >> 4;
        }
     }


     // copy borders to make the map periodic


     memcpy(&((*_p1)[0][0]), &((*_p1)[1][0]), sizeof(int)*(FLOTSIZE+2));
     memcpy(&((*_p1)[FLOTSIZE+1][0]), &((*_p1)[1][0]), sizeof(int)*(FLOTSIZE+2));

     step = (FLOTSIZE+2);

     for(x=0, ptr = &((*_p1)[0][0]); x<(FLOTSIZE+1); x++, ptr += step)
     {
        ptr[0] = ptr[1];
        ptr[FLOTSIZE+1] = ptr[1];
     }

     /* swap buffers t and t-1, we advance in time */


     q=_p1;
     _p1=_p2;
     _p2=q;


}



//----------------------------------------
// filter and smooth producted values
//----------------------------------------


void dmFlotte::_Lisse_Flot(void)
{
     register int x,y,i;


     for(x=1; x<FLOTSIZE+1; x++)
     {
        for(y=1; y<FLOTSIZE+1; y++)
        {
           _Lisse[x][y] = (3*(*_p1)[x][y]+2*(*_p1)[x+1][y]+2*(*_p1)[x][y+1]+(*_p1)[x+1][y+1]) >> 3;
        }
     }


     for(i=1; i<4; i++)
     {
       for(x=1; x<FLOTSIZE+1; x++)
       {
          for(y=1; y<FLOTSIZE+1; y++)
          {
             _Lisse[x][y] = (3*_Lisse[x][y]+2*_Lisse[x+1][y]+2*_Lisse[x][y+1]+_Lisse[x+1][y+1]) >> 3;
          }
       }
     }


}


//------------------------------------------
// pre-building of a geometric model
//------------------------------------------

void dmFlotte::_prebuild_Flot(void)
{
     register float h1,xmin,ymin;
     register int x,y;

   {
        /* vertices calculus -> we already know X and Y */
        /* calculus of background texture coordinates */

        for(x=1; x<=FLOTSIZE; x++)
        {
           xmin = (x-FLOT_MILX)/6.5f;

           for(y=1; y<=FLOTSIZE; y++)
           {
              ymin = (y-FLOT_MILY)/7.5f;

              _sommet[x-1][y-1][0] = xmin;
              _sommet[x-1][y-1][1] = ymin;

              _uvmap[x-1][y-1][0] = (x-1)*(1.0f/(FLOTSIZE-1));
              _uvmap[x-1][y-1][1] = (y-1)*(1.0f/(FLOTSIZE-1));
           }

        }


        /* nomals to faces calculus : Z component is constant */

        // -> simplified cross product and optimized knowing that we have
        //    a distance of 1.0 between each fluid cells.

        for(x=0; x < FLOTSIZE-1; x++)
        {
           for(y=0; y < FLOTSIZE-1; y++)
           {
              _normal[x][y][2] = 0.01f;
           }
        }


        //..............................................................................................................
        //
        // the following calculus is useless because each cell of _snormal[x][y][2] = 0.01+0.01+0.01+0.01 = 0.04
        //..............................................................................................................


        /* copy borders of the map (Z component only) for periodicity */

        memcpy((char*) &_normal[FLOTSIZE-1][0][0], (char*) &_normal[FLOTSIZE-2][0][0], 3*sizeof(float)*FLOTSIZE);

        for(x=0; x < FLOTSIZE; x++)
        {
           _normal[x][FLOTSIZE-1][2] = _normal[x][FLOTSIZE-2][2];
        }


        /* calculate normals to vertices (Z component only)*/

        for(x=1; x < FLOTSIZE-1; x++)
        {
           for(y=1; y < FLOTSIZE-1; y++)
           {
              _snormal[x][y][2] = _normal[x-1][y][2]+_normal[x+1][y][2]+_normal[x][y-1][2]+_normal[x][y+1][2];
           }
        }


        /* copy borders of the map (Z component only) for periodicity */

        for(x=0; x < FLOTSIZE; x++)
        {
           _snormal[x][0][2] = _normal[x][0][2];
           _snormal[x][FLOTSIZE-1][2] = _normal[x][FLOTSIZE-1][2];
        }

        memcpy((char*) &_snormal[0][0][0], (char*) &_normal[0][0][0], 3*sizeof(float)*FLOTSIZE);
        memcpy((char*) &_snormal[FLOTSIZE-1][0][0], (char*) &_normal[FLOTSIZE-1][0][0], 3*sizeof(float)*FLOTSIZE);

   } // end lowtesselation
}

//----------------------------------------
// construction of a geometric model
//----------------------------------------

void dmFlotte::_build_Flot(void)
{
     register float h1,sqroot;
     register int x,y;

     float L[3], V[3], R[3], RV[3], ls, lz, radius, dotprod;

   {

        /* calculate vertices : Z component */

        for(x=1; x<=FLOTSIZE; x++)
        {
           for(y=1; y<=FLOTSIZE; y++)
           {
              if ( (h1 = (_Lisse[x][y] / 100.0f)) < 0.0f)
              {
                 h1 = 0.0f;
              }

              _sommet[x-1][y-1][2] = h1;
           }
        }


        /* calculate normals to faces : components X and Y */

        // -> simplified cross product knowing that we have a distance of 1.0 between
        //    each fluid cells.

        for(x=0; x < FLOTSIZE-1; x++)
        {
           for(y=0; y < FLOTSIZE-1; y++)
           {
              _normal[x][y][0] = 0.1f*(_sommet[x][y][2]-_sommet[x+1][y][2]);
              _normal[x][y][1] = 0.1f*(_sommet[x][y][2]-_sommet[x][y+1][2]);
           }
        }


        /* copy map borders(components X and Y only) for periodicity */

        memcpy((char*) &_normal[FLOTSIZE-1][0][0], (char*) &_normal[FLOTSIZE-2][0][0], 3*sizeof(float)*FLOTSIZE);

        for(x=0; x < FLOTSIZE; x++)
        {
           _normal[x][FLOTSIZE-1][0] = _normal[x][FLOTSIZE-2][0];
           _normal[x][FLOTSIZE-1][1] = _normal[x][FLOTSIZE-2][1];
        }


        /* calculate normals to vertices (components X and Y only) */

        for(x=1; x < FLOTSIZE-1; x++)
        {
           for(y=1; y < FLOTSIZE-1; y++)
           {
              _snormal[x][y][0] = _normal[x-1][y][0]+_normal[x+1][y][0]+_normal[x][y-1][0]+_normal[x][y+1][0];
              _snormal[x][y][1] = _normal[x-1][y][1]+_normal[x+1][y][1]+_normal[x][y-1][1]+_normal[x][y+1][1];
           }
        }


        /* copy map borders (components X and Y only) */

        for(x=0; x < FLOTSIZE; x++)
        {
           _snormal[x][0][0] = _normal[x][0][0];
           _snormal[x][0][1] = _normal[x][0][1];
           _snormal[x][FLOTSIZE-1][0] = _normal[x][FLOTSIZE-1][0];
           _snormal[x][FLOTSIZE-1][1] = _normal[x][FLOTSIZE-1][1];
        }

        memcpy((char*) &_snormal[0][0][0], (char*) &_normal[0][0][0], 3*sizeof(float)*FLOTSIZE);
        memcpy((char*) &_snormal[FLOTSIZE-1][0][0], (char*) &_normal[FLOTSIZE-1][0][0], 3*sizeof(float)*FLOTSIZE);


        /* calculate ourself normalization */

        for(x=0; x < FLOTSIZE; x++)
        {
           for(y=0; y < FLOTSIZE; y++)
           {


              sqroot = sqrt(_snormal[x][y][0]*_snormal[x][y][0] +
                            _snormal[x][y][1]*_snormal[x][y][1] +
                            0.0016f);


              _snormaln[x][y][0] = _snormal[x][y][0]/sqroot;
              _snormaln[x][y][1] = _snormal[x][y][1]/sqroot;
              _snormaln[x][y][2] = 0.04f/sqroot;             // _snormal[x][y][2] = 0.04


              // perturbate coordinates of background mapping with the components X,Y of normals...
              // simulate refraction

              _newuvmap[x][y][0] = _uvmap[x][y][0] + 0.05f*_snormaln[x][y][0];
              _newuvmap[x][y][1] = _uvmap[x][y][1] + 0.05f*_snormaln[x][y][1];

           }
        }



        // really simple version of a fake envmap generator

        for(x=0; x < FLOTSIZE; x++)
        {
           for(y=0; y < FLOTSIZE; y++)
           {
              // trick : xy projection of normals  ->  assume reflection in direction of the normals
              //                                       looks ok for non-plane surfaces
              _envmap[x][y][0] = 0.5f + _snormaln[x][y][0]*0.45f;
              _envmap[x][y][1] = 0.5f + _snormaln[x][y][1]*0.45f;

           }
        }


   } // end low tesselation

}







//----------------------------------------
// display geometric model
//----------------------------------------

void dmFlotte::display(void)
{
	int strip_width;


   	if (_hightesselation)
   	{
		strip_width = FLOTSIZE*2-1-1;
   	}
   	else
   	{
    	strip_width = FLOTSIZE-1-1;
   	}

	// 2 pass rendering - 1 texture/pass (2 times polygons)

    register int x,y;


    // build triangle strips ...

    float myTex[100][2] = {0.0f, 0.0f};
    float myVer[100][3] = {0.0f, 0.0f, 0.0f};

	if (_lowtesselation)
    {
		//printf("strip_width: %d\n", strip_width);
    	if (texture_bg != NULL)
        	model->setTextureId (texture_bg->textureId, 0);


        for(x=0; x<strip_width; x+=2)
        {
            int i = 0;

            //printf("x : %d\n", x);
            //glBegin(GL_TRIANGLE_STRIP);

            //glTexCoord2fv(_newuvmap[x+2][2]);          // WARNING: glTexCoord2fv BEFORE glVertex !!!
            //glVertex3fv(_sommet[x+2][2]);              // otherwise everything is scrolled !!!

            //printf("_newuvmap[x+2][2] : %f %f %f\n", _newuvmap[x+2][2][0], _newuvmap[x+2][2][1], _newuvmap[x+2][2][2]);
            //printf("_sommet[x+2][2] : %f %f %f\n", _sommet[x+2][2][0], _sommet[x+2][2][1], _sommet[x+2][2][2]);
            i++;

            //glVertexPointer(3, GL_FLOAT, 0, _sommet[x+2][2]);
            //glTexCoordPointer(2, GL_FLOAT, 0, _newuvmap[x+2][2]);
            //glVertexPointer(3, GL_FLOAT, 0, _sommet[x+2][2]);
            //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            myTex[i-1][0] = _newuvmap[x+2][2][0];
            myTex[i-1][1] = _newuvmap[x+2][2][1];
            myVer[i-1][0] = _sommet[x+2][2][0];
            myVer[i-1][1] = _sommet[x+2][2][1];
            myVer[i-1][2] = _sommet[x+2][2][2];

            for(y=2; y<strip_width; y+=2)
            {
                //printf("y : %d\n", y);

                //glTexCoord2fv(_newuvmap[x][y]);
                //glVertex3fv(_sommet[x][y]);

                //printf("_newuvmap[x][y] : %f %f %f\n", _newuvmap[x][y][0], _newuvmap[x][y][1], _newuvmap[x][y][2]);
                //printf("_sommet[x][y] : %f %f %f\n", _sommet[x][y][0], _sommet[x][y][1], _sommet[x][y][2]);
                i++;

                //glVertexPointer(3, GL_FLOAT, 0, _sommet[x][y]);
                //glTexCoordPointer(2, GL_FLOAT, 0, _newuvmap[x][y]);
                //glVertexPointer(3, GL_FLOAT, 0, _sommet[x][y]);
                //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

                myTex[i-1][0] = _newuvmap[x][y][0];
                myTex[i-1][1] = _newuvmap[x][y][1];
                myVer[i-1][0] = _sommet[x][y][0];
                myVer[i-1][1] = _sommet[x][y][1];
                myVer[i-1][2] = _sommet[x][y][2];

                //glTexCoord2fv(_newuvmap[x+2][y+2]);
                //glVertex3fv(_sommet[x+2][y+2]);

                //printf("_newuvmap[x+2][y+2] : %f %f %f\n", _newuvmap[x+2][y+2][0], _newuvmap[x+2][y+2][1], _newuvmap[x+2][y+2][2]);
                //printf("_sommet[x+2][y+2] : %f %f %f\n", _sommet[x+2][y+2][0], _sommet[x+2][y+2][1], _sommet[x+2][y+2][2]);
                i++;

                //glVertexPointer(3, GL_FLOAT, 0, _sommet[x+2][y+2]);
                //glTexCoordPointer(2, GL_FLOAT, 0, _newuvmap[x+2][y+2]);
                //glVertexPointer(3, GL_FLOAT, 0, _sommet[x+2][y+2]);
                //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

                myTex[i-1][0] = _newuvmap[x+2][y+2][0];
                myTex[i-1][1] = _newuvmap[x+2][y+2][1];
                myVer[i-1][0] = _sommet[x+2][y+2][0];
                myVer[i-1][1] = _sommet[x+2][y+2][1];
                myVer[i-1][2] = _sommet[x+2][y+2][2];

            }

            //glTexCoord2fv(_newuvmap[x][y]);
            //glVertex3fv(_sommet[x][y]);

            //printf("_newuvmap[x][y] : %f %f %f\n", _newuvmap[x][y][0], _newuvmap[x][y][1], _newuvmap[x][y][2]);
            //printf("_sommet[x][y] : %f %f %f\n", _sommet[x][y][0], _sommet[x][y][1], _sommet[x][y][2]);
            i++;


/*LP
            //glVertexPointer(3, GL_FLOAT, 0, _sommet[x][y]);
            glTexCoordPointer(2, GL_FLOAT, 0, _newuvmap[x][y]);
            glVertexPointer(3, GL_FLOAT, 0, _sommet[x][y]);
            //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
*/
            myTex[i-1][0] =  _newuvmap[x][y][0];
            myTex[i-1][1] = _newuvmap[x][y][1];
            myVer[i-1][0] = _sommet[x][y][0];
            myVer[i-1][1] = _sommet[x][y][1];
            myVer[i-1][2] = _sommet[x][y][2];


    		model->setVertices(&myVer[0][0], i * 3 * sizeof(GLfloat), 0);
    		model->setUvs(&myTex[0][0], i * 2 * sizeof (GLfloat), 0);
    		model->setTriangleNums(i / 3, 0);
			model->renderModel ();


           //printf("Vertices : i %d formula %d\n", i, 1 + 1 + (strip_width - 2 - 1)/2);
        }
    } // end of _lowtesselation


     // change Z-buffer function to EQUAL
     // so it will trace second geometry on the same layer (and avoid tracing if some
     // objects are before ...
    if (_lowtesselation && enableEnv)
    {

    	if (texture_env != NULL)
        	model->setTextureId (texture_env->textureId, 0);


        for(x=0; x<strip_width; x+=2)
        {
            int i = 0;

            //printf("x : %d\n", x);
            //glBegin(GL_TRIANGLE_STRIP);

            //glTexCoord2fv(_envmap[x+2][2]);
            //glVertex3fv(_sommet[x+2][2]);                               // otherwise everything is scrolled !!!

            //printf("_envmap[x+2][2] : %f %f %f\n", _envmap[x+2][2][0], _envmap[x+2][2][1], _envmap[x+2][2][2]);
            //printf("_sommet[x+2][2] : %f %f %f\n", _sommet[x+2][2][0], _sommet[x+2][2][1], _sommet[x+2][2][2]);
            i++;

            //glVertexPointer(3, GL_FLOAT, 0, _sommet[x+2][2]);
            //glTexCoordPointer(2, GL_FLOAT, 0, _envmap[x+2][2]);
            //glVertexPointer(3, GL_FLOAT, 0, _sommet[x+2][2]);
            //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            myTex[i-1][0] = _envmap[x+2][2][0];
            myTex[i-1][1] = _envmap[x+2][2][1];
            myVer[i-1][0] = _sommet[x+2][2][0];
            myVer[i-1][1] = _sommet[x+2][2][1];
            myVer[i-1][2] = _sommet[x+2][2][2];

            for(y=2; y<strip_width; y+=2)
            {
                //printf("y : %d\n", y);

                //glTexCoord2fv(_envmap[x][y]);
                //glVertex3fv(_sommet[x][y]);

                //printf("_envmap[x][y] : %f %f %f\n", _envmap[x][y][0], _envmap[x][y][1], _envmap[x][y][2]);
                //printf("_sommet[x][y] : %f %f %f\n", _sommet[x][y][0], _sommet[x][y][1], _sommet[x][y][2]);
                i++;

                //glVertexPointer(3, GL_FLOAT, 0, _sommet[x][y]);
                //glTexCoordPointer(2, GL_FLOAT, 0, _envmap[x][y]);
                //glVertexPointer(3, GL_FLOAT, 0, _sommet[x][y]);
                //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

                myTex[i-1][0] = _envmap[x][y][0];
                myTex[i-1][1] = _envmap[x][y][1];
                myVer[i-1][0] = _sommet[x][y][0];
                myVer[i-1][1] = _sommet[x][y][1];
                myVer[i-1][2] = _sommet[x][y][2];

                //glTexCoord2fv(_envmap[x+2][y+2]);
                //glVertex3fv(_sommet[x+2][y+2]);

                //printf("_envmap[x+2][y+2] : %f %f %f\n", _envmap[x+2][y+2][0], _envmap[x+2][y+2][1], _envmap[x+2][y+2][2]);
                //printf("_sommet[x+2][y+2] : %f %f %f\n", _sommet[x+2][y+2][0], _sommet[x+2][y+2][1], _sommet[x+2][y+2][2]);
                i++;

                //glVertexPointer(3, GL_FLOAT, 0, _sommet[x+2][y+2]);
                //glTexCoordPointer(2, GL_FLOAT, 0, _envmap[x+2][y+2]);
                //glVertexPointer(3, GL_FLOAT, 0, _sommet[x+2][y+2]);
                //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

                myTex[i-1][0] = _envmap[x+2][y+2][0];
                myTex[i-1][1] = _envmap[x+2][y+2][1];
                myVer[i-1][0] = _sommet[x+2][y+2][0];
                myVer[i-1][1] = _sommet[x+2][y+2][1];
                myVer[i-1][2] = _sommet[x+2][y+2][2];
            }

            //glTexCoord2fv(_envmap[x][y]);
            //glVertex3fv(_sommet[x][y]);

            //printf("_envmap[x][y] : %f %f %f\n", _envmap[x][y][0], _envmap[x][y][1], _envmap[x][y][2]);
            //printf("_sommet[x][y] : %f %f %f\n", _sommet[x][y][0], _sommet[x][y][1], _sommet[x][y][2]);
            i++;
            myTex[i-1][0] = _envmap[x][y][0];
            myTex[i-1][1] = _envmap[x][y][1];
            myVer[i-1][0] = _sommet[x][y][0];
            myVer[i-1][1] = _sommet[x][y][1];
            myVer[i-1][2] = _sommet[x][y][2];

			model->enableBlend (true, 0);
    		model->setVertices(&myVer[0][0], i * 3 * sizeof(GLfloat), 0);
    		model->setUvs(&myTex[0][0], i * 2 * sizeof (GLfloat), 0);
			model->setBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, 0);
			model->renderModel ();



            //printf("Vertices : i %d formula %d\n", i, 1 + 1 + (strip_width - 2 - 1)/2);
        }
    }

}


//--------------------------------------------
// load a texture TEW_WIDTH*TEX_HEIGHT*3
//--------------------------------------------

void dmFlotte::_load_tex (int num, char *aName)
{

	TGA tga;
	GLuint      Bpp;
    FILE * fTGA;                                                    /* File pointer to texture file */
	int nbcomp;
	int i,j;
	GLubyte tmp;

    if (num == 0)
    {
       nbcomp = TEX_COMP1;
    }
    else if (num == 1)
    {
       nbcomp = TEX_COMP2;
    }


    fTGA = fopen(aName, "rb");                                   	/* Open file for reading */
    if(fTGA == NULL)                                                /* If it didn't open.... */
    {
        printf("Error could not open texture file");                /* Display an error message */
        return ;                                               /* Exit function */
    }  

    if(fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)             /* Read TGA header */
    {
        printf("Error could not read info header");                         /* Display error */
        if(fTGA != NULL)                                                    /* if file is still open */
        {
            fclose(fTGA);                                                   /* Close it */
        }
        return;                                                       /* Return failular */
    }

	if (fread (_TexBuff[num], 1, nbcomp*_texwidth[num]*_texheight[num], fTGA) == -1) {
		
        fclose(fTGA);                                                       /* Close file */
        return;                                                       		/* Return failed */

	}


     // swap BGR and RGB, BGRA and RGBA

    for(i=0; i<_texwidth[num]*_texheight[num]; i++)
    {

       for(j=0; j < (3 >> 1); j++)
       {
          tmp = (_TexBuff[num])[i*nbcomp+j];
          (_TexBuff[num])[i*nbcomp+j] = (_TexBuff[num])[i*nbcomp+3-1-j];
          (_TexBuff[num])[i*nbcomp+3-1-j] = tmp;
       }
    }

	fclose (fTGA);

}

//--------------------------------------------
// TEW_WIDTH*TEX_HEIGHT*3 to 256x256*3
//
// crappy downsampling used for
// Voodoo1/Voodoo2 compatibility (can't use
// texture with a definition higher than
// 256x256)
//--------------------------------------------


void dmFlotte::_reduce_tex(int num, GLubyte *map)   // downgrade to 256x256
{
   if (map)
   {
      int sizeX = _texwidth[num];
      int sizeY = _texheight[num];

      GLubyte *newmap = new GLubyte[((sizeX*sizeY) >> 2) * TEX_COMP2 * sizeof(GLubyte)];
      GLubyte *ptmap;

      int i,j,ki, kj;
      unsigned int rgb[3];

      for(ptmap = newmap, i=0; i < (sizeX >> 2); i++)
      {
        for(j=0; j < (sizeY >> 2); j++)
        {
           rgb[0] = 0; rgb[1] = 0; rgb[2] = 0;

           for(ki = (i << 2); ki < (i << 2)+4; ki++)
           {
             for(kj = (j << 2); kj < (j << 2)+4; kj++)
             {

                rgb[0] += map[ki*sizeX*TEX_COMP2 + kj*TEX_COMP2];
                rgb[1] += map[ki*sizeX*TEX_COMP2 + kj*TEX_COMP2 + 1];
                rgb[2] += map[ki*sizeX*TEX_COMP2 + kj*TEX_COMP2 + 2];
             }
           }

           // average
           *ptmap++ = (rgb[0] >> 4);
           *ptmap++ = (rgb[1] >> 4);
           *ptmap++ = (rgb[2] >> 4);

        }
      }


      memcpy(map, newmap, ((sizeX*sizeY) >> 2) * TEX_COMP2 * sizeof(GLubyte));

      delete[] newmap;
   }
}
