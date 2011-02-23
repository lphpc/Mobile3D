
#include "model.h"
#include "log.h"
#include "M3DRenderer.h"

M3D_BEGIN_NAMESPACE


M3DRenderer::M3DRenderer ()
{
}

M3DRenderer::~M3DRenderer ()
{
}



void M3DRenderer::render(const M3DRenderObject *ob) 
{

/*
	if (!mesh->isEnabled ())
    	return;
*/
    glPushMatrix();



    //enable or disable gl command status
	if (ob->m_blendEnabled) {
		glDisable(GL_DEPTH_TEST);
      	glBlendFunc(ob->m_blendSFactor, ob->m_blendDFactor);
      	glEnable(GL_BLEND);

	}
	else {
     	//glDepthMask(GL_TRUE);
      	//glDepthFunc(GL_LESS);
      	glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
	}



/*
	//use matrix
	if (m_matrix != NULL) 
		glMultMatrixf (m_matrix);

*/
    if (ob->m_position != NULL) {
        glTranslatef(ob->m_position[0], ob->m_position[1], ob->m_position[2]);
    }


    if (ob->m_rotate != NULL) {
        //ratate x axis
        if (ob->m_rotate[0] != 0.0f)
             glRotatef(ob->m_rotate[0], 1.0f, 0.0f, 0.0f);
        //ratate y axis
        if (ob->m_rotate[1] != 0.0f)
             glRotatef(ob->m_rotate[1], 0.0f, 1.0f, 0.0f);
        //ratate z axis
        if (ob->m_rotate[2] != 0.0f)
           	glRotatef(ob->m_rotate[2], 0.0f, 0.0f, 1.0f);
    }

    if (ob->m_scale != NULL)
       	glScalef(ob->m_scale[0], ob->m_scale[1], ob->m_scale[2]);


    if (ob->m_vertices != NULL){
        glEnableClientState(GL_VERTEX_ARRAY);
       	glVertexPointer(3, GL_FLOAT, 0, ob->m_vertices);
	}
    else 
       	return;
      
 
    if (ob->m_normals != NULL) {
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, 0, ob->m_normals);
	}

    if (ob->m_uvs != NULL && ob->m_textureId != -1) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ob->m_textureId);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 0, ob->m_uvs);
    } else {
        glDisable(GL_TEXTURE_2D);
        if ((ob->m_uvs != NULL && ob->m_textureId == -1) ||
            (ob->m_uvs == NULL && ob->m_textureId != -1) ) {
			printf("Only have uvs or texture id!\n");
        }
    }


    if (ob->m_colors != NULL) {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, ob->m_colors);
	}



    //Add for light/material
    if (ob->m_materialAmbient != NULL) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ob->m_materialAmbient);

        _M3D_PRINTF ("ambient: r = %g, g = %g, b = %g.\n", ob->m_materialAmbient[0], 
					ob->m_materialAmbient[1], ob->m_materialAmbient[2]);

    }

    if (ob->m_materialDiffuse != NULL){
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ob->m_materialDiffuse);
        _M3D_PRINTF ("diffuse: r = %g, g = %g, b = %g.\n", ob->m_materialDiffuse[0], 
					ob->m_materialDiffuse[1], ob->m_materialDiffuse[2]);

    }

    if (ob->m_materialSpecular != NULL) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ob->m_materialSpecular);
      	_M3D_PRINTF ("specular: r = %g, g = %g, b = %g.\n", ob->m_materialSpecular[0], 
					ob->m_materialSpecular[1], ob->m_materialSpecular[2]);

    }


    if (ob->m_materialEmission != NULL) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ob->m_materialEmission);

      _M3D_PRINTF ("emission: r = %g, g = %g, b = %g.\n", ob->m_materialEmission[0], 
					ob->m_materialEmission[1], ob->m_materialEmission[2]);

	}


    if (ob->m_materialShininess != NULL) {
        glMaterialfv (GL_FRONT_AND_BACK, GL_SHININESS, ob->m_materialShininess);
      	_M3D_PRINTF ("shininess: s = %g.\n", ob->m_materialShininess[0]);

    }
    //dump indices
/*
    if (m_indices != NULL){
    	for (int i = 0; i < m_triangleNums * 3; i++) {
        	_M3D_PRINTF ("indices[%d] = %d. \n", i, m_indices[i]);
    	}
	}

    //dump vertices
    for (int i = 0; i < 6 * 3; i++) {
        _M3D_PRINTF ("m_vertices[%d] = %g. \n", i, m_vertices[i]);
    }

*/



	//GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES
	GLenum primitivesType;
	switch (ob->m_primType) {
		case M3DRenderObject::PT_TRIANGLES:
			primitivesType = GL_TRIANGLES;
			break;
	}
	

    //end light/material

    if (ob->m_useIndex){
        glDrawElements(primitivesType, ob->m_indexCount, GL_UNSIGNED_SHORT, ob->m_indices);
        //glDrawElements(GL_TRIANGLES, triangleNum * 3, GL_UNSIGNED_SHORT, mesh->getIndices());
	}
    else {
        glDrawArrays(primitivesType, 0, ob->m_vertexCount);
        //glDrawArrays(GL_TRIANGLES, 0, triangleNum * 3);
	}

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    //restore matrix
    glPopMatrix();


    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );


}






M3D_END_NAMESPACE
