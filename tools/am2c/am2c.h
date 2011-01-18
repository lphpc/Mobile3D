

#define AM_MAX_MESHNAME    16

    typedef struct {
        float vertex [3];
        float uvs[2];
    } am_vertex_t;

    typedef struct  {
        short indices [3];
        float normals [3][3];
        float s[3];
        float t[3];
    } am_triangle_t;

    typedef struct {
        char mesh_name[AM_MAX_MESHNAME];
        am_vertex_t *vertices;
        am_triangle_t *triangles;
        int triangle_num;
        int vertex_num;
        float ambient [3];
        float diffuse [3];
        float specular [3];
        float emission [3];
        float shininess [1];
    } am_mesh_t;

    typedef struct {
        am_mesh_t *meshes;
        int mesh_num;
    } am_model_t;

