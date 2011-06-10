
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include "app.h"

#ifdef __cplusplus
extern "C" {
#endif


#define MAX_BODY_NUM    2
#define MAX_HEAD_NUM    7
#define MAX_HAIR_NUM    3
#define MAX_EYEBROW_NUM    3
#define MAX_EYE_NUM    3
#define MAX_NOSE_NUM    3
#define MAX_MOUTH_NUM    3
#define MAX_BEARD_NUM    3

const char * body_file_name [MAX_BODY_NUM] = {
        //"male_body.am",
        //"female_body.am",
        "/data/mobile3d/androidgldemos/andmii/male_body_1.am",
};


const char * head_file_name [MAX_HEAD_NUM] = {
        //"male_head.am",
        //"female_head.am",
        "/data/mobile3d/androidgldemos/andmii/male_head_guazilian.am",
        "/data/mobile3d/androidgldemos/andmii/male_head_yuanlian.am",
        "/data/mobile3d/androidgldemos/andmii/male_head_changlian.am",
        "/data/mobile3d/androidgldemos/andmii/male_head_jianzui.am",
        "/data/mobile3d/androidgldemos/andmii/male_head_sifang.am",
        "/data/mobile3d/androidgldemos/andmii/male_head_changfang.am",
        "/data/mobile3d/androidgldemos/andmii/male_head_xiakuanchanglian.am"
};


const char * hair_file_name [MAX_HAIR_NUM] = {
        //"male_hair.am",
        //"female_hair.am",
        "/data/mobile3d/androidgldemos/andmii/male_hair_01.am",
        "/data/mobile3d/androidgldemos/andmii/male_hair_02.am",
        "/data/mobile3d/androidgldemos/andmii/male_hair_03.am",
};

const char * eyebrow_l_file_name [MAX_EYEBROW_NUM] = {
        //"male_eyebrow_l.am",
        //"female_eyebrow_l.am",
        "/data/mobile3d/androidgldemos/andmii/male_eyebrow_01_l.am",
        "/data/mobile3d/androidgldemos/andmii/male_eyebrow_02_l.am",
        "/data/mobile3d/androidgldemos/andmii/male_eyebrow_03_l.am",
};

const char * eyebrow_r_file_name [MAX_EYEBROW_NUM] = {
        //"male_eyebrow_r.am",
        //"female_eyebrow_r.am",
        "/data/mobile3d/androidgldemos/andmii/male_eyebrow_01_r.am",
        "/data/mobile3d/androidgldemos/andmii/male_eyebrow_02_r.am",
        "/data/mobile3d/androidgldemos/andmii/male_eyebrow_03_r.am",

};

const char * eye_l_file_name [MAX_EYE_NUM] = {
        //"male_eye_l.am",
        //"female_eye_l.am",
        "/data/mobile3d/androidgldemos/andmii/male_eye_01_l.am",
        "/data/mobile3d/androidgldemos/andmii/male_eye_02_l.am",
        "/data/mobile3d/androidgldemos/andmii/male_eye_03_l.am",
};


const char * eye_r_file_name [MAX_EYE_NUM] = {
        //"male_eye_r.am",
        //"female_eye_r.am",
        "/data/mobile3d/androidgldemos/andmii/male_eye_01_r.am",
        "/data/mobile3d/androidgldemos/andmii/male_eye_02_r.am",
        "/data/mobile3d/androidgldemos/andmii/male_eye_03_r.am",
};


const char * nose_file_name [MAX_NOSE_NUM] = {
        //"male_nose.am",
        //"female_nose.am",
        "/data/mobile3d/androidgldemos/andmii/male_nose_01.am",
        "/data/mobile3d/androidgldemos/andmii/male_nose_02.am",
        "/data/mobile3d/androidgldemos/andmii/male_nose_03.am",
};

const char * mouth_file_name [MAX_MOUTH_NUM] = {
        //"male_mouth.am",
        //"female_mouth.am",
        "/data/mobile3d/androidgldemos/andmii/male_mouth_01.am",
        "/data/mobile3d/androidgldemos/andmii/male_mouth_02.am",
        "/data/mobile3d/androidgldemos/andmii/male_mouth_03.am",
};



//all mesh data structure
M3D::am_model_t **bodies;
int body_num = 0;

M3D::am_model_t **heads;
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

    body_num = 1;
    bodies = (M3D::am_model_t**)malloc (body_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < body_num; i++)
        bodies[i] = M3D::ModelAM::loadAmModel (body_file_name[i]);


    head_num = 7;
    heads = (M3D::am_model_t**)malloc (head_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < head_num; i++)
        heads[i] = M3D::ModelAM::loadAmModel (head_file_name[i]);


    hair_num = 3;
    hair = (M3D::am_model_t**)malloc (hair_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < hair_num; i++)
        hair[i] = M3D::ModelAM::loadAmModel (hair_file_name[i]);

    eyebrow_l_num = 3;
    eyebrows_l = (M3D::am_model_t**)malloc (eyebrow_l_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < eyebrow_l_num; i++)
        eyebrows_l[i] = M3D::ModelAM::loadAmModel (eyebrow_l_file_name[i]);


    eyebrow_r_num = 3;
    eyebrows_r = (M3D::am_model_t**)malloc (eyebrow_r_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < eyebrow_r_num; i++)
        eyebrows_r[i] = M3D::ModelAM::loadAmModel (eyebrow_r_file_name[i]);


    eye_l_num = 3;
    eyes_l = (M3D::am_model_t**)malloc (eye_l_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < eye_l_num; i++)
        eyes_l[i] = M3D::ModelAM::loadAmModel (eye_l_file_name[i]);


    eye_r_num = 3;
    eyes_r = (M3D::am_model_t**)malloc (eye_r_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < eye_r_num; i++)
        eyes_r[i] = M3D::ModelAM::loadAmModel (eye_r_file_name[i]);


    nose_num = 3;
    noses = (M3D::am_model_t**)malloc (nose_num * sizeof (M3D::am_model_t*));
    for (i = 0; i < nose_num; i++)
        noses[i] = M3D::ModelAM::loadAmModel (nose_file_name[i]);

    mouth_num = 3;
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

    __android_log_print(ANDROID_LOG_INFO, "AndMii", "dump bodies.\n");


    for (i = 0; i < body_num; i++){

    	__android_log_print(ANDROID_LOG_INFO, "AndMii", "body_file_name[%d] = %s.\n", i, body_file_name[i]);

        if (bodies == NULL)
    		__android_log_print(ANDROID_LOG_INFO, "AndMii", "bodies = NULL.\n");

        if (bodies[i] == NULL)
    		__android_log_print(ANDROID_LOG_INFO, "AndMii", "bodies[%d] = NULL.\n", i);

    	__android_log_print(ANDROID_LOG_INFO, "AndMii", "bodies[%d]->mesh_num = %d\n", i, bodies[i]->mesh_num);
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

