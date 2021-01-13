#include "BitBool.h"

#define ENGINE 1
#include "Window.h"
#include "Mesh.h"
#define ENGINE 0

#include <iostream>
#include <Windows.h>

Window _mainWindow;
//windows Dimensions
const GLint WIDTH = 800, HEIGHT = 600;
Mesh* aMesh;
GLuint VAO, VBO, shader;

//Vertex shader
static const char* vShader = "               \n\
 #version 440                                \n\
                                             \n\
 layout (location = 0) in vec3 pos;          \n\
                                             \n\
void main(){                                 \n\
    gl_Position = vec4(pos.x,pos.y,pos.z,1); \n\
}";

//fragment shader
static const char* fShader = "\n\
 #version 440                 \n\
                              \n\
 out vec4 color;              \n\
                              \n\
void main(){                  \n\
    color = vec4(1,0,0,1);    \n\
}";
void RenderOnlyMesh(Mesh& mesh) {
    mesh.BindVAO();
    //glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, mesh.IndexCount() / 3);
    //glDisableVertexAttribArray(0);
    mesh.UnbindVAO();
}
void createQuad() {
    GLfloat vertices[] = {
        	-0.5f,0.5f,0,
        	-0.5f,-0.5f,0,
        	0.5f,-0.5f,0,
        	0.5f,-0.5f,0,
        	0.5f,0.5f,0,
        	-0.5f,0.5f,0,
        };
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);//bind
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//bind

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);//unbind
    glBindVertexArray(0);//unbind
}
void createQuadA() {
    float positions[] = {
            -0.5f,0.5f,0,
            -0.5f,-0.5f,0,
            0.5f,-0.5f,0,
            0.5f,-0.5f,0,
            0.5f,0.5f,0,
            -0.5f,0.5f,0,
    };
    aMesh = new Mesh(positions, (sizeof(positions) / sizeof(positions[0])));
}
void renderQuad() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);// 6 Vertex
    glBindVertexArray(0);
}
void renderQuadA() {
    RenderOnlyMesh(*aMesh);
}
void addShader(GLuint theProg, const char* shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLenth[1];
    codeLenth[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLenth);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        std::cout << "Error compiling" << shaderType << " shader\n" << eLog;
        return;
    }

    glAttachShader(theProg, theShader);
}
void compileShaders() {
    shader = glCreateProgram();
    if (!shader) {
        std::cout << "Shader program creation failed\n";
    }
    addShader(shader, vShader, GL_VERTEX_SHADER);
    addShader(shader, fShader, GL_FRAGMENT_SHADER);

    //DEBUG STUFF
    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        std::cout << "Error Linking Program\n" << eLog;
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        std::cout << "Error in shader code\n" << eLog;
        return;
    }
}
class A {
public :
    char temp;
    A() { temp = 0; }
    A(char q) { temp = q; }
};
class B:public A {
public:
    B():A() {}
    B(char q):A(q) {}
};
int main() {
	_mainWindow = Window(400, 400, "Test Engine");
	_mainWindow.Initialise();
	float positions[] = {
		-0.5f,0.5f,0,
		-0.5f,-0.5f,0,
		0.5f,-0.5f,0,
		0.5f,-0.5f,0,
		0.5f,0.5f,0,
		-0.5f,0.5f,0,
	};
    createQuadA();
    compileShaders();

    A *a;
    B b('a');
    a = (A*)(&b);
    std::cout << a->temp;
	while (!_mainWindow.ShouldClose()) {
		glfwPollEvents();
		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
		if (_mainWindow.getsKeys()[GLFW_KEY_ESCAPE])
			_mainWindow.CloseWindow(true), _mainWindow.getsKeys().Set(GLFW_KEY_ESCAPE,false);
		if (_mainWindow.getsKeys()[GLFW_KEY_BACKSPACE])
			_mainWindow.CloseWindow(false), _mainWindow.getsKeys().Set(GLFW_KEY_BACKSPACE, false);
    
        glUseProgram(shader);
        renderQuadA();
        glUseProgram(0);
    
		_mainWindow.swapBuffers();
		Sleep(10);
	}
    return 0;//_Main();
}