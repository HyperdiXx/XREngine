#include "LinearAllocator.h"

XAllocator::LinearAllocator::LinearAllocator(size_t size, void * start) : Allocator(size, start), currpos(start)
{
	assert(size > 0);
}

XAllocator::LinearAllocator::~LinearAllocator()
{
	currpos = NULL;
}

void * XAllocator::LinearAllocator::allocate(size_t s, uint8 aling)
{
	assert(s != 0);



	return nullptr;
}

void XAllocator::LinearAllocator::dealloc(void * a)
{

}

void XAllocator::LinearAllocator::clear()
{


}

