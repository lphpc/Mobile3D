
#include <stdio.h>
#include <stdlib.h>
#include <mobile3d/m3d.h>
#include <mobile3d/model_am.h>

using namespace M3D;

#ifdef __cplusplus
extern "C" {
#endif



#define MAX_BODY_NUM    1
#define MAX_HEAD_NUM    7
#define MAX_HAIR_NUM    3
#define MAX_EYEBROW_NUM    3
#define MAX_EYE_NUM    3
#define MAX_NOSE_NUM    3
#define MAX_MOUTH_NUM   3
#define MAX_BEARD_NUM   3

const char * body_file_name [MAX_BODY_NUM] = {
        "/usr/local/share/mobile3d/mii/male_body_1.am",
};


const char * head_file_name [MAX_HEAD_NUM] = {
        "/usr/local/share/mobile3d/mii/male_head_guazilian.am",
        "/usr/local/share/mobile3d/mii/male_head_yuanlian.am",
        "/usr/local/share/mobile3d/mii/male_head_changlian.am",
        "/usr/local/share/mobile3d/mii/male_head_jianzui.am",
        "/usr/local/share/mobile3d/mii/male_head_sifang.am",
        "/usr/local/share/mobile3d/mii/male_head_changfang.am",
        "/usr/local/share/mobile3d/mii/male_head_xiakuanchanglian.am"
};


const char * hair_file_name [MAX_HAIR_NUM] = {
        "/usr/local/share/mobile3d/mii/male_hair_01.am",
        "/usr/local/share/mobile3d/mii/male_hair_02.am",
        "/usr/local/share/mobile3d/mii/male_hair_03.am",
};

const char * eyebrow_l_file_name [MAX_EYEBROW_NUM] = {
        "/usr/local/share/mobile3d/mii/male_eyebrow_01_l.am",
        "/usr/local/share/mobile3d/mii/male_eyebrow_02_l.am",
        "/usr/local/share/mobile3d/mii/male_eyebrow_03_l.am",
};

const char * eyebrow_r_file_name [MAX_EYEBROW_NUM] = {
        "/usr/local/share/mobile3d/mii/male_eyebrow_01_r.am",
        "/usr/local/share/mobile3d/mii/male_eyebrow_02_r.am",
        "/usr/local/share/mobile3d/mii/male_eyebrow_03_r.am",

};

const char * eye_l_file_name [MAX_EYE_NUM] = {
        "/usr/local/share/mobile3d/mii/male_eye_01_l.am",
        "/usr/local/share/mobile3d/mii/male_eye_02_l.am",
        "/usr/local/share/mobile3d/mii/male_eye_03_l.am",
};


const char * eye_r_file_name [MAX_EYE_NUM] = {
        "/usr/local/share/mobile3d/mii/male_eye_01_r.am",
        "/usr/local/share/mobile3d/mii/male_eye_02_r.am",
        "/usr/local/share/mobile3d/mii/male_eye_03_r.am",
};


const char * nose_file_name [MAX_NOSE_NUM] = {
        "/usr/local/share/mobile3d/mii/male_nose_01.am",
        "/usr/local/share/mobile3d/mii/male_nose_02.am",
        "/usr/local/share/mobile3d/mii/male_nose_03.am",
};

const char * mouth_file_name [MAX_MOUTH_NUM] = {
        "/usr/local/share/mobile3d/mii/male_mouth_01.am",
        "/usr/local/share/mobile3d/mii/male_mouth_02.am",
        "/usr/local/share/mobile3d/mii/male_mouth_03.am",
};



//all mesh data structure
am_model_t **bodies;
int body_num = 0;

am_model_t **heads;
int head_num = 0;

M3D::am_model_t **hair;
int hair_num = 0;

M3D::am_model_t **eyebrows_l;
int eyebrow_l_num = 0;

M3D::am_model_t **eyebrows_r;
int eyebrow_r_num = 0;

M3D::am_model_t **eyes_l;
int eye_l_num = 0;

M3D::am_model_t **eyes_r;
int eye_r_num = 0;

M3D::am_model_t **noses;
int nose_num = 0;

M3D::am_model_t **mouths;
int mouth_num = 0;

bool loadAllMeshes ()
{
    int i;

    printf ("load all meshes.\n");

    body_num = MAX_BODY_NUM;
    bodies = (M3D::am_model_t**)malloc (body_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < body_num; i++)
        bodies[i] = M3D::ModelAM::loadAmModel (body_file_name[i]);


    head_num = MAX_HEAD_NUM;
    heads = (M3D::am_model_t**)malloc (head_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < head_num; i++)
        heads[i] = M3D::ModelAM::loadAmModel (head_file_name[i]);


    hair_num = MAX_HAIR_NUM;
    hair = (M3D::am_model_t**)malloc (hair_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < hair_num; i++)
        hair[i] = M3D::ModelAM::loadAmModel (hair_file_name[i]);

    eyebrow_l_num = MAX_EYEBROW_NUM;
    eyebrows_l = (M3D::am_model_t**)malloc (eyebrow_l_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < eyebrow_l_num; i++)
        eyebrows_l[i] = M3D::ModelAM::loadAmModel (eyebrow_l_file_name[i]);


    eyebrow_r_num = MAX_EYEBROW_NUM;
    eyebrows_r = (M3D::am_model_t**)malloc (eyebrow_r_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < eyebrow_r_num; i++)
        eyebrows_r[i] = M3D::ModelAM::loadAmModel (eyebrow_r_file_name[i]);


    eye_l_num = MAX_EYE_NUM;
    eyes_l = (M3D::am_model_t**)malloc (eye_l_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < eye_l_num; i++)
        eyes_l[i] = M3D::ModelAM::loadAmModel (eye_l_file_name[i]);


    eye_r_num = MAX_EYE_NUM;
    eyes_r = (M3D::am_model_t**)malloc (eye_r_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < eye_r_num; i++)
        eyes_r[i] = M3D::ModelAM::loadAmModel (eye_r_file_name[i]);


    nose_num = MAX_NOSE_NUM;
    noses = (M3D::am_model_t**)malloc (nose_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < nose_num; i++)
        noses[i] = M3D::ModelAM::loadAmModel (nose_file_name[i]);

    mouth_num = MAX_MOUTH_NUM;
    mouths = (M3D::am_model_t**)malloc (mouth_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < mouth_num; i++)
        mouths[i] = M3D::ModelAM::loadAmModel (mouth_file_name[i]);

    return true;
}

void destroyAllMeshes ()
{
    int i;

    for (i = 0; i < body_num; i++)
        FREEANDNULL(bodies[i]);
    FREEANDNULL(bodies);

    for (i = 0; i < head_num; i++)
        FREEANDNULL(heads[i]);
    FREEANDNULL(heads);


    for (i = 0; i < hair_num; i++)
        FREEANDNULL(hair[i]);
    FREEANDNULL(hair);

    for (i = 0; i < eyebrow_l_num; i++)
        FREEANDNULL(eyebrows_l[i]);
    FREEANDNULL(eyebrows_l);

    for (i = 0; i < eyebrow_r_num; i++)
        FREEANDNULL(eyebrows_r[i]);
    FREEANDNULL(eyebrows_r);



    for (i = 0; i < eye_l_num; i++)
        FREEANDNULL(eyes_l[i]);
    FREEANDNULL(eyes_l);

    for (i = 0; i < eye_r_num; i++)
        FREEANDNULL(eyes_r[i]);
    FREEANDNULL(eyes_r);


    for (i = 0; i < nose_num; i++)
        FREEANDNULL(noses[i]);
    FREEANDNULL(noses);


    for (i = 0; i < mouth_num; i++)
        FREEANDNULL(mouths[i]);
    FREEANDNULL(mouths);

}

void dumpBodies ()
{

    int i = 0;

    printf ("dump bodies.\n");


    for (i = 0; i < body_num; i++){

        printf ("body_file_name[%d] = %s.\n", i, body_file_name[i]);

        if (bodies == NULL)
            printf ("bodies = NULL.\n");

        if (bodies[i] == NULL)
            printf ("bodies[%d] = NULL.\n", i);

        printf ("bodies[%d]->mesh_num = %d\n", i, bodies[i]->mesh_num);
    }
/*
    for (i = 0; i < body_num; i++) {
        printf ("body%d has %d mesh.\n", i, bodies[i]->mesh_num);
    }
*/
    return;
}



#ifdef __cplusplus
}
#endif

