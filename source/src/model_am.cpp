

#include "model_am.h"


M3D_BEGIN_NAMESPACE

/**
 * ModelMD2 class for all games using M3D.
 */

ModelAM::ModelAM() :
    m_model(NULL) {

}

ModelAM::~ModelAM() {

    int i = 0;

    if (NULL == m_model)
        return;

    if (m_model->mesh_num == 0)
        return;

    for (i = 0; i < m_model->mesh_num; i++) {
        if (m_model->meshes[i].vertex_num > 0 && m_model->meshes[i].vertices != NULL)
            FREEANDNULL (m_model->meshes[i].vertices);

        if (m_model->meshes[i].triangle_num> 0 && m_model->meshes[i].triangles != NULL)
            FREEANDNULL (m_model->meshes[i].triangles);

    }

    FREEANDNULL(m_model->meshes);
}


am_model_t* ModelAM::loadAmModel (const char* filename)
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
    am_model_t *model = NULL;
    int material_num = 0;
    float specular_level, glossiness;

    printf ("loadModel %s.\n", filename);

    file = fopen (filename, "r");
    if (file == NULL)
        return NULL;

    model = (am_model_t*)malloc (sizeof (am_model_t));

    r = fscanf (file, "SimpleMeshFormat %d\n", &version);
    printf ("verson = %d.\n", version);

    r = fscanf (file, "%d\n", &mesh_num);
    printf ("mesh_num = %d.\n", mesh_num);

    model->mesh_num = mesh_num;
    model->meshes = (am_mesh_t*)malloc (mesh_num * sizeof (am_mesh_t));

    for (i = 0; i < mesh_num; i++) {

        r = fscanf (file, "%s\n", model->meshes[i].mesh_name);
        printf ("mesh_name = %s.\n", model->meshes[i].mesh_name);

        r = fscanf (file, "%d\n", &vertex_num);

        model->meshes[i].vertex_num = vertex_num;
        printf ("vertex_num = %d.\n", model->meshes[i].vertex_num);

        model->meshes[i].vertices = (am_vertex_t*)malloc (vertex_num * sizeof (am_vertex_t));
        if (!model->meshes[i].vertices) {
            //Fixme: free sth if needed.
            return NULL;
        }

        for (j = 0; j < vertex_num; j++)  {
            r = fscanf (file, "%g %g %g\n",
                            &model->meshes[i].vertices[j].vertex[0],
                            &model->meshes[i].vertices[j].vertex[1],
                            &model->meshes[i].vertices[j].vertex[2]);
            /*printf ("mesh[%d]->vertex[%d] = %g %g %g.\n", i, j,
                            m_model.meshes[i].vertices[j].vertex[0],
                            m_model.meshes[i].vertices[j].vertex[1],
                            m_model.meshes[i].vertices[j].vertex[2]);*/
        }


        r = fscanf (file, "%d\n", &uv_num);

        for (j = 0; j < uv_num; j++)  {
            r = fscanf (file, "%g %g\n",
                            &model->meshes[i].vertices[j].uvs[0],
                            &model->meshes[i].vertices[j].uvs[1]);
        }


        r = fscanf (file, "%d\n", &triangle_num);
        model->meshes[i].triangle_num = triangle_num;
        printf ("triangle_num = %d.\n", model->meshes[i].triangle_num);

        model->meshes[i].triangles = (am_triangle_t*)malloc (triangle_num * sizeof (am_triangle_t));
        if (!model->meshes[i].triangles) {
            //Fixme: free sth
            return NULL;
        }

        for (j = 0; j < triangle_num; j++)  {
            r = fscanf (file, "%d %d %d %d %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g\n",
                           &temp, /*nSmoothGroup*/
                           &model->meshes[i].triangles[j].indices[0],
                           &model->meshes[i].triangles[j].indices[1],
                           &model->meshes[i].triangles[j].indices[2],
                           &model->meshes[i].triangles[j].normals[0][0],
                           &model->meshes[i].triangles[j].normals[0][1],
                           &model->meshes[i].triangles[j].normals[0][2],
                           &model->meshes[i].triangles[j].normals[1][0],
                           &model->meshes[i].triangles[j].normals[1][1],
                           &model->meshes[i].triangles[j].normals[1][2],
                           &model->meshes[i].triangles[j].normals[2][0],
                           &model->meshes[i].triangles[j].normals[2][1],
                           &model->meshes[i].triangles[j].normals[2][2],
                           &model->meshes[i].triangles[j].s[0],
                           &model->meshes[i].triangles[j].s[1],
                           &model->meshes[i].triangles[j].s[2],
                           &model->meshes[i].triangles[j].t[0],
                           &model->meshes[i].triangles[j].t[1],
                           &model->meshes[i].triangles[j].t[2]);

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

        r = fscanf (file, "%d\n", &material_num);
        printf ("material_num = %d.\n", material_num);

        for (j = 0; j < material_num; j++)  {
            r = fscanf (file, "%g %g %g %g %g %g %g %g %g %g %g %g %g %g\n",
                           &specular_level,
                           &glossiness,
                           &model->meshes[i].ambient[0],
                           &model->meshes[i].ambient[1],
                           &model->meshes[i].ambient[2],
                           &model->meshes[i].diffuse[0],
                           &model->meshes[i].diffuse[1],
                           &model->meshes[i].diffuse[2],
                           &model->meshes[i].specular[0],
                           &model->meshes[i].specular[1],
                           &model->meshes[i].specular[2],
                           &model->meshes[i].emission[0],
                           &model->meshes[i].emission[1],
                           &model->meshes[i].emission[2]);

            if (specular_level > 0)
                model->meshes[i].shininess[0] = glossiness;
            else
                model->meshes[i].shininess[0] = -1;


/*
            printf ("%g %g %g %g %g %g %g %g %g %g\n",
                           &model->meshes[i].shininess[0],
                           &model->meshes[i].ambient[0],
                           &model->meshes[i].ambient[1],
                           &model->meshes[i].ambient[2],
                           &model->meshes[i].diffuse[0],
                           &model->meshes[i].diffuse[1],
                           &model->meshes[i].diffuse[2],
                           &model->meshes[i].specular[0],
                           &model->meshes[i].specular[1],
                           &model->meshes[i].specular[2]);
*/
        }
    }

    fclose (file);


    return model;
}


bool ModelAM::loadModel(const char *filename) {

	m_model = loadAmModel (filename);
	setMeshCount (m_model->mesh_num);

	if (m_model == NULL)
		return false;

	return true;
}


void ModelAM::loadModel(am_model_t *model){

    int mesh_num = 0;
    int triangle_num = 0;
    int i = 0;

    if (m_model == NULL){

        m_model = model;

        mesh_num = model->mesh_num;
        setMeshCount (mesh_num);

        for (i = 0; i < mesh_num; i++) {
            triangle_num = model->meshes[i].triangle_num;
            setTriangleNums (triangle_num, i);
        }

    }

    return;

}

void ModelAM::updateModel(am_model_t *model){

    GLfloat position_x = 0;
    GLfloat position_y = 0;
    GLfloat position_z = 0;
    GLfloat rotate_x = 0;
    GLfloat rotate_y = 0;
    GLfloat rotate_z = 0;
    GLfloat scale_x  = 0;
    GLfloat scale_y  = 0;
    GLfloat scale_z  = 0;
	bool havePosition = false;
	bool haveRotate = false;
	bool haveScale = false;

	havePosition = getPosition (&position_x, &position_y, &position_z);
	haveRotate = getRotate (&rotate_x, &rotate_y, &rotate_z);
	haveScale = getScale (&scale_x, &scale_y, &scale_z);
 
    int mesh_num = 0;
    int triangle_num = 0;
    int i = 0;

    m_model = model;

    mesh_num = model->mesh_num;
    setMeshCount (mesh_num);

    for (i = 0; i < mesh_num; i++) {
        triangle_num = model->meshes[i].triangle_num;
        setTriangleNums (triangle_num, i);
    }

	if (havePosition)
		setPosition (position_x, position_y, position_z);
	if (haveRotate)
		setRotate (rotate_x, rotate_y, rotate_z);
	if (haveScale)
		setScale (scale_x, scale_y, scale_z);

	

    return;

}


void ModelAM::prepareFrame() {

    int i = 0, j = 0;
    int vertex_id = 0;
    int uv_id = 0;
    int index_id = 0;
    int vertex_sum = 0;
    int triangle_sum = 0;
    int uv_sum = 0;

    if (m_model == NULL)
        return;

    for (i = 0; i < m_model->mesh_num; i++) {

        vertex_sum = m_model->meshes[i].vertex_num;
        uv_sum = m_model->meshes[i].vertex_num;
        triangle_sum = m_model->meshes[i].triangle_num;

        //printf ("vertex_sum = %d, triangle_sum = %d.\n", vertex_sum, triangle_sum);

        float *vertices = (float*)malloc (vertex_sum * 3 * sizeof (float));
        short *indices = (short *)malloc (triangle_sum * 3 * sizeof (short));
        float *uvs = (float*)malloc (uv_sum * 2 * sizeof (float));

        vertex_id = 0;
        for (j = 0; j < m_model->meshes[i].vertex_num; j++){

            vertices [vertex_id++] = m_model->meshes[i].vertices[j].vertex[0];
            vertices [vertex_id++] = m_model->meshes[i].vertices[j].vertex[1];
            vertices [vertex_id++] = m_model->meshes[i].vertices[j].vertex[2];

        }

        uv_id = 0;
        for (j = 0; j < m_model->meshes[i].vertex_num; j++){

            uvs [uv_id++] = m_model->meshes[i].vertices[j].uvs[0];
            uvs [uv_id++] = m_model->meshes[i].vertices[j].uvs[1];
         }


         //printf ("final vertex_id = %d.\n", vertex_id);

         index_id = 0;
         for (j = 0; j < m_model->meshes[i].triangle_num; j++){
             indices [index_id++] = m_model->meshes[i].triangles[j].indices[0];
             indices [index_id++] = m_model->meshes[i].triangles[j].indices[1];
             indices [index_id++] = m_model->meshes[i].triangles[j].indices[2];
         }
         //printf ("index_id = %d.\n", index_id);


		 setTriangleNums(triangle_sum, i);
         setVertices (vertices, vertex_sum * 3 * sizeof (float), i);
         setIndices (indices, triangle_sum * 3 * sizeof (short), i);
         setUvs(uvs, uv_sum * 2 * sizeof (float), i);


         setMaterialAmbient (m_model->meshes[i].ambient[0],
                             m_model->meshes[i].ambient[1],
                             m_model->meshes[i].ambient[2],
                             i);

         setMaterialDiffuse (m_model->meshes[i].diffuse[0],
                             m_model->meshes[i].diffuse[1],
                             m_model->meshes[i].diffuse[2],
                             i);

         setMaterialEmission (m_model->meshes[i].emission[0],
                              m_model->meshes[i].emission[1],
                              m_model->meshes[i].emission[2],
                              i);

         if (m_model->meshes[i].shininess[0] > 0) {

             setMaterialShininess (m_model->meshes[i].shininess[0], i);
             setMaterialSpecular (m_model->meshes[i].specular[0],
                             m_model->meshes[i].specular[1],
                             m_model->meshes[i].specular[2],
                             i);

         }

         FREEANDNULL (vertices);
         FREEANDNULL (indices);
         FREEANDNULL (uvs);
    }

    return;

    }

void ModelAM::renderModel() {
    //enable or disable gl command status
    prepareFrame();

    for (int i = 0; i < m_meshCount; i++) {
        m_meshs[i].renderMesh();
	}
}

M3D_END_NAMESPACE
