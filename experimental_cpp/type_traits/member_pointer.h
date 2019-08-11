#pragma once

namespace experimental {

template <typename TClass, typename TMember, TMember TClass::*Pointer>
struct member_pointer_t {
    using value_type = TMember;
    using type = TMember TClass::*;
    static constexpr type value = Pointer;

	constexpr value_type& operator()(TClass& c) noexcept {
        return c.*value;
    }
    constexpr const value_type& operator()(const TClass& c) noexcept {
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
};

#define MEMBER_POINTER_T(class_name, member_name) member_pointer_t<class_name, decltype(class_name::member_name), &class_name::member_name>


void member_pointer_test();

}