#pragma once

#include "Setup.h"

namespace XEngine
{
	namespace pointermath
	{
		bool isAligned(const void* adress, uint8 alignmebt);

		template<class T>
		bool isAligned(const T* address);

		void* alignForward(void* adress, uint8 alignment);
		const void* alignForward(const void* adress, uint8 alignment);

		void* alignBack(void* adress, uint8 alignment);
		const void* alignBack(const void* address, uint8 alignment);

		uint8 alignAdd(const void* address, uint8 alignment);
		template<typename T>
		uint8 alignForwardHeader(const void *adress, uint8 alignment);

		void* add(void* p, size_t co);
		const void* add(const void* p, size_t co);

		void *substract(void* ad, size_t co);
		void *substract(const void* ad, size_t co);


		inline bool isAligned(const void* address, uint8 alignment)
		{
			return alignForwardAdjustment(address, alignment) == 0;
		}

		template<class T>
		inline bool isAligned(const T* address)
		{
			return alignForwardAdjustment(address, __alignof(T)) == 0;
		}

		inline void* alignForward(void* address, uint8 alignment)
		{
			return (void*)((reinterpret_cast<uint8>(address) + static_cast<uint8>(alignment - 1)) & static_cast<uint8>(~(alignment - 1)));
		}

		inline const void* alignForward(const void* address, uint8 alignment)
		{
			return (void*)((reinterpret_cast<uint8>(address) + static_cast<uint8>(alignment - 1)) & static_cast<uint8>(~(alignment - 1)));
		}

		inline void* alignBackward(void* address, uint8 alignment)
		{
			return (void*)(reinterpret_cast<uint8>(address)& static_cast<uint8>(~(alignment - 1)));
		}

		inline const void* alignBackward(const void* address, uint8 alignment)
		{
			return (void*)(reinterpret_cast<uint8>(address)& static_cast<uint8>(~(alignment - 1)));
		}

		inline uint8 alignForwardAdjustment(const void* address, uint8 alignment)
		{
			uint8 adjustment = alignment - (reinterpret_cast<uint8>(address)& static_cast<uint8>(alignment - 1));

			if (adjustment == alignment)
				return 0; //already aligned

			return adjustment;
		}
		/*
		inline u8 alignForwardAdjustmentWithHeader(const void* address, u8 alignment, u8 header_size)
		{
		u8 adjustment = alignForwardAdjustment(address, alignment);
		u8 needed_space = header_size;
		if(adjustment < needed_space)
		{
		needed_space -= adjustment;
		//Increase adjustment to fit header
		adjustment += alignment * (needed_space / alignment);
		if(needed_space % alignment > 0)
		adjustment += alignment;
		}
		return adjustment;
		}
		*/
		template<typename T>
		inline u8 alignForwardAdjustmentWithHeader(const void* address, u8 alignment)
		{
			if (__alignof(T) > alignment)
				alignment = __alignof(T);

			u8 adjustment = sizeof(T) + alignForwardAdjustment(pointer_math::add(address, sizeof(T)), alignment);

			return adjustment;
		}

		inline uint8 alignBackwardAdjustment(const void* address, uint8 alignment)
		{
			uint8 adjustment = reinterpret_cast<uint8>(address)& static_cast<uint8>(alignment - 1);

			if (adjustment == alignment)
				return 0; //already aligned

			return adjustment;
		}

		inline void* add(void* p, size_t x)
		{
			return (void*)(reinterpret_cast<uint8>(p) + x);
		}

		inline const void* add(const void* p, size_t x)
		{
			return (const void*)(reinterpret_cast<uint8>(p) + x);
		}

		inline void* subtract(void* p, size_t x)
		{
			return (void*)(reinterpret_cast<uint8>(p) - x);
		}

		inline const void* subtract(const void* p, size_t x)
		{
			return (const void*)(reinterpret_cast<uint8>(p) - x);
		}



	}
}