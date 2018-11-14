#pragma once

#ifndef _LINEAR_ALLOC
#define _LINEAR_ALLOC

#include "Allocator.h"

namespace XAllocator
{
	class LinearAllocator : public Allocator
	{
	public:
		LinearAllocator(size_t size, void* start);
		~LinearAllocator();

		void* allocate(size_t s, uint8 aling);
		void dealloc(void* a);
		void clear();


	private:
		LinearAllocator(const LinearAllocator& obj);
		LinearAllocator & operator=(const LinearAllocator&);
	private:
		void* currpos;
	};

}

#endif // !_LINEAR_ALLOC


