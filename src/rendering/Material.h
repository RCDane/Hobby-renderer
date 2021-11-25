#include "Shader.h"
#include "Texture.h"
class Material{
public:
    Material(Shader* shader,Texture *albedo, Texture *metalness, float shininess);
    void PrepareShader();
    void BindParameters();
    Shader* GetShader();
private:
    Shader *shader;
    Texture* diffuse, *specular;
    float shininess;
};