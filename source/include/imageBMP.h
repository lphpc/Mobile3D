
#ifndef M3D_IMAGEBMP_H_
#define M3D_IMAGEBMP_H_

#include "m3d.h"
#include "image.h"

#define BMP_TORASTER_OFFSET	10
#define BMP_SIZE_OFFSET		18
#define BMP_BPP_OFFSET		28
#define BMP_RLE_OFFSET		30
#define BMP_COLOR_OFFSET	54

#define fill4B(a)	( ( 4 - ( (a) % 4 ) ) & 0x03)

M3D_BEGIN_NAMESPACE

    class ImageBMP : public Image {

    private:
        GLsizei m_width;
        GLsizei m_height;

        void fetchPallete(FILE *fd, Color pallete[], int count);

    public:
        ImageBMP();
        ~ImageBMP();

        Texture *loadTexture(const char *filename);
    };

M3D_END_NAMESPACE

#endif /* M3D_IMAGEBMP_H_ */
