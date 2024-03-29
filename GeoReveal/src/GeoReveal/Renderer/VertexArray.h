#pragma once
#include "Buffer.h"

namespace GV {
	struct Vertex {
		glm::vec3 pos = glm::vec3(.0f);
		glm::vec3 normal = glm::vec3(.0f, 1.0f, .0f);
		glm::vec2 texCoords = glm::vec3(.0f);
		glm::vec4 color = glm::vec4(1.0f);
	};

	class VertexArray {
	public:
		virtual ~VertexArray() = default;

		virtual void addVertexBuffer(const Ref<VertexBuffer>& vBuffer) = 0;
		virtual void clearVertexBuffers() = 0;
		virtual void setIndexBuffer(const Ref<IndexBuffer>& iBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& getIndexBuffer() const = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
	};
}