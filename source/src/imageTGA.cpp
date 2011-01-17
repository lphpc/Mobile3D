
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "imageTGA.h"


M3D_BEGIN_NAMESPACE

ImageTGA::ImageTGA() {
}

ImageTGA::~ImageTGA() {
}


Texture *ImageTGA::loadTexture(const char * filename)				/* Load a TGA file */
{
	Texture *texture = NULL;
	GLubyte uTGAcompare[12] = {0,0,2, 0,0,0,0,0,0,0,0,0};   /* Uncompressed TGA Header */
	GLubyte cTGAcompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};   /* Compressed TGA Header */

	FILE * fTGA;													/* File pointer to texture file */
	fTGA = fopen(filename, "rb");									/* Open file for reading */

	if(fTGA == NULL)												/* If it didn't open.... */
	{
		printf("Error could not open texture file");				/* Display an error message */
		return NULL;												/* Exit function */
	}

	if(fread(&tgaheader, sizeof(TGAHeader), 1, fTGA) == 0)			/* Attempt to read 12 byte header from file */
	{
		printf("Error could not read file header");					/* If it fails, display an error message */
		if(fTGA != NULL)												/* Check to seeiffile is still open */
		{
			fclose(fTGA);												/* If it is, close it */
		}
		return NULL;													/* Exit function */
	}

	if(memcmp(uTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)	/* See if header matches the predefined header of */
	{																/* an Uncompressed TGA image */
		texture = LoadUncompressedTGA(filename, fTGA);					/* If so, jump to Uncompressed TGA loading code */
	}
	else if(memcmp(cTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)	/* See if header matches the predefined header of */
	{																	/* an RLE compressed TGA image */
		texture = LoadCompressedTGA(filename, fTGA);						/* If so, jump to Compressed TGA loading code */
	}
	else																/* If header matches neither type */
	{
		printf("Error TGA file be type 2 or type 10 ");				/* Display an error */
		fclose(fTGA);
		return NULL;												/* Exit function */
	}
	return texture;														/* All went well, continue on */
}

Texture* ImageTGA::LoadUncompressedTGA(const char * filename, FILE * fTGA)	/* Load an uncompressed TGA (note, much of this code is based on NeHe's */
{
	Texture *texture = NULL;
	GLuint  type;
	GLubyte * imageData = NULL;

	GLuint cswap;															/* TGA Loading code nehe.gamedev.net) */
	if(fread(tga.header, sizeof(tga.header), 1, fTGA) == 0)				/* Read TGA header */
	{
		printf("Error could not read info header");							/* Display error */
		if(fTGA != NULL)													/* if file is still open */
		{
			fclose(fTGA);													/* Close it */
		}
		return NULL;														/* Return failular */
	}

	tga.Width  = tga.header[1] * 256 + tga.header[0];					/* Determine The TGA Width	(highbyte*256+lowbyte) */
	tga.Height = tga.header[3] * 256 + tga.header[2];					/* Determine The TGA Height	(highbyte*256+lowbyte) */
	tga.Bpp	= tga.header[4];										/* Determine the bits per pixel */

	if((tga.Width <= 0) || (tga.Height <= 0) || ((tga.Bpp != 24) && (tga.Bpp !=32)))	/* Make sure all information is valid */
	{
		printf("Error invalid texture information");						/* Display Error */
		if(fTGA != NULL)													/* Check if file is still open */
		{
			fclose(fTGA);													/* If so, close it */
		}
		return NULL;														/* Return failed */
	}

    texture = (Texture *) malloc(sizeof(Texture));
	m_width = tga.Width;
	m_height = tga.Height;
	texture->width = m_width;
	texture->height = m_height;


	if(tga.Bpp == 24)													/* If the BPP of the image is 24... */
	{
		type = GL_RGB;											/* Set Image type to GL_RGB */
	}
	else																	/* Else if its 32 BPP */
	{
		type = GL_RGBA;											/* Set image type to GL_RGBA */
	}

	tga.bytesPerPixel	= (tga.Bpp / 8);									/* Compute the number of BYTES per pixel */
	tga.imageSize		= (tga.bytesPerPixel * tga.Width * tga.Height);		/* Compute the total amout ofmemory needed to store data */
	imageData	= (GLubyte*)malloc(tga.imageSize);							/* Allocate that much memory */

	if(imageData == NULL)											/* If no space was allocated */
	{
		printf("Error could not allocate memory for image");				/* Display Error */
		fclose(fTGA);														/* Close the file */
		return NULL;														/* Return failed */
	}

	if(fread(imageData, 1, tga.imageSize, fTGA) != tga.imageSize)	/* Attempt to read image data */
	{
		printf("Error could not read image data");							/* Display Error */
		if(imageData != NULL)										/* If imagedata has data in it */
		{
			free(imageData);										/* Delete data from memory */
		}
		fclose(fTGA);														/* Close file */
		return NULL;														/* Return failed */
	}

	/* Byte Swapping Optimized By Steve Thomas */
	for(cswap = 0; cswap < (int)tga.imageSize; cswap += tga.bytesPerPixel)
	{
		imageData[cswap] ^= imageData[cswap+2] ^=
		imageData[cswap] ^= imageData[cswap+2];
	}


	glGenTextures(1, &(texture->textureId));
    glBindTexture(GL_TEXTURE_2D, texture->textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, type, m_width, m_height, 0, type, GL_UNSIGNED_BYTE, imageData);

    FREEANDNULL(imageData);


	fclose(fTGA);															/* Close file */
	return texture;															/* Return success */
}

Texture* ImageTGA::LoadCompressedTGA(const char * filename, FILE * fTGA)		/* Load COMPRESSED TGAs */
{
	return NULL;																		/* return success */
}


M3D_END_NAMESPACE
