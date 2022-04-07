#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<math.h>
#include "util.h"

unsigned int program;

float color[8][4];
float scale = 0.5f;

GLint colorLoc[8];
GLint scaleLoc;

float currentTime = 0.0f;
float lastTime = 0.0f;
float deltaTime = 0.0f;

float counter = 0;

void randomColor() {
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 4; i++) {
            color[j][i] = (rand() * 1.0f) / RAND_MAX;
        }
        glUniform4f(colorLoc[j], color[j][0], color[j][1], color[j][2], color[j][3]);
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        randomColor();
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        scale -= 0.1f;
        glUniform1f(scaleLoc, scale);
    }
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        scale += 0.1f;
        glUniform1f(scaleLoc, scale);
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Project UTS", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);

    GLenum err = glewInit();

    const float pi = 2 * acos(0.0);

    float vertices[18];
    int index = 2;
    float x, y;

    //determine the center of octagon
    vertices[0] = 0;
    vertices[1] = 0;

    //determine the vertices of octagon-shape
    for (float i = 0; i < (7 * pi) / 4; i += (pi / 4)) {
        x = sin(i);
        vertices[index] = x;
        index++;

        y = cos(i);
        vertices[index] = y;
        index++;
    };

    unsigned int indexArr[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 7,
        0, 7, 8,
        0, 8, 1
    };

    randomColor();

    unsigned int vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 9, vertices, GL_STATIC_DRAW);

    unsigned int indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3 * 8, indexArr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexChar, NULL);
    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glUseProgram(program);

    scaleLoc = glGetUniformLocation(program, "scale");
    glUniform1f(scaleLoc, scale);
    //glProgramUniform1f(program, scaleLoc, scale);

    for (int i = 0; i < 8; i++) {
        string iStr = "colors[" + to_string(i) + "]";
        colorLoc[i] = glGetUniformLocation(program, iStr.c_str());
        glUniform4f(colorLoc[i], color[i][0], color[i][1], color[i][2], color[i][3]);
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        counter += deltaTime;
        if (counter >= 1.0f) {
            counter = 0.0f;
            randomColor();
        }

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}