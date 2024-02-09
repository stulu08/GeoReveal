#pragma once
#include "GeoReveal/Renderer/Renderer.h"

#include "OpenGLBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include "OpenGLVertexArray.h"

namespace GV {
	class OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer();

		virtual void OnResize(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const override;

		virtual void SetWireFrame(bool value) const override;
		virtual void Clear(const glm::vec4& color) const override;

		virtual void Submit(const Ref<VertexArray>& vertexArray, uint32_t count = 0, uint32_t instances = 0) const override;
	};
}
