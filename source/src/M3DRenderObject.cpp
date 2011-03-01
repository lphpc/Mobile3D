
#include "M3DRenderObject.h"
#include "log.h"


M3D_BEGIN_NAMESPACE

M3DRenderObject::M3DRenderObject() {
	m_vertices = NULL;
   	m_indices = NULL;
    m_colors = NULL;

    m_normals = NULL;
    m_uvs = NULL;
    m_textureId = -1;

    m_position = NULL;
    m_rotate = NULL;
    m_scale = NULL;

    m_materialAmbient = NULL;
    m_materialDiffuse = NULL;
    m_materialSpecular = NULL;
    m_materialEmission = NULL;
    m_materialShininess = NULL;

	m_blendEnabled = false;

	m_hardwareVertexBuffer = NULL;
	m_hardwareIndexBuffer = NULL;
	m_softwareVertexBuffer = NULL;
	m_softwareIndexBuffer = NULL;


/*
    m_triangleNums = 0;
    m_enabled = GL_FALSE;
	m_matrix = NULL;
*/	
	m_primType = PT_TRIANGLES;

	m_vertexCount = 0;
	m_indexCount = 0;

}

M3DRenderObject::~M3DRenderObject() {

}



M3D_END_NAMESPACE
