#pragma once

#ifndef _LINEAR_ALLOC
#define _LINEAR_ALLOC

#include "Allocator.h"

namespace XEngine
{
	class LinearAllocator : public Allocator
	{
	public:
		LinearAllocator(size_t size, void* start);



	private:
		LinearAllocator(const LinearAllocator& obj);


	};

}

#endif // !_LINEAR_ALLOC


