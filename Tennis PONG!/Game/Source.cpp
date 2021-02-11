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
 out vec2 pass_texCoord;                     \n\
 out vec3 pass_fragPosn;                     \n\
 out vec3 pass_normal;                       \n\
                                             \n\
 uniform mat4 model;                         \n\
 uniform mat4 projViewMat;                   \n\
                                             \n\
void main(){                                 \n\
    vec4 World_Posn = model * vec4(pos, 1.0);\n\
                                             \n\
    gl_Position = projViewMat * World_Posn;  \n\
    pass_texCoord = TexCoord;                \n\
    pass_fragPosn = vec3(World_Posn);                     \n\
    pass_normal = mat3(transpose(inverse(model))) * Norml;\n\
}";

//fragment shader
static const char* fShader = " \n\
 #version 440                  \n\
                               \n\
 in vec2 pass_texCoord;        \n\
 in vec3 pass_fragPosn;        \n\
 in vec3 pass_normal;          \n\
                               \n\
 struct Light{                 \n\
    vec3 color;                \n\
    float ambient_Int;         \n\
    float diffuse_Int;         \n\
 };                            \n\
 struct DirectionalLight{      \n\
    Light base;                \n\
    vec3 direction;            \n\
 };                            \n\
                               \n\
 uniform sampler2D diffuse_Tex;       \n\
 uniform DirectionalLight mainLight;  \n\
                               \n\
 out vec4 out_color;           \n\
                               \n\
vec3 CalcLightColorByDirn(Light light,vec3 dirn){           \n\
    float factor_amb = light.ambient_Int;                   \n\
    float factor_diff = max(dot(pass_normal, dirn), 0.0f);  \n\
    factor_diff *= light.diffuse_Int;                       \n\
                                                            \n\
    return light.color*(factor_amb + factor_diff);          \n\
}                                                           \n\
                               \n\
vec4 CalcColorByDirnlLight(){                                                       \n\
    return vec4( CalcLightColorByDirn( mainLight.base, mainLight.direction), 1.0);  \n\
}                                                                                    \n\
                               \n\
void main(){                   \n\
    vec4 finalColour = CalcColorByDirnlLight();                     \n\
    out_color = texture(diffuse_Tex, pass_texCoord) * finalColour;  \n\
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
void SCENE1_SUN_UPDATE(Entity& _this) {
	_this.Rotation(glm::vec3(45.0f*sin(glfwGetTime()*0.3f) + 90.0f, 45.0f * sin(glfwGetTime() * 0.6f) + 90.0f, 0));
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
	model1->AddModel("space_port_tunnel.obj");
	model1->AddScripts(SCENE1_ENTT1_RESET, SCENE1_ENTT1_UPDATE);

	camera = &_this.AddEntity(glm::vec3(0.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(1.0f));
	camera->AddCamera(90.0f, ((float)_mainWindow.GetBufferWidth() / (float)_mainWindow.GetBufferHeight()), 0.1f, 100.0f);
	camera->AddScripts(SCENE1_CAMERA_UPDATE);

	Entity& Sun = _this.AddEntity(glm::vec3(0.0f), glm::vec3(45.0f, 45.0f, 0.0f), glm::vec3(1.0f));
	Sun.AddSun(glm::vec3(1, 1, 1), 0.1f, 0.6f);
	Sun.AddScripts(SCENE1_SUN_UPDATE);
	
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
		//Sleep(10);
	}
    return 0;//_Main();
}