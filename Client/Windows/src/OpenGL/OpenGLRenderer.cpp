#include "gv_pch.h"
#include "OpenGLRenderer.h"

#include <Glad/glad.h>
#include <GLFW/glfw3.h>

namespace GV {
	Ref<VertexBuffer> CreateVertexBuffer(uint32_t size, BufferDrawMode mode) {
		return createRef<OpenGLVertexBuffer>(size, mode);
	}
	Ref<VertexBuffer> CreateVertexBuffer(uint32_t size, float* vertices, BufferDrawMode mode) {
		return createRef<OpenGLVertexBuffer>(size, vertices, mode);
	}
	Ref<VertexBuffer> CreateVertexBuffer(uint32_t size, const void* data, BufferDrawMode mode) {
		return createRef<OpenGLVertexBuffer>(size, data, mode);
	}
	Ref<IndexBuffer> CreateIndexBuffer(uint32_t count, uint32_t* indices, BufferDrawMode mode) {
		return createRef<OpenGLIndexBuffer>(count, indices, mode);
	}
	Ref<UniformBuffer> CreateUniformBuffer(uint32_t size, uint32_t binding) {
		return createRef<OpenGLUniformBuffer>(size, binding);
	}
	Ref<ShaderStorageBuffer> CreateShaderStorageBuffer(uint32_t size, uint32_t bindingt, BufferDrawMode mode) {
		return createRef<OpenGLShaderStorageBuffer>(size, bindingt, mode);
	}
	Ref<VertexArray> CreateVertexArray() {
		return createRef<OpenGLVertexArray>();
	}
	Ref<Texture2D> CreateTexture(const std::string& path, const TextureSettings& settings) {
		return createRef<OpenGLTexture2D>(path, settings);
	}
	Ref<Texture2D> CreateTexture(uint32_t width, uint32_t height, const TextureSettings& settings) {
		return createRef<OpenGLTexture2D>(width, height, settings);
	}
	Ref<Shader> CreateShader(const std::string& name, const ShaderSource& sources) {
		return createRef<OpenGLShader>(name, sources);
	}
	Ref<Renderer> CreateRenderer() {
		return createRef<OpenGLRenderer>();
	}

	void glDebugCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum messageSeverity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
	{
		switch (messageSeverity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			GV_GFX_ERROR("{0}", message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			GV_GFX_WARN("{0}", message);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			GV_GFX_INFO("{0}", message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			GV_GFX_TRACE("{0}", message);
			break;
		default:
			break;
		}
	}
	OpenGLRenderer::OpenGLRenderer() {
		int32_t status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			GV_ASSERT_MSG(false, "Failed to initlized OpenGl");
		}
		GV_GFX_INFO("Loaded OpenGL {0}.{1}", GLVersion.major, GLVersion.minor);

#ifdef GV_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	void OpenGLRenderer::OnResize(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const {
		glViewport(x, y, width, height);
	}
	void OpenGLRenderer::SetWireFrame(bool value) const {
		glPolygonMode(GL_FRONT, value ? GL_LINE : GL_FILL);
		glPolygonMode(GL_BACK, value ? GL_LINE : GL_FILL);
	}
	void OpenGLRenderer::Clear(const glm::vec4& color) const {
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRenderer::Submit(const Ref<VertexArray>& vertexArray, uint32_t count, uint32_t instances) const {
		vertexArray->bind();
		uint32_t _count = count ? count : vertexArray->getIndexBuffer()->getCount();
		if (instances < 1)
			glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, nullptr);
		else
			glDrawElementsInstanced(GL_TRIANGLES, _count, GL_UNSIGNED_INT, nullptr, instances);
	}
}