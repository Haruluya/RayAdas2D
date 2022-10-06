#pragma once

#include <memory>
#include "rendering/Buffer.h"

namespace RayAdas {

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const SRef<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const SRef<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<SRef<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const SRef<IndexBuffer>& GetIndexBuffer() const = 0;

		static SRef<VertexArray> Create();
	};

}