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
static const char* vShader = "../Shaders/vShader_common.glsl";
//fragment shader
static const char* fShader = "../Shaders/fShader_common.glsl";

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
void SCENE1_SUN_UPDATE(Entity& _this) {
	_this.Rotation(glm::vec3(/*45.0f*sin(glfwGetTime()*0.3f) + 90.0f*/0, 180.0f * sin(glfwGetTime()*0.5f) + 90.0f, 0));
}
Entity* model1 = NULL;
Entity* camera = NULL;
Entity* sun = NULL;
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
	//if (_mainWindow.getsKeys()[GLFW_KEY_W])
	//	_this.Position(_this.Position() + 0.1f * static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Front());
	//if (_mainWindow.getsKeys()[GLFW_KEY_S])
	//	_this.Position(_this.Position() - 0.1f * static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Front());
	//if (_mainWindow.getsKeys()[GLFW_KEY_D])
	//	_this.Position(_this.Position() + 0.1f * static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Right());
	//if (_mainWindow.getsKeys()[GLFW_KEY_A])
	//	_this.Position(_this.Position() - 0.1f * static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Right());
	//if (_mainWindow.getsKeys()[GLFW_KEY_UP])
	//	_this.Position(_this.Position() + 0.1f * static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Up());
	//if (_mainWindow.getsKeys()[GLFW_KEY_DOWN])
	//	_this.Position(_this.Position() - 0.1f * static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Up());

	//if (_mainWindow.getsKeys()[GLFW_KEY_SPACE])
	//	std::cout << _this.Rotation(), static_cast<Camera*>(_this.GetComponent(Camera::Typ))->LookAt(model1->Position()), std::cout << _this.Rotation() << "\n" << std::endl;//, _mainWindow.getsKeys().Set(GLFW_KEY_SPACE, false);
	_this.Position(model1->Position() - 20.0f*sun->Front());
	if (_mainWindow.getsKeys()[GLFW_KEY_LEFT_CONTROL]) {
		//__debugbreak();
		std::cout << _this.Rotation();
		static_cast<Camera*>(_this.GetComponent(Camera::Typ))->Follow(model1);
		std::cout << _this.Rotation() << "\n";
		_mainWindow.getsKeys().Set(GLFW_KEY_LEFT_CONTROL, false);
	}
}
void SCENE1_INIT(Scene& _this) {
	model1 = &_this.AddEntity(glm::vec3(0, 0, -10), glm::vec3(0, 1, 0), glm::vec3(0.02f));
	model1->AddModel("../Models/space_port_tunnel.obj").ChangeMaterial(256,0.02f);
	model1->AddScripts(SCENE1_ENTT1_RESET, SCENE1_ENTT1_UPDATE);
	
	camera = &_this.AddEntity(glm::vec3(0.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.0f));
	camera->AddCamera(90.0f, ((float)_mainWindow.GetBufferWidth() / (float)_mainWindow.GetBufferHeight()), 0.1f, 100.0f);
	camera->AddScripts(SCENE1_CAMERA_UPDATE);

	sun = &_this.AddEntity(glm::vec3(0.0f), glm::vec3(45.0f, 45.0f, 0.0f), glm::vec3(1.0f));
	sun->AddSun(glm::vec3(1, 1, 1), 0.05f, 0.3f);
	sun->AddScripts(SCENE1_SUN_UPDATE);
	
	//PrePare To Render
	Scene::ComponentCatalogue __this = _this.AllSceneComponentCatalogue();
	for (const Scripts& script : *(__this.allScripts)) {
		script.Reset();
	}

	//Initialize Locations
	Material::SetLocationsInShaderProg(shaders[SHADER::COMMON].getLoc("material.specular_Int"), shaders[SHADER::COMMON].getLoc("material.shininess"));
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
	shaders[SHADER::COMMON].SetVec3("eyePosition", _this.currCamera->Obj().Position());
	_this.mainLight->ApplyLight(shaders[SHADER::COMMON].getLoc("mainLight.base.color"), shaders[SHADER::COMMON].getLoc("mainLight.base.ambient_Int"), shaders[SHADER::COMMON].getLoc("mainLight.base.diffuse_Int"), shaders[SHADER::COMMON].getLoc("mainLight.direction"));
	
	shaders[SHADER::COMMON].SetInt("diffuse_Tex", 1);//Linking to texture unit 1
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
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
int main() {
	_mainWindow = Window(400, 400, "Test Engine");
	_mainWindow.Initialise();
	
	Scene Scene1(SCENE1_INIT, SCENE1_UPDATE, SCENE1_RENDER);

	shaders[SHADER::COMMON].CreateFromFiles(vShader, fShader);
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