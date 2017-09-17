#include<iostream>

#include "../include/glad/glad.h"
#include "glfw3.h"

#include "../include/core/Particle.h"
#include "../include/core/Spring.h"

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const unsigned int NUM_MASSES = 20;

const float ROPE_START = 0.0f;

Particle* masses[NUM_MASSES];
Spring* springs[NUM_MASSES - 1];
float positions[NUM_MASSES  * 3];

void setupWorld();

void update();

void windowResizeCallback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow* window);

int main()
{
    setupWorld();

    masses[0]->lock();
    masses[NUM_MASSES - 1]->lock();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create 'GLFW' window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, windowResizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR: VERTEX SHADER COMPILATION FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR: FRAGMENT SHADER COMPILATION FAILED\n" << infoLog << std::endl;
    }

    unsigned int shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR: FAILED TO LINK 'SHADERS' TOGETHER\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while(!(glfwWindowShouldClose(window)))
    {
        update();
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);

        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);
        glBindVertexArray(VAO);
        glPointSize(4.0f);
        glDrawArrays(GL_POINTS, 0, NUM_MASSES);
        glDrawArrays(GL_LINE_STRIP, 0, NUM_MASSES);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void setupWorld()
{
    for(int i = 0; i < NUM_MASSES; ++i)
    {
        masses[i] = new Particle(0.1f, Vector3D(ROPE_START + (0.05f * i), 0.5f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f),
                                     Vector3D(0.0f, 0.0f, 0.0f));

        positions[(i * 3)] = masses[(i * 3) / 3]->getPosition()._x;
        positions[(i * 3) + 1] = masses[(i * 3) / 3]->getPosition()._y;
        positions[(i * 3) + 2] = masses[(i * 3) / 3]->getPosition()._z;

    }

    for(int i = 0; i < NUM_MASSES - 1; ++i)
    {
        springs[i] = new Spring(19620.0f, 30.0f, 0.05f, masses[i], masses[i + 1]);
    }
}

void update()
{
    for(int i = 0; i < NUM_MASSES; ++i)
    {
        masses[i]->applyForce(Vector3D(0.0f, -9.81f, 0.0f));
        masses[i]->applyForce(masses[i]->getVelocity() * -0.3f); // Apply Drag
    }

    for(int i = 0; i < NUM_MASSES - 1; ++i)
    {
        springs[i]->simulate(0.0016f);
    }

    for(int i = 0; i < NUM_MASSES * 3; i+=3)
    {
        positions[i] = masses[i / 3]->getPosition()._x;
        positions[i + 1] = masses[i / 3]->getPosition()._y;
        positions[i + 2] = masses[i / 3]->getPosition()._z;
    }
}

void windowResizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        masses[NUM_MASSES - 1]->unlock();
    }
    else if(glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
    {
        masses[NUM_MASSES - 1]->lock();
    }
    else if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        masses[NUM_MASSES - 1]->applyForce(Vector3D(100.0f, 0.0f, 0.0f));
    }
}