#pragma once

#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

namespace GV {
	Ref<VertexBuffer> CreateVertexBuffer(uint32_t size, BufferDrawMode mode = BufferDrawMode::Dynamic);
	Ref<VertexBuffer> CreateVertexBuffer(uint32_t size, float* vertices, BufferDrawMode mode = BufferDrawMode::Static);
	Ref<VertexBuffer> CreateVertexBuffer(uint32_t size, const void* data, BufferDrawMode mode = BufferDrawMode::Static);
	Ref<IndexBuffer> CreateIndexBuffer(uint32_t count, uint32_t* indices, BufferDrawMode mode = BufferDrawMode::Dynamic);
	Ref<UniformBuffer> CreateUniformBuffer(uint32_t size, uint32_t binding);
	Ref<ShaderStorageBuffer> CreateShaderStorageBuffer(uint32_t size, uint32_t bindingt, BufferDrawMode mode = BufferDrawMode::Dynamic);

	Ref<VertexArray> CreateVertexArray();

	Ref<Texture2D> CreateTexture(const std::string& path, const TextureSettings& settings = TextureSettings());
	Ref<Texture2D> CreateTexture(uint32_t width, uint32_t height, const TextureSettings& settings = TextureSettings());

	Ref<Shader> CreateShader(const std::string& name, const ShaderSource& sources);


	class Renderer {
	public:
		virtual void OnResize(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const = 0;

		virtual void SetWireFrame(bool value) const = 0;
		virtual void Clear(const glm::vec4& color) const = 0;

		virtual void Submit(const Ref<VertexArray>& vertexArray, uint32_t count = 0, uint32_t instances = 0) const = 0;
	};

	Ref<Renderer> CreateRenderer();
}