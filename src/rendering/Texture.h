

#pragma once
#include <string>
#include <glad/glad.h>

class Texture
{
public:
    Texture();
    ~Texture();
    bool notLoaded;
    bool load(const std::string & file_name);
    
    void bind(int index = 0) const
    {
        
        //glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, to_id);
    }

    bool use_linear;

private:
    GLuint to_id;
};
