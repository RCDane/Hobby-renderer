

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "rendering/Lights.h"
#define  GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include <stdlib.h>
#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "rendering/Model.h"
#include "rendering/GameObject.h"
GLFWwindow* window;
const int WINDOW_WIDTH  = 1024;
const int WINDOW_HEIGHT = 768;

Model   * mesh    = nullptr;
Shader  * shader  = nullptr;
Texture * texture = nullptr;

/* Matrices */
glm::vec3 cam_position = glm::vec3(0.0f, 1.0f, -1.2f);
glm::vec3 cam_look_at  = glm::vec3(0.0f, 0.5f, 0.0f);
glm::vec3 cam_up       = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 world_matrix      = glm::rotate(glm::mat4(1.0f),3.14f, glm::vec3(0, 1, 0));
glm::mat4 view_matrix       = glm::lookAt(cam_position, cam_look_at, cam_up);
glm::mat4 projection_matrix = glm::perspectiveFov(glm::radians(60.0f), float(WINDOW_WIDTH), float(WINDOW_HEIGHT), 0.1f, 10.0f);

float rho = 0.0f;
float phi = 0.0f;

void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    projection_matrix = glm::perspectiveFov(glm::radians(60.0f), float(width), float(height), 0.1f, 10.0f);
    
    if (shader != nullptr)
    {
        shader->setUniformMatrix4fv("viewProj", projection_matrix * view_matrix);
    }
}

int init()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Modern GL!", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetWindowSizeCallback(window, window_size_callback);

    /* Initialize glad */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* Set the viewport */
    glClearColor(0.6784f, 0.8f, 1.0f, 1.0f);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glEnable(GL_DEPTH_TEST);

    return true;
}
std::vector<GameObject> gameObjects;

int loadContent()
{
    mesh = new Model("res/models/alliance.obj");
    struct Light l1 = {glm::vec3(1.0f,.0f,-1.0f),
                      1.0f,
                      0.09f,
                      0.032f,
                      glm::vec3(0.0f, 0.0f, 0.0f),
                      glm::vec3(0.9f, 0.f, 0.f),
                      glm::vec3(.0f, .0f, .0f)};
    struct Light l2 = { glm::vec3(.0f,1.0f,-1.0f),
                      1.0f,
                      0.09f,
                      0.032f,
                      glm::vec3(0.0f, 0.0f, 0.0f),
                      glm::vec3(0.0f, 0.4f, 0.0f),
                      glm::vec3(.0f, .0f, .0f) };
    struct Light l3 = { glm::vec3(-1.0f,.0f,1.0f),
                      1.0f,
                      0.09f,
                      0.032f,
                      glm::vec3(0.0f, 0.0f, 0.0f),
                      glm::vec3(0.0f, 0.0f, 0.9f),
                      glm::vec3(.0f, .0f, .0f) };
    Lights lights(3);
    lights.Add(l1);
    lights.Add(l2);
    lights.Add(l3);
     /* Create and apply basic shader */
    shader = new Shader("multiple_lights.vert", "multiple_lights.frag");
    lights.Bind(shader);
    shader->apply();

    
    shader->setUniformMatrix4fv("view", view_matrix);
    shader->setUniformMatrix4fv("projection", projection_matrix );
    // Setting directional light direction
    shader->setUniform3fv("dirLight.direction",glm::vec3( 1.f, -1.0f,1.0f));
    shader->setUniform3fv("dirLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
    
    shader->setUniform3fv("dirLight.diffuse", glm::vec3(1.f, 1.f, 1.f));
    shader->setUniform3fv("dirLight.specular", glm::vec3(0.f, 0.f, 0.f));
 
    shader->setUniform3fv("viewPos", cam_position);
    cam_look_at = glm::normalize(cam_look_at - cam_position);

    texture = new Texture();
    texture->load("res/models/alliance.png");
    texture->bind();
    Material *mat = new Material(shader, texture, texture, 1);
    GameObject gameObj = GameObject(mesh,mat, glm::vec3(0.,0.,0.), glm::vec3(1.), glm::vec3(1.,1.,1.));
    GameObject gameObj2 = GameObject(mesh,mat, glm::vec3(1.,1.,0.), glm::vec3(1.), glm::vec3(1.,1.,1.));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j <10; j++) {
            glm::vec3 pos = glm::vec3(i * 0.5-2., j * 1-3., 0.);
            gameObjects.push_back(GameObject(mesh, mat, pos, glm::vec3(1.), glm::vec3(1., 1., 1.)* 0.3f));
        }
    }

    return true;
}

void render(float time)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
    glm::vec3 pos = glm::vec3(cos(time),0, sin(time));
    

    shader->apply();
    texture->bind();
    // LineDrawer lineDrawer = LineDrawer();
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i].Render();
        // gameObjects[i].RenderAABB(view_matrix,projection_matrix);
        
    }
        // gameObjects[5].Render();
        // gameObjects[5].RenderAABB(view_matrix,projection_matrix);
    //mesh->Draw();
}
float gameTime = 0.0f;

void UpdateCamera(int key){
    if(key == GLFW_KEY_A) {
        cam_position = cam_position + glm::normalize(-glm::cross(cam_look_at, cam_up))*gameTime * 0.03f;
    }
    if(key == GLFW_KEY_D) {
        cam_position = cam_position + glm::normalize(glm::cross(cam_look_at-cam_position, cam_up)) * gameTime * 0.03f;;
    }
    if(key == GLFW_KEY_W) {
        cam_position = cam_position + glm::normalize(cam_look_at-cam_position)*gameTime* 0.03f;
    }
    if(key == GLFW_KEY_S) {
        cam_position = cam_position - glm::normalize(cam_look_at-cam_position)*gameTime* 0.03f;
    }
    std::cout <<  glm::to_string(cam_position) << std::endl;

    view_matrix      = glm::lookAt(cam_position, cam_position + cam_look_at, cam_up);

    shader->setUniformMatrix4fv("view", view_matrix);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_A || key ==  GLFW_KEY_S || key == GLFW_KEY_W || key == GLFW_KEY_D)
        UpdateCamera(key);

}

void update()
{
    float startTime = static_cast<float>(glfwGetTime());
    float newTime  = 0.0f;
    gameTime = 0.0f;
    glfwSetKeyCallback(window, key_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Update game time value */
        newTime  = static_cast<float>(glfwGetTime());
        gameTime = newTime - startTime;
        /* Render here */
        render(gameTime);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

int main(void)
{
    if (!init())
        return -1;

    if (!loadContent())
        return -1;

    update();

    glfwTerminate();

    delete mesh;
    delete shader;
    delete texture;

    return 0;
}

