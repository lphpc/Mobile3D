

#include "model_am.h"


M3D_BEGIN_NAMESPACE

/**
 * ModelMD2 class for all games using M3D.
 */

ModelAM::ModelAM()
{
}

ModelAM::~ModelAM() {

}


void ModelAM::renderModel() {

    for (int i = 0; i < m_meshCount; i++) {
        m_meshs[i].renderMesh();
	}
}


void ModelAM::loadModel (const char* filename)
{
    FILE *file;
    int r, i, j;
    int version = 0;
    int mesh_num = 0;
    int vertex_num = 0;
    int uv_num = 0;
    int triangle_num = 0;
    int temp = 0;
    float t1, t2, t3;
    int material_num = 0;
    float specular_level, glossiness;


    char mesh_name[32];
    float box;
	float *vertices = NULL;
	float *uvs = NULL;
	short *indices = NULL;


    printf ("loadModel %s.\n", filename);

    file = fopen (filename, "r");
    if (file == NULL)
        return;


    r = fscanf (file, "SimpleMeshFormat %d\n", &version);
    printf ("verson = %d.\n", version);

    r = fscanf (file, "%d\n", &mesh_num);
    printf ("mesh_num = %d.\n", mesh_num);
	setMeshCount (mesh_num);


    for (i = 0; i < mesh_num; i++) {

        r = fscanf (file, "%s\n", mesh_name);
        printf ("mesh_name = %s.\n", mesh_name);

        r = fscanf (file, "%d\n", &vertex_num);
        printf ("vertex_num = %d.\n", vertex_num);

        vertices = (float*)malloc (vertex_num * 3 * sizeof (float));
        if (!vertices) {
            //Fixme: free sth if needed.
            return;
        }

        for (j = 0; j < vertex_num; j++)  {
            r = fscanf (file, "%g %g %g\n",
                            &vertices[j*3],
                            &vertices[j*3+1],
                            &vertices[j*3+2]);
            /*printf ("mesh[%d]->vertex[%d] = %g %g %g.\n", i, j,
                            m_model.meshes[i].vertices[j].vertex[0],
                            m_model.meshes[i].vertices[j].vertex[1],
                            m_model.meshes[i].vertices[j].vertex[2]);*/
        }

		
        setVertices (vertices, vertex_num * 3 * sizeof (float), i);
        FREEANDNULL (vertices);

        r = fscanf (file, "%d\n", &uv_num);
	
        uvs = (float*)malloc (uv_num * 2 * sizeof (float));

        for (j = 0; j < uv_num; j++)  {
            r = fscanf (file, "%g %g\n",
                            &uvs[j*2],
                            &uvs[j*2+1]);
        }

        setUvs(uvs, uv_num * 2 * sizeof (float), i);
        FREEANDNULL (uvs);


        r = fscanf (file, "%d\n", &triangle_num);
        printf ("triangle_num = %d.\n", triangle_num);
		
		setTriangleNums(triangle_num, i);

        indices = (short *)malloc (triangle_num * 3 * sizeof (short));
	
        for (j = 0; j < triangle_num; j++)  {
            r = fscanf (file, "%d %d %d %d %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g\n",
                           &temp, /*nSmoothGroup*/
                           &indices[j*3],
                           &indices[j*3+1],
                           &indices[j*3+2],
                           &box,
                           &box,
                           &box,
                           &box,
                           &box,
                           &box,
                           &box,
                           &box,
                           &box,
                           &box,
                           &box,
                           &box,
                           &box,
                           &box,
                           &box);

                /*printf ("%d %d %d %d %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g\n",
                               temp, //nSmoothGroup
                               m_model.meshes[i].triangles[j].indices[0],
                               m_model.meshes[i].triangles[j].indices[1],
                               m_model.meshes[i].triangles[j].indices[2],
                               m_model.meshes[i].triangles[j].normals[0][0],
                               m_model.meshes[i].triangles[j].normals[0][1],
                               m_model.meshes[i].triangles[j].normals[0][2],
                               m_model.meshes[i].triangles[j].normals[1][0],
                               m_model.meshes[i].triangles[j].normals[1][1],
                               m_model.meshes[i].triangles[j].normals[1][2],
                               m_model.meshes[i].triangles[j].normals[2][0],
                               m_model.meshes[i].triangles[j].normals[2][1],
                               m_model.meshes[i].triangles[j].normals[2][2],
                               m_model.meshes[i].triangles[j].s[0],
                               m_model.meshes[i].triangles[j].s[1],
                               m_model.meshes[i].triangles[j].s[2],
                               m_model.meshes[i].triangles[j].t[0],
                               m_model.meshes[i].triangles[j].t[1],
                               m_model.meshes[i].triangles[j].t[2]);*/

        }


        setIndices (indices, triangle_num * 3 * sizeof (short), i);

        FREEANDNULL (indices);
 


//    	setMaterialAmbient (0.9, 0.6, 0.6, 0);
//    	setMaterialDiffuse (0.9, 0.6, 0.6, 0);


		float ambient [3];
    	float diffuse [3];
    	float specular [3];
    	float emission [3];
    	float shininess;



        r = fscanf (file, "%d\n", &material_num);
        //_M3D_PRINTF ("material_num = %d.\n", material_num);


		//FIXME: handle only one material

        r = fscanf (file, "%g %g %g %g %g %g %g %g %g %g %g %g %g %g\n",
                           &specular_level,
                           &glossiness,
                           &ambient[0],
                           &ambient[1],
                           &ambient[2],
                           &diffuse[0],
                           &diffuse[1],
                           &diffuse[2],
                           &specular[0],
                           &specular[1],
                           &specular[2],
                           &emission[0],
                           &emission[1],
                           &emission[2]);

        if (specular_level > 0)
            shininess = glossiness;
        else
            shininess = -1;

			
/*
            _M3D_PRINTF ("loadAmModel: %g %g %g %g %g %g %g %g %g %g\n",
                           shininess,
                           ambient[0],
                           ambient[1],
                           ambient[2],
                           diffuse[0],
                           diffuse[1],
                           diffuse[2],
                           specular[0],
                           specular[1],
                           specular[2]);
        }
*/

        setMaterialAmbient (ambient[0],
                            ambient[1],
                            ambient[2],
                            i);

        setMaterialDiffuse (diffuse[0],
                            diffuse[1],
                            diffuse[2],
                            i);

        setMaterialEmission (emission[0],
                             emission[1],
                             emission[2],
                             i);

        if (shininess > 0) {

             setMaterialShininess (shininess, i);
             setMaterialSpecular (specular[0], specular[1], specular[2], i);

        }


 

    }



    fclose (file);


    return;
}





M3D_END_NAMESPACE
