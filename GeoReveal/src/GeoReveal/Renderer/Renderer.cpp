#include "gv_pch.h"
#include "Renderer.h"

namespace GV {
	extern Ref<VertexBuffer> CreateVertexBuffer(uint32_t size, BufferDrawMode mode);
	extern Ref<VertexBuffer> CreateVertexBuffer(uint32_t size, float* vertices, BufferDrawMode mode);
	extern Ref<VertexBuffer> CreateVertexBuffer(uint32_t size, const void* data, BufferDrawMode mode);
	extern Ref<IndexBuffer> CreateIndexBuffer(uint32_t count, uint32_t* indices, BufferDrawMode mode);
	extern Ref<UniformBuffer> CreateUniformBuffer(uint32_t size, uint32_t binding);
	extern Ref<ShaderStorageBuffer> CreateShaderStorageBuffer(uint32_t size, uint32_t bindingt, BufferDrawMode mode);

	extern Ref<VertexArray> CreateVertexArray();

	extern Ref<Texture2D> CreateTexture(const std::string& path, const TextureSettings& settings);
	extern Ref<Texture2D> CreateTexture(uint32_t width, uint32_t height, const TextureSettings& settings);

	extern Ref<Shader> CreateShader(const std::string& name, const ShaderSource& sources);
	extern Ref<Shader> CreateShader(const std::string& name, const std::string& vertex, const std::string& fragment) { return CreateShader(name, ShaderSource{ vertex, fragment }); }
	extern Ref<Shader> CreateShader(const std::string& name, const std::string& compute) { return CreateShader(name, ShaderSource{ compute }); }
	
	extern Ref<Renderer> CreateRenderer();
}