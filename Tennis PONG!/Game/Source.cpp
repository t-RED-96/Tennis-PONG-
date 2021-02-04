#include "BitBool.h"

#define STB_IMAGE_IMPLEMENTATION
//
#include "Window.h"
#include "Entity.h"
#include "Mesh.h"
#include "Model.h"
#include "ShaderProgram.h"
//
#include <iostream>
#include <Windows.h>

Window _mainWindow;
//windows Dimensions
const GLint WIDTH = 800, HEIGHT = 600;
//Shaders
enum SHADER: unsigned char {
	COMMON,
	TOTAL,
};
ShaderProgram shaders[SHADER::TOTAL];
//Vertex shader
static const char* vShader = "               \n\
 #version 440                                \n\
                                             \n\
 layout (location = 0) in vec3 pos;          \n\
 layout (location = 1) in vec2 TexCoord;     \n\
 layout (location = 2) in vec3 Norml;        \n\
                                             \n\
 out vec2 texCoord;                          \n\
                                             \n\
 uniform mat4 model;                         \n\
                                             \n\
void main(){                                 \n\
    gl_Position = model * vec4(pos, 1.0);    \n\
    texCoord = TexCoord;					 \n\
}";

//fragment shader
static const char* fShader = "\n\
 #version 440                 \n\
                              \n\
 in vec2 texCoord;            \n\
 uniform sampler2D theTex;    \n\
 out vec4 color;              \n\
                              \n\
void main(){                  \n\
    color = texture(theTex, texCoord);  \n\
}";
#if 1
std::ostream& operator <<(std::ostream& cout, const glm::vec2& any) {
	cout << "glm::vec3( " << any.x << ", " << any.y << " )\n";
	return cout;
}
std::ostream& operator <<(std::ostream& cout, const glm::vec3& any) {
	cout << "glm::vec3( " << any.x << ", " << any.y << ", " << any.z << " )\n";
	return cout;
}
std::ostream& operator <<(std::ostream& cout, const glm::vec4& any) {
	cout << "glm::vec3( " << any.x << ", " << any.y << ", " << any.z << ", " << any.w << " )\n";
	return cout;
}
std::ostream& operator <<(std::ostream& cout, const glm::mat4& any) {
	cout << "glm::mat4---------------------";
	for (size_t y = 0;y < 4;y++) {
		cout << "\n";
		for (size_t x = 0;x < 4;cout << ", ", x++) {
			cout << any[y][x];
		}
	}
	cout << "\n------------------------------\n";
	return cout;
}
void SCENE1_ENTT1_RESET(Entity& _this) {
	_this.ChangeAllParams(glm::vec3(-0.5, 0, 0.4), glm::vec3(0, 1, 0), glm::vec3(0.005f));
}
void SCENE1_ENTT1_UPDATE(Entity& _this) {
	_this.Rotation(glm::vec3(sin((float)glfwGetTime() * 0.3f) * 20.0f));
}
void SCENE1_INIT(Scene& _this) {
	Entity& model1 = _this.AddEntity(glm::vec3(0), glm::vec3(0), glm::vec3(0));
	model1.AddModel("space_port_tunnel.obj");
	model1.AddScripts(SCENE1_ENTT1_RESET, SCENE1_ENTT1_UPDATE);

	Scene::ComponentCatalogue __this = _this.AllSceneComponentCatalogue();
	for (const Scripts& script : *(__this.allScripts)) {
		script.Reset();
	}
}
void SCENE1_UPDATE(Scene& __this) {
	Scene::ComponentCatalogue _this = __this.AllSceneComponentCatalogue();
	for (auto& script : *_this.allScripts) {
		script.Update();
	}
}
void SCENE1_RENDER(Scene& __this) {
	Scene::ComponentCatalogue _this = __this.AllSceneComponentCatalogue();
	
	shaders[SHADER::COMMON].Use();

	shaders[SHADER::COMMON].SetInt("theTex", 1);//Linking to texture unit 1

	for (auto& model : *_this.allModel) {
		shaders[SHADER::COMMON].SetMat4("model", model.Matrix());//unresolved externalsymbol because linker dosent know where to lnk to (as library of engine is not compiled)
		// i.e solve libraries problems
		model.RenderModel();
	}

	shaders[SHADER::COMMON].Stop();
}

#endif// Scene and oth miscellaneous funcs

void PrePare() {
	glfwPollEvents();
	// Clear the window
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
int main() {
	_mainWindow = Window(400, 400, "Test Engine");
	_mainWindow.Initialise();
	
	Scene Scene1(SCENE1_INIT, SCENE1_UPDATE, SCENE1_RENDER);

	shaders[SHADER::COMMON].CreateFromString(vShader, fShader);
	Scene1.Init();
	while (!_mainWindow.ShouldClose()) {
		
		PrePare();
    
		if (_mainWindow.getsKeys()[GLFW_KEY_ESCAPE])
			_mainWindow.CloseWindow(true), _mainWindow.getsKeys().Set(GLFW_KEY_ESCAPE,false);
		
		Scene1.Update();

		Scene1.Render();

		_mainWindow.swapBuffers();
		Sleep(10);
	}
    return 0;//_Main();
}