
#ifndef M3D_IMAGERGB_H_
#define M3D_IMAGERGB_H_

#include "m3d.h"
#include "image.h"

M3D_BEGIN_NAMESPACE



	typedef struct _ImageRec {
    	unsigned short imagic;
    	unsigned short type;
    	unsigned short dim;
    	unsigned short xsize, ysize, zsize;
    	unsigned int min, max;
    	unsigned int wasteBytes;
    	char name[80];
    	unsigned long colorMap;
    	FILE *file;
    	unsigned char *tmp;
    	unsigned long rleEnd;
    	unsigned int *rowStart;
    	int *rowSize;
	} ImageRec;



    class ImageRGB : public Image {

    private:
        GLsizei m_width;
        GLsizei m_height;

	private:
		void rgbtorgb(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *l,int n);
		void ConvertShort(unsigned short *array, unsigned int length);
		void ConvertUint(unsigned *array, unsigned int length);
		ImageRec *ImageOpen(const char *fileName);
		void ImageClose(ImageRec *image);
		void ImageGetRow(ImageRec *image, unsigned char *buf, int y, int z);
		GLubyte *read_alpha_texture(const char *name, int *width, int *height);
		GLubyte *read_rgb_texture(const char *name, int *width, int *height);

    public:
        ImageRGB();
        ~ImageRGB();

        Texture *loadRGBTexture(const char *filename);
        Texture *loadAlphaTexture(const char *filename);
    };


M3D_END_NAMESPACE

#endif /* M3D_IMAGERGB_H_ */
