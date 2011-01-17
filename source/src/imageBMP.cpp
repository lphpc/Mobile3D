
#include "imageBMP.h"


M3D_BEGIN_NAMESPACE

    ImageBMP::ImageBMP() {
    }

    ImageBMP::~ImageBMP() {
    }

    void ImageBMP::fetchPallete(FILE *fd, Color pallete[], int count) {
        unsigned char buff[4];
        int i;

        fseek(fd, BMP_COLOR_OFFSET, SEEK_SET);
        for (i=0; i<count; i++) {
            //read(fd, buff, 4);
            fread (buff, 4, 1, fd);
            pallete[i].red = buff[2];
            pallete[i].green = buff[1];
            pallete[i].blue = buff[0];
        }
        return;
    }

    Texture *ImageBMP::loadTexture(const char *filename) {
        FILE *fd;
        int  bpp, raster, i, j, skip, index = 0;
        Texture *texture = (Texture *) malloc(sizeof(Texture));
        unsigned char buff[4];
        unsigned char id[2];
        unsigned char *buffer;
        Color pallete[256];

        fd = fopen (filename, "rb");
        if (!fd) {
            return NULL;
        }

        //check is real bmp file
        fread (id, 2, 1, fd);

        if ( !(id[0]=='B' && id[1]=='M') ) {
            return NULL;
        }

        if (fseek(fd, BMP_TORASTER_OFFSET, SEEK_SET) == -1) {
            return NULL;
        }

        //read raster
        fread (buff, 4, 1, fd);
        raster = buff[0] + (buff[1]<<8) + (buff[2]<<16) + (buff[3]<<24);

        if (fseek(fd, BMP_SIZE_OFFSET, SEEK_SET) == -1) {
            return NULL;
        }

        //read width
        fread (buff, 4, 1, fd);
        m_width = buff[0] + (buff[1]<<8) + (buff[2]<<16) + (buff[3]<<24);
        //read height
        fread (buff, 4, 1, fd);
        m_height = buff[0] + (buff[1]<<8) + (buff[2]<<16) + (buff[3]<<24);

        buffer = (unsigned char *) malloc(m_width * m_height * 3 * sizeof(unsigned char));
        if (!buffer) {
            return NULL;
        }
        texture->width = m_width;
        texture->height = m_height;

        //read bpp
        if (fseek(fd, BMP_BPP_OFFSET, SEEK_SET) == -1) {
            return NULL;
        }

        //read(fd, buff, 2);
        fread (buff, 2, 1, fd);
        bpp = buff[0] + (buff[1]<<8);

        switch (bpp) {
        case 8: /* 8bit palletized */
            skip = fill4B(m_width);
            fetchPallete(fd, pallete, 256);
            fseek(fd, raster, SEEK_SET);
            for (i = 0; i < m_height; i++) {
                for (j = 0; j < m_width; j++) {
                    //read(fd, buff, 1);
                    fread (buff, 1, 1, fd);
                    buffer[index++] = pallete[buff[0]].red;
                    buffer[index++] = pallete[buff[0]].green;
                    buffer[index++] = pallete[buff[0]].blue;
                }
                if (skip) {
                    //read(fd, buff, skip);
                    fread (buff, skip, 1, fd);
                }
            }
            break;
        case 24: /* 24bit RGB */
            skip = fill4B(m_width * 3);
            fseek(fd, raster, SEEK_SET);
            for (i = 0; i < m_height; i++) {
                for (j = 0; j < m_width; j++) {
                    //read(fd, buff, 3);
                    fread (buff, 3, 1, fd);
                    buffer[index++] = buff[2];
                    buffer[index++] = buff[1];
                    buffer[index++] = buff[0];
                }
                if (skip) {
                    //read(fd, buff, skip);
                    fread (buff, skip, 1, fd);
                }
            }
            break; default:
            return NULL;
        }

        fclose(fd);

        glGenTextures(1, &(texture->textureId));
        glBindTexture(GL_TEXTURE_2D, texture->textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);

        FREEANDNULL(buffer);

        return texture;
    }

M3D_END_NAMESPACE
