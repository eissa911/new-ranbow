#pragma once

#include <cstdint>
#include <type_traits>

namespace Engine {
	class Memory {
	public:
		template <typename Type, typename Base, typename Offset>
		static inline Type Ptr(Base base, Offset offset) {
			static_assert(std::is_pointer<Type>::value || std::is_integral<Type>::value, "*/*E*/*R*/*R*/*O*/*R*/*1");
			static_assert(std::is_pointer<Base>::value || std::is_integral<Base>::value, "*/*E*/*R*/*R*/*O*/*R*/* 2*/*");
			static_assert(std::is_pointer<Offset>::value || std::is_integral<Offset>::value, "*/*E*/*R*/*R*/*O*/*R*/* 3*/*");

			return base ? reinterpret_cast<Type>((reinterpret_cast<uint64_t>(base) + static_cast<uint64_t>(offset))) : nullptr;
		}

		template <typename Type>
		static bool IsValidPtr(Type* ptr) {
			return (ptr && sizeof(ptr)) ? true : false;
		}

		static bool IsValidPtr(void* ptr) {
			return (ptr && sizeof(ptr)) ? true : false;
		}
	};
}