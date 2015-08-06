#pragma once
#include "AddTexture.h"

void AddTextura(Texture* txt)
{
     glEnable(GL_TEXTURE_2D);
	 glGenTextures(1, &txt->texID);
     glBindTexture(GL_TEXTURE_2D, txt->texID);
     gluBuild2DMipmaps(GL_TEXTURE_2D, txt->bpp / 8, txt->width, txt->height, txt->type, 
                      GL_UNSIGNED_BYTE, txt->imageData);		
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	 glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

	

	 
}

    