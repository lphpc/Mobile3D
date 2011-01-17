
#include "imagePixelData.h"


M3D_BEGIN_NAMESPACE

    ImagePixelData::ImagePixelData() {
    }

    ImagePixelData::~ImagePixelData() {
    }


    Texture *ImagePixelData::loadTexture(unsigned char *data, int width, int height, M3D_BitmapConfig config) {
	
        Texture *texture = (Texture *) malloc(sizeof(Texture));
		texture->width = width;
        texture->height = height;

		if (config == M3D_RGB) {

        	glGenTextures(1, &(texture->textureId));
        	glBindTexture(GL_TEXTURE_2D, texture->textureId);

        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		}
		else {
			FREEANDNULL (texture);
			return NULL;
		}

        return texture;


		
    }

M3D_END_NAMESPACE

