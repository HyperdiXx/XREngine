#pragma once

#ifndef _ALLOCCATOR_H
#define _ALLOCCATOR_H

#include "../pch/TypesSetup.h"

#include <cassert>

#include <new>


class Allocator
{
public:
	Allocator() {};
	Allocator(size_t size, void *align) : _align(align), _size(size), used_memory(0), _num_allocations(0) {}
	virtual ~Allocator()
	{
		assert(_num_allocations == 0 && used_memory == 0);
		_align = NULL;
		_size = NULL;
	}

	virtual void* allocate(size_t s, uint8 alignment = 4) = 0;
	virtual void deallocate(void* p) = 0;
	void* getStart() const { return _align; }
	size_t getSize() const { return _size; }
	size_t getUsedMemory() const { return used_memory; }
	size_t getNumAllocations() const { return _num_allocations; }

protected:
	void *_align;
	size_t _size;
	size_t used_memory;
	size_t _num_allocations;

};


namespace allocator
{
	template <class T, class... Args> 
	T* allocateNew(Allocator& alloc, Args &&... args)
	{
		return new (alloc.allocate(sizeof(T), __alignof(T))) T;
	}

	template <class T> 
	T* allocateNew(Allocator& alloc, const T& t)
	{
		return new (alloc.allocate(sizeof(T), __alignof(T))) T(t);
	}

	template <class T> 
	void deallocate(Allocator& alloc, T& obj)
	{
		obj.~T();
		alloc.deallocate(&obj);
	}

	template <class T> 
	T* allocatorArray(Allocator& alloc, size_t length)
	{
		assert(length != 0);
		uint8 hS = sizeof(size_t)/sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0) hS += 1;

		T* p = ((T*) alloc.allocate(sizeof(T) * (length + hS), __alignof(T)));

		*(((size_t*)p) - 1) = length;

		for (size_t i = 0; i < length; ++i)
		{
			new (&p) T;
		}
		return p;
	}


	template <class T> 
	void deallocateArray(Allocator& alloc, T* array1)
	{
		assert(array1 != 0);
		size_t length = *(((size_t*)array1) - 1);

		for (size_t i = 0; i < length; ++i)
			array1.~T();

		uint8 hS = sizeof(size_t) / sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0)
			hS += 1;
		alloc.deallocate(array1 - hS);
	}
}
#endif // !_ALLACCATOR_H

