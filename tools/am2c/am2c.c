
#include <stdio.h>
#include "am2c.h"

am_model_t *load_model (const char* filename)
{

	FILE *file;
	int r, i, j;
    int version = 0;
    int mesh_num = 0;
    int vertex_num = 0;
    int uv_num = 0;
    int triangle_num = 0;
    int material_num = 0;
    int temp = 0;
    float t1, t2, t3;
    float specular_level, glossiness;
	am_model_t*model = NULL;


    file = fopen (filename, "r");
    if (file == NULL)
        return NULL;

    r = fscanf (file, "SimpleMeshFormat %d\n", &version);
    printf ("verson = %d.\n", version);

    r = fscanf (file, "%d\n", &mesh_num);
    printf ("mesh_num = %d.\n", mesh_num);

	
   	model = (am_model_t*)malloc(sizeof(am_model_t));
	if (model == NULL){
        fclose (file);
		return NULL;
	}

    model->mesh_num = mesh_num;
    model->meshes = (am_mesh_t*)malloc (mesh_num * sizeof (am_mesh_t));
	if (model->meshes == NULL) {
		//Fixme
        fclose (file);
		return NULL;
	}

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
            printf ("mesh[%d]->vertex[%d] = %g %g %g.\n", i, j,
                            model->meshes[i].vertices[j].vertex[0],
                            model->meshes[i].vertices[j].vertex[1],
                            model->meshes[i].vertices[j].vertex[2]);
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
                               &model->meshes[i].triangles[j].t[0],
                               &model->meshes[i].triangles[j].s[1],
                               &model->meshes[i].triangles[j].t[1],
                               &model->meshes[i].triangles[j].s[2],
                               &model->meshes[i].triangles[j].t[2]);
                /*
                printf ("%d %d %d %d %d %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g\n",
                               j,
                               temp, //nSmoothGroup
                               model->meshes[i].triangles[j].indices[0],
                               model->meshes[i].triangles[j].indices[1],
                               model->meshes[i].triangles[j].indices[2],
                               model->meshes[i].triangles[j].normals[0][0],
                               model->meshes[i].triangles[j].normals[0][1],
                               model->meshes[i].triangles[j].normals[0][2],
                               model->meshes[i].triangles[j].normals[1][0],
                               model->meshes[i].triangles[j].normals[1][1],
                               model->meshes[i].triangles[j].normals[1][2],
                               model->meshes[i].triangles[j].normals[2][0],
                               model->meshes[i].triangles[j].normals[2][1],
                               model->meshes[i].triangles[j].normals[2][2],
                               model->meshes[i].triangles[j].s[0],
                               model->meshes[i].triangles[j].s[1],
                               model->meshes[i].triangles[j].s[2],
                               model->meshes[i].triangles[j].t[0],
                               model->meshes[i].triangles[j].t[1],
                               model->meshes[i].triangles[j].t[2]);  */

        }

        r = fscanf (file, "%d\n", &material_num);

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

            }

        }

        fclose (file);

		return model;
}

void export_model (am_model_t* model, const char* filename)
{

	FILE *file;
	int i = 0, j  = 0;

	if (model == NULL)
		return;

    file = fopen (filename, "w");
    if (file == NULL)
        return;


    for (i = 0; i < model->mesh_num; i++) {

		fprintf (file, "\n\n/*============== %s ==============*/\n\n", 
					model->meshes[i].mesh_name);
		
		fprintf (file, "GLfloat afVertices_%s[]= {\n", model->meshes[i].mesh_name);


        for (j = 0; j < model->meshes[i].vertex_num; j++){

			fprintf (file, "\t%g, %g, %g,\n", 
						model->meshes[i].vertices[j].vertex[0],
						model->meshes[i].vertices[j].vertex[1],
						model->meshes[i].vertices[j].vertex[2]);

        }

		fprintf (file, "};\n\n");


		fprintf (file, "GLfloat afTexCoord_%s[] = {\n", model->meshes[i].mesh_name);

        for (j = 0; j < model->meshes[i].vertex_num; j++){

			fprintf (file, "\t%g, %g,\n", 
						model->meshes[i].vertices[j].uvs[0],
						model->meshes[i].vertices[j].uvs[1]);

        }

		fprintf (file, "};\n\n");


		fprintf (file, "GLint afVertIndices_%s[] = {\n", model->meshes[i].mesh_name);

        for (j = 0; j < model->meshes[i].triangle_num; j++){

			fprintf (file, "\t%d, %d, %d,\n", 
						model->meshes[i].triangles[j].indices[0],
						model->meshes[i].triangles[j].indices[1],
						model->meshes[i].triangles[j].indices[2]);

        }


		fprintf (file, "};\n\n");

		fprintf (file, "GLfloat afNormals_%s[] = {\n", model->meshes[i].mesh_name);

        for (j = 0; j < model->meshes[i].triangle_num; j++){

			fprintf (file, "\t%g, %g, %g, %g, %g, %g, %g, %g, %g,\n", 
						model->meshes[i].triangles[j].normals[0][0],
						model->meshes[i].triangles[j].normals[0][1],
						model->meshes[i].triangles[j].normals[0][2],
						model->meshes[i].triangles[j].normals[1][0],
						model->meshes[i].triangles[j].normals[1][1],
						model->meshes[i].triangles[j].normals[1][2],
						model->meshes[i].triangles[j].normals[2][0],
						model->meshes[i].triangles[j].normals[2][1],
						model->meshes[i].triangles[j].normals[2][2]);

        }


		fprintf (file, "};\n\n");


    }

	
	fclose (file);

}

int main (int argc, char*argv[])
{
	am_model_t*model = NULL;

	if (argc <= 1){
		printf ("Please specify a file.\n");
		return 0;
	}

	model = load_model (argv[1]);

	export_model (model, argv[2]);

	return 0;	
}
