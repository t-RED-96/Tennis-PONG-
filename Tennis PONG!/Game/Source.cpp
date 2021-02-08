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
 out vec3 fragPosn;                          \n\
                                             \n\
 uniform mat4 model;                         \n\
 uniform mat4 projViewMat;                   \n\
                                             \n\
void main(){                                 \n\
    gl_Position = projViewMat * model * vec4(pos, 1.0);    \n\
    texCoord = TexCoord;					 \n\
    fragPosn = vec3(pos.x*0.01,pos.y*0.01,pos.z*0.01);\n\
}";

//fragment shader
static const char* fShader = "\n\
 #version 440                 \n\
                              \n\
 in vec2 texCoord;            \n\
 in vec3 fragPosn;            \n\
 uniform sampler2D theTex;    \n\
 out vec4 color;              \n\
                              \n\
void main(){                  \n\
    color = vec4(fragPosn, 1.0);  \n\
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
			cout << any[x][y];
		}
	}

	cout << "\n--Matrix-is-transposed-for-humman-understanding--\n";
	return cout;
}
std::ostream& operator <<(std::ostream& cout, const glm::mat3& any) {
	cout << "glm::mat3---------------------";
	for (size_t y = 0;y < 3;y++) {
		cout << "\n";
		for (size_t x = 0;x < 3;cout << ", ", x++) {
			cout << any[x][y];
		}
	}
	
	cout << "\n-----Matrix-is-transposed------\n";
	return cout;
}
void SCENE1_ENTT1_RESET(Entity& _this) {
	_this.ChangeAllParams(glm::vec3(0, 0, 50), glm::vec3(0, 0, 0), glm::vec3(0.05f));
	std::cout << _this.Matrix();
}
Entity* model1 = NULL;
Entity* camera = NULL;
void SCENE1_ENTT1_UPDATE(Entity& _this) {
	if (_mainWindow.getsKeys()[GLFW_KEY_B])
		std::cout << _this.Front() << _this.Right() << _this.Up(),__debugbreak();
	if (_mainWindow.getsKeys()[GLFW_KEY_L])
		std::cout << _this.Front() << _this.Right() << _this.Up(), __debugbreak();
	if (_mainWindow.getsKeys()[GLFW_KEY_8])
		_this.Position(_this.Position() + 0.1f*_this.Front());
	if (_mainWindow.getsKeys()[GLFW_KEY_2])
		_this.Position(_this.Position() - 0.1f*_this.Front());
	if (_mainWindow.getsKeys()[GLFW_KEY_6])
		_this.Position(_this.Position() + 0.1f*_this.Right());
	if (_mainWindow.getsKeys()[GLFW_KEY_4])
		_this.Position(_this.Position() - 0.1f*_this.Right());
	if (_mainWindow.getsKeys()[GLFW_KEY_5])
		_this.Position(_this.Position() + 0.1f*_this.Up());
	
}
void SCENE1_CAMERA_UPDATE(Entity& _this) {
	if (_mainWindow.getsKeys()[GLFW_KEY_W])
		_this.Position(_this.Position() + 0.1f * static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Front());
	if (_mainWindow.getsKeys()[GLFW_KEY_S])
		_this.Position(_this.Position() - 0.1f * static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Front());
	if (_mainWindow.getsKeys()[GLFW_KEY_D])
		_this.Position(_this.Position() + 0.1f * static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Right());
	if (_mainWindow.getsKeys()[GLFW_KEY_A])
		_this.Position(_this.Position() - 0.1f * static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Right());
	if (_mainWindow.getsKeys()[GLFW_KEY_UP])
		_this.Position(_this.Position() + 0.1f * static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Up());
	if (_mainWindow.getsKeys()[GLFW_KEY_DOWN])
		_this.Position(_this.Position() - 0.1f * static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Up());

	if (_mainWindow.getsKeys()[GLFW_KEY_SPACE])
		std::cout << _this.Rotation(), static_cast<Camera*>(_this.GetComponent(Camera::Typ))->LookAt(model1->Position()), std::cout << _this.Rotation() << "\n" << std::endl;//, _mainWindow.getsKeys().Set(GLFW_KEY_SPACE, false);
	if (_mainWindow.getsKeys()[GLFW_KEY_LEFT_CONTROL])
		std::cout << _this.Rotation(), static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Follow(model1), std::cout << _this.Rotation()<<"\n", _mainWindow.getsKeys().Set(GLFW_KEY_LEFT_CONTROL, false);
}
void SCENE1_INIT(Scene& _this) {
	model1 = &_this.AddEntity(glm::vec3(0, 0, -10), glm::vec3(0, 1, 0), glm::vec3(0.02f));
	model1->AddModel("space_port_tunnel.obj");
	model1->AddScripts(SCENE1_ENTT1_RESET, SCENE1_ENTT1_UPDATE);

	camera = &_this.AddEntity(glm::vec3(0.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.0f));
	camera->AddCamera(90.0f, ((float)_mainWindow.GetBufferWidth() / (float)_mainWindow.GetBufferHeight()), 0.1f, 100.0f);
	camera->AddScripts(SCENE1_CAMERA_UPDATE);
	
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

	_this.currCamera->Update();
	// When toggeling camera call UpdateMatrix() internally not Update();

	//Change Matrix Update flag
	for (auto& entt : *_this.allEntity) {
		entt.Updated(false);
	}
}
void SCENE1_RENDER(Scene& __this) {
	Scene::ComponentCatalogue _this = __this.AllSceneComponentCatalogue();
	
	shaders[SHADER::COMMON].Use();

	shaders[SHADER::COMMON].SetInt("theTex", 1);//Linking to texture unit 1
	shaders[SHADER::COMMON].SetMat4("projViewMat", _this.currCamera->ProjectionViewMatrix());

	for (auto& model : *_this.allModel) {
		shaders[SHADER::COMMON].SetMat4("model", model.Matrix());
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
		_mainWindow.ResetKeys();
		Sleep(10);
	}
    return 0;//_Main();
}