
#include <stb_image.h>

#include "Texture.h"
#include <iostream>
#include <helpers/RootDir.h>
int new_to = 0;

Texture::Texture()
    : use_linear(true)
{
    notLoaded = true;
}
Texture::~Texture()
{
    
    glDeleteTextures(1, &to_id);
    to_id = 0;
}

bool Texture::load(const std::string & file_name)
{
    if(file_name.empty())
    {
        return false;
    }

    bool is_loaded = false;
    int width, height, components;
    
    unsigned char* pixels = stbi_load((file_name).c_str(), &width, &height, &components, 4);
    if(pixels != nullptr)
    {
        GLuint id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        
        

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        glGenerateMipmap(GL_TEXTURE_2D);

        is_loaded = true;
        this->to_id = id;
    }
    else
    {
        std::cout << "Could not load file " << file_name << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(pixels);
    notLoaded = false;
    return is_loaded;
}


