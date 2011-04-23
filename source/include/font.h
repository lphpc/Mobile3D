
#ifndef _M3D_FONT_H_
#define _M3D_FONT_H_

#include "m3d.h"
#include "imageBMP.h"

M3D_BEGIN_NAMESPACE

class Font {
    private:
        unsigned int    m_charWidth;
        unsigned int    m_charHeight;
        unsigned int    m_colCount;
        unsigned int    m_rowCount;
        unsigned int    m_fontWidth;
        unsigned int    m_fontHeight;
        GLint           m_textureId;
        //private functions
    public:
        /**
        * Constructor
        */
        //another font constructor with real draw font width,height
        Font(unsigned int charWidth,
             unsigned int charHeight,
             unsigned int fontWidth,
             unsigned int fontHeight,
             const char *texName);

        /**
         * Destructor
         */
        virtual ~Font();

        void drawString(int x, int y, const char *str);
        void drawString(int x, int y, int fontWidth, int fontHeight, const char *str);
        unsigned int getFonWidth();
        unsigned int getFonHeight();
    };



M3D_END_NAMESPACE

#endif /* _M3D_FONT_H_ */
