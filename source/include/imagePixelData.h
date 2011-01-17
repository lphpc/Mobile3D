
#ifndef M3D_IMAGEPIXELDATA_H_
#define M3D_IMAGEPIXELDATA_H_

#include "m3d.h"
#include "image.h"


M3D_BEGIN_NAMESPACE



    class ImagePixelData : public Image {

    private:
        GLsizei m_width;
        GLsizei m_height;

    public:
        ImagePixelData();
        ~ImagePixelData();

        Texture *loadTexture(unsigned char *data, int width, int height, M3D_BitmapConfig config);
    };


M3D_END_NAMESPACE

#endif /* M3D_IMAGEPIXELDATA_H_ */
