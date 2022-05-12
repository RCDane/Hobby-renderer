

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
#include "rendering/Camera.h"
GLFWwindow* window;
const int WINDOW_WIDTH  = 1024;
const int WINDOW_HEIGHT = 768;

Model   * mesh    = nullptr;
Shader  * shader  = nullptr;
Texture * texture = nullptr;
/* Matrices */
glm::vec3 cam_position = glm::vec3(0.0f, 0.0f, -1.2f);
glm::vec3 cam_look_at  = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cam_up       = glm::vec3(0.0f, 1.0f, 0.0f);
Camera cam = Camera(cam_look_at, cam_position, cam_up);


glm::mat4 world_matrix      = glm::rotate(glm::mat4(1.0f),3.14f, glm::vec3(0, 1, 0));
glm::mat4 view_matrix       = glm::lookAt(cam_position, cam_look_at, cam_up);
glm::mat4 projection_matrix = glm::perspectiveFov(glm::radians(60.0f), float(WINDOW_WIDTH), float(WINDOW_HEIGHT), 0.1f, 10.0f);

float rho = 0.0f;
float phi = 0.0f;

double oldx = 0;
double oldy = 0;
double newx = 0;
double newy = 0;
bool rightMouseDown = false;
float gameTime = 0.0f;


static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    oldx = newx;
    oldy = newy;
    newx = xpos;
    newy =ypos;
    
    if(rightMouseDown)
    {
        float diffx = newx - oldx;
        float diffy = newy - oldy;
        cam.MouseRotate(diffx, diffy,gameTime);
        shader->setUniformMatrix4fv("view", cam.GetCamera());
    }
}
void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    projection_matrix = glm::perspectiveFov(glm::radians(60.0f), float(width), float(height), 0.1f, 10.0f);
    
    if (shader != nullptr)
    {
        shader->setUniformMatrix4fv("viewProj", projection_matrix * cam.GetCamera());
    }
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        rightMouseDown = true;
    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        rightMouseDown = false;

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
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
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
    mesh = new Model("res/models/sponza/sponza");
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
    // lights.Bind(shader);
    cam = Camera(cam_look_at, cam_position, cam_up);

    shader->apply();
    lights.Bind(shader);
    
    shader->setUniformMatrix4fv("view", cam.GetCamera());
    shader->setUniformMatrix4fv("projection", projection_matrix );
    
    // Setting directional light direction
     shader->setUniform3fv("dirLight.direction",glm::vec3( 1.f, -1.0f,1.0f));
     shader->setUniform3fv("dirLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
    
     shader->setUniform3fv("dirLight.diffuse", glm::vec3(1.f, 1.f, 1.f));
     shader->setUniform3fv("dirLight.specular", glm::vec3(0.f, 0.f, 0.f));
 
    // shader->setUniform3fv("viewPos", cam.GetPosition());

    texture = new Texture();

     texture->load("res/models/Stanford/grey.png");
    texture->bind();
    Material *mat = new Material(shader, texture, texture, 1);
    GameObject gameObj = GameObject(mesh,mat, glm::vec3(0.,0.,0.), glm::vec3(1.), glm::vec3(1.,1.,1.));
    gameObjects.push_back(gameObj);
    /*GameObject gameObj2 = GameObject(mesh,mat, glm::vec3(1.,1.,0.), glm::vec3(1.), glm::vec3(1.,1.,1.));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j <10; j++) {
            glm::vec3 pos = glm::vec3(i * 0.5-2., j * 1-3., 0.);
            gameObjects.push_back(GameObject(mesh, mat, pos, glm::vec3(1.), glm::vec3(1., 1., 1.)* 0.3f));
        }
    }*/

    return true;
}

void render(float time)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glm::vec3 pos = glm::vec3(cos(time),0, sin(time));
    
    shader->apply();
    //texture->bind();
    // LineDrawer lineDrawer = LineDrawer();
    for (int i = 0; i < gameObjects.size(); i++){
        gameObjects[i].Render();
        gameObjects[i].RenderAABB(view_matrix, projection_matrix);
    }
        
}
int horizontal = 0;
int vertical = 0;
void UpdateCameraInput(int key, bool press){
    horizontal += ((key == GLFW_KEY_A) * -1
                 + (key == GLFW_KEY_D) * 1) * (press ? 1 : -1 );
    vertical += ((key == GLFW_KEY_S) * -1 
                 + (key == GLFW_KEY_W) * 1) * (press ? 1 : -1 );
    
}








void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_A || key ==  GLFW_KEY_S || key == GLFW_KEY_W || key == GLFW_KEY_D)
    {
        if (action == GLFW_PRESS){
            UpdateCameraInput(key,true);
        }
        else if (action == GLFW_RELEASE){
            UpdateCameraInput(key, false);
        }
    }
    
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
        cam.MoveCamera(vertical,horizontal,gameTime);
        shader->setUniformMatrix4fv("view", cam.GetCamera());
        
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

