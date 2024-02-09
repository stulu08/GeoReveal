#include "gv_pch.h"

#include <GeoReveal/World/World.h>
#include <GeoReveal/Renderer/Renderer.h>
#include <spdlog/stopwatch.h>

#include <GLFW/glfw3.h>

void glfwErrorCallback(int32_t error, const char* msg) {
	GV_ERROR("GLFW error {0}: {1}", error, msg);
}

GLFWwindow* CreateGLFWWindow(uint32_t width, uint32_t height, const std::string& title) {
	GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
	return window;
}

void InitMain() {
	GV::Log::Init();
	GV_ASSERT(glfwInit());

#ifdef GV_DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwSetErrorCallback(glfwErrorCallback);
}

void Test() {
	GV::World world;
	GV::Log::Info("Max world size with depth {0}: {1:.2f}GB", GV::MAX_TREE_DEPTH, world.MaxSize() * 1e-9);
	GV::Log::Info("Min degree with depth {0}: {1}~{2}m", GV::MAX_TREE_DEPTH, world.MinDegree(), world.MinDegree() / 111111);
	spdlog::stopwatch sw;

	sw.reset();
	world.Explore({ 45.01237f, 55.12324f });
	GV::Log::Info("Exploring empty: {0:.7f}s", sw);

	sw.reset();
	world.Explore({ 45.01537f, 55.16324f });
	GV::Log::Info("Exploring allocated: {0:.7f}s", sw);

	sw.reset();
	bool value = world.IsExplored({ 45.01537f, 55.16324f });
	GV::Log::Info("Lookup explored({1}): {0:.7f}s", sw, value);
}

void AppLoop() {
	InitMain();
	Test();

	GLFWwindow* window = CreateGLFWWindow(1280, 720, "GeoReveal");

	auto renderer = GV::CreateRenderer();

	float vertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,	1.0f, 0.0f,
	};
	uint32_t indices[] = {
		0,1,2,
		2,3,0
	};

	auto vertexBuffer = GV::CreateVertexBuffer(sizeof(vertices), vertices);
	auto indexBuffer = GV::CreateIndexBuffer(sizeof(indices) / sizeof(uint32_t), indices);

	auto vertexArray = GV::CreateVertexArray();
	vertexBuffer->setLayout({
		{GV::ShaderDataType::Float3, "Pos"},
		{GV::ShaderDataType::Float2, "UV"}
		});
	vertexArray->addVertexBuffer(vertexBuffer);
	vertexArray->setIndexBuffer(indexBuffer);

	GV::ShaderSource shaderSource;
	shaderSource.Add(GV::ShaderType::Vertex, R"(
#version 460 core
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_uv;

out vec2 u_uv;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_transform;

void main() {
	u_uv = a_uv;
	gl_Position =  u_projection * u_view * u_transform * vec4(a_pos, 1.0);
}
)");
	shaderSource.Add(GV::ShaderType::Fragment, R"(
#version 460 core
out vec4 a_color;

in vec2 u_uv;

layout(binding = 0) uniform sampler2D u_texture;
layout(binding = 1) uniform sampler2D u_fog;

void main() {
	a_color = texture2D(u_texture, u_uv).rgba;
	a_color += texture2D(u_fog, u_uv).rgba;
}
)");

	auto shader = GV::CreateShader("Default", shaderSource);

	GV::TextureSettings settings;
	settings.filtering = GV::TextureFiltering::Linear;

	auto texture = GV::CreateTexture(360, 180, settings);
	auto fogTexture = GV::CreateTexture(360, 180, settings);

	glm::vec3 camPos = { 0.0f,0.0f,133.0f };
	glm::quat camRot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	float time = (float)glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		int32_t width, height;
		glfwGetWindowSize(window, &width, &height);
		float aspect = (float)width / (float)height;
		float delta = 0.0f;
		{
			float last = time;
			time = (float)glfwGetTime();
			delta = time - last;
		}
		

		renderer->OnResize(0, 0, width, height);
		renderer->Clear({ 0.2f, 0.3f, 0.3f, 1.0f });
		
		{
			glm::mat4 projection = glm::perspective(glm::radians(85.0f), aspect, 0.01f, 1000.0f);
			glm::mat4 view = glm::translate(glm::mat4(1.0f), camPos) * glm::mat4_cast(camRot);
			glm::mat4 transform = glm::scale(glm::mat4(1.0f), { 360.0f, 180.0f, 1.0f });

			texture->bind(0);
			fogTexture->bind(1);

			shader->bind();
			shader->setMat("u_projection", projection);
			shader->setMat("u_view", glm::inverse(view));
			shader->setMat("u_transform", transform);

			float speed = 4.0f * delta;
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
				speed *= 10;
			}
			if (glfwGetKey(window, GLFW_KEY_W)) {
				camPos.z -= speed;
			}
			if (glfwGetKey(window, GLFW_KEY_S)) {
				camPos.z += speed;
			}
			if (glfwGetKey(window, GLFW_KEY_A)) {
				camPos.x -= speed;
			}
			if (glfwGetKey(window, GLFW_KEY_D)) {
				camPos.x += speed;
			}
			if (glfwGetKey(window, GLFW_KEY_Q)) {
				camPos.y -= speed;
			}
			if (glfwGetKey(window, GLFW_KEY_E)) {
				camPos.y += speed;
			}
		}

		renderer->Submit(vertexArray);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}



#ifdef GV_DIST
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
	AppLoop();
	return 0;
}
#else
int main() {
	AppLoop();
	return 0;
}
#endif