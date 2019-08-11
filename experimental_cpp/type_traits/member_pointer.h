#pragma once
#include <stddef.h>
#include "cpp_version.h"

namespace experimental {

template <typename TClass, typename TMember, TMember TClass::*Pointer>
struct member_pointer_t {
    using class_type = TClass;
    using value_type = TMember;
    using type = TMember TClass::*;
    static constexpr type value = Pointer;

    constexpr value_type& operator()(TClass& c) noexcept {
        return c.*value;
    }
    constexpr const value_type& operator()(const TClass& c) noexcept {
        return c.*value;
    }
    friend constexpr bool operator==(const member_pointer_t&, const member_pointer_t&) { return true; }

    friend constexpr value_type& operator%(class_type& c, const member_pointer_t&) {
        return c.*value;
    }
    friend constexpr const value_type& operator%(const class_type& c, const member_pointer_t&) {
        return c.*value;
    }

    static constexpr value_type& get(TClass& c) noexcept {
        return c.*value;
    }
    static constexpr const value_type& get(const TClass& c) noexcept {
        return c.*value;
    }
    static constexpr value_type& set(TClass& c, value_type v) noexcept {
        c.*value = std::move(v);
        return c.*value;
    }
    static constexpr std::ptrdiff_t get_offset() noexcept {
        return reinterpret_cast<std::ptrdiff_t>(&(*reinterpret_cast<class_type*>(nullptr).*value));
    }
};

template <typename TClass, typename TMember, TMember TClass::*Pointer>
constexpr auto member_pointer_v = member_pointer_t<TClass, TMember, Pointer>{}; //

#define MEMBER_POINTER_T(class_name, member_name) member_pointer_t<class_name, decltype(class_name::member_name), &class_name::member_name>
#define MEMBER_POINTER_V(class_name, member_name) member_pointer_v<class_name, decltype(class_name::member_name), &class_name::member_name>

namespace member_pointer_details {
template <typename T>
struct detect_type;

template <typename TClass, typename TMember>
struct detect_type<TMember TClass::*> {
    using class_type = TClass;
    using value_type = TMember;
    using type = TMember TClass::*;
};
}

#ifdef __cpp17_enabled
template <auto Pointer>
using member_pointer_tt = member_pointer_t<
    typename member_pointer_details::detect_type<decltype(Pointer)>::class_type,
    typename member_pointer_details::detect_type<decltype(Pointer)>::value_type,
    Pointer>;

template <auto Pointer>
constexpr auto member_pointer_vv = member_pointer_tt<Pointer>{};
#endif


void member_pointer_test();

}