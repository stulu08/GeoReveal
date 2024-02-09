#include "gv_pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace GV {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case GV::ShaderDataType::Float:		return GL_FLOAT;
		case GV::ShaderDataType::Float2:		return GL_FLOAT;
		case GV::ShaderDataType::Float3:		return GL_FLOAT;
		case GV::ShaderDataType::Float4:		return GL_FLOAT;
		case GV::ShaderDataType::Int:		return GL_INT;
		case GV::ShaderDataType::Int2:		return GL_INT;
		case GV::ShaderDataType::Int3:		return GL_INT;
		case GV::ShaderDataType::Int4:		return GL_INT;
		case GV::ShaderDataType::Mat3:		return GL_FLOAT;
		case GV::ShaderDataType::Mat4:		return GL_FLOAT;
		case GV::ShaderDataType::Bool:		return GL_INT;
		case GV::ShaderDataType::Sampler:	return GL_INT;
		}
		GV_ASSERT_MSG(false, "Uknown ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_rendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_rendererID);
	}

	void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vBuffer) {
		GV_ASSERT_MSG(vBuffer->getLayout().getElements().size(), "Vertexbuffer has no layout");
		glBindVertexArray(m_rendererID);
		vBuffer->bind();
		const auto& layout = vBuffer->getLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(m_vertexbufferIndex);
			glVertexAttribPointer(
				m_vertexbufferIndex, element.getComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(), (const void*)(intptr_t)element.offset
			);
			m_vertexbufferIndex++;
		}
		m_vertexBufffers.push_back(vBuffer);
	}

	void OpenGLVertexArray::clearVertexBuffers() {
		glBindVertexArray(m_rendererID);
		for (auto& vb : m_vertexBufffers) {
			vb->unbind();
		}
		m_vertexbufferIndex = 0;
		m_vertexBufffers.clear();
	}

	void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& iBuffer) {
		glBindVertexArray(m_rendererID);
		iBuffer->bind();
		m_indexBuffer = iBuffer;
	}

	void OpenGLVertexArray::bind() const {
		glBindVertexArray(m_rendererID);
	}

	void OpenGLVertexArray::unbind() const {
		glBindVertexArray(0);
	}
}
