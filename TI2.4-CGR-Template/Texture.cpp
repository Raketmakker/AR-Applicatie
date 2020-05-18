#pragma once
#include "Texture.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string& fileName)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    stbi_set_flip_vertically_on_load(true);
    int width, height, comp;
    unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &comp, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
    glActiveTexture(id);
}
