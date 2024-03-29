#pragma once
#include "GeoReveal/Renderer/Shader.h"

typedef unsigned int GLenum;

namespace GV {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const ShaderSource& sources);
		virtual ~OpenGLShader();

		virtual void reload(const ShaderSource& sources) override;
		virtual void reload(const std::string& vertex, const std::string& fragment) override { reload(ShaderSource{ vertex, fragment }); }
		virtual void reload(const std::string& compute) override { reload(ShaderSource{ compute }); } 

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void Dispatch(const glm::uvec3& numWorkGroups = { 1u,1u,1u }, uint32_t usage = 0xFFFFFFFF) override;
		virtual void Dispatch(const uint32_t numWorkGroupsX, const uint32_t numWorkGroupsY, const uint32_t numWorkGroupsZ, uint32_t usage = 0xFFFFFFFF) override {
			Dispatch({ numWorkGroupsX ,numWorkGroupsY,numWorkGroupsZ }, usage);
		}

		virtual void setFloat(const std::string& name, float value) override;
		virtual void setInt(const std::string& name, int value) override;
		virtual void setVec(const std::string& name, const glm::vec4& value) override;
		virtual void setMat(const std::string& name, const glm::mat4& value) override;
		virtual void setFloatArray(const std::string& name, const float* floats, uint32_t count) override;
		virtual void setIntArray(const std::string& name, const int* ints, uint32_t count) override;
		virtual void setVecArray(const std::string& name, const glm::vec4* vecs, uint32_t count) override;
		virtual void setMatArray(const std::string& name, const glm::mat4* mats, uint32_t count) override;

		virtual void setTexture(const std::string& name, uint32_t binding, const Ref<Texture>& texture, uint32_t mipLevel = 0, AccesMode mode = AccesMode::ReadWrite) override;
		virtual void setTextureInternal(const std::string& name, uint32_t binding, void* texture, uint32_t mipLevel = 0, AccesMode mode = AccesMode::ReadWrite, TextureFormat format = TextureFormat::Auto) override;

		virtual const std::string& getName() const override { return m_name; }
		virtual const void* getNativeRendererObject() const override { return &m_rendererID; };
	private:
		uint32_t m_rendererID;
		std::string m_name;

		void compile(const ShaderSource& sources);
	};
}

