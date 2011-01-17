
#ifndef M3D_IMAGETGA_H_
#define M3D_IMAGETGA_H_

#include "m3d.h"
#include "image.h"

M3D_BEGIN_NAMESPACE


typedef struct
{
    GLubyte Header[12];                                 /* TGA File Header */
} TGAHeader;

typedef struct
{
    GLubyte     header[6];                              /* First 6 Useful Bytes From The Header */
    GLuint      bytesPerPixel;                          /* Holds Number Of Bytes Per Pixel Used In The TGA File */
    GLuint      imageSize;                              /* Used To Store The Image Size When Setting Aside Ram */
    GLuint      temp;                                   /* Temporary Variable */
    GLuint      type;
    GLuint      Height;                                 /* Height of Image */
    GLuint      Width;                                  /* Width ofImage */
    GLuint      Bpp;                                    /* Bits Per Pixel */
} TGA;


class ImageTGA : public Image {

private:
	TGAHeader tgaheader;                                    /* TGA header */
	TGA tga;
	int m_width;
	int m_height;

private: 
	Texture* LoadUncompressedTGA(const char * filename, FILE * fTGA);
	Texture* LoadCompressedTGA(const char * filename, FILE * fTGA);	/* Load COMPRESSED TGAs */

public:
	ImageTGA();
    ~ImageTGA();

    Texture *loadTexture(const char *filename);
};


M3D_END_NAMESPACE

#endif /* M3D_IMAGETGA_H_ */
