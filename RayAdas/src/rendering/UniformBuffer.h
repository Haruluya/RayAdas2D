#pragma once

#include "utils/Base.h"

namespace RayAdas {

	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() {}
		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) = 0;

		static SRef<UniformBuffer> Create(uint32_t size, uint32_t binding);
	};

}