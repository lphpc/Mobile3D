
#include "font.h"

M3D_BEGIN_NAMESPACE

#define DEBUG 

    Font::Font(unsigned int charWidth,
               unsigned int charHeight,
               unsigned int fontWidth,
               unsigned int fontHeight,
               const char *texName) {

        m_charWidth = charWidth;
        m_charHeight = charHeight;
        m_fontWidth = fontWidth;
        m_fontHeight = fontHeight;

        ImageBMP *image = new ImageBMP();
        Texture *texture = image->loadTexture(texName);

        m_colCount = texture->width / m_charWidth;
        m_rowCount = texture->height / m_charHeight - 1;
#ifdef DEBUG
        printf("m_colCount: %d, m_rowCount: %d\n", m_colCount, m_rowCount);
#endif
        m_textureId = texture->textureId;

        delete image;
    }

    Font::~Font() {
#ifdef DEBUG
        printf("Font destructor...\n");
#endif
    }

    unsigned int Font::getFonWidth() {
        return m_fontWidth;
    }

    unsigned int Font::getFonHeight() {
        return m_fontHeight;
    }

    void Font::drawString(int x, int y, const char *str) {
        drawString(x, y, m_fontWidth, m_fontHeight, str);
    }

    void Font::drawString(int x, int y, int fontWidth, int fontHeight, const char *str) {
#ifndef GL_OES_draw_texture
#ifdef DEBUG
        printf("Unsupport GL_OES_draw_texture extension...\n");
#endif
#else
        glPushMatrix();

        glShadeModel(GL_FLAT);//GL_SMOOTH,GL_FLAT
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_FOG);
        glEnable(GL_BLEND);
        glEnable(GL_DITHER);
        glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE); //GL_SRC_ALPHA

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, m_textureId);

        glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        glColor4f(1.0f, 0.0f, 0.0f, 0.0f);

        for (unsigned int i = 0; i < strlen(str); i++) {
            int index = (int)(str[i] - 32);
#if (defined(DEBUG) && defined(SHOW_FONT_POS))
            printf("str[%d]: %c, index: %d\n", i, str[i], index);
#endif
            GLint crop[4] = { 0, 0, m_charWidth, m_charHeight };

            int x_idx = index % m_colCount;
            int y_idx = (int)(index / m_colCount);
            crop[0] = x_idx * m_charWidth;
            crop[1] = (m_rowCount - y_idx) * m_charHeight;
#if (defined(DEBUG) && defined(SHOW_FONT_POS))
            printf("x_idx: %d, y_idx: %d, crop[0]: %d, crop[1]: %d\n", x_idx, y_idx, crop[0], crop[1]);
#endif

            glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_CROP_RECT_OES, crop);
            glDrawTexiOES(x + i * fontWidth, y, 0, fontWidth, fontHeight);
        }

        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
        glShadeModel(GL_SMOOTH);//GL_SMOOTH,GL_FLAT
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        glDisable(GL_DITHER);
#endif
    }

M3D_END_NAMESPACE
