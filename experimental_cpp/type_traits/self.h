#pragma once
#include <type_traits>

namespace experimental {

#define ADD_SELF_TYPEDEF                          \
    template <typename T>                         \
    static T _self_type_return_fn(void (T::*)()); \
    void _self_helper_fn();                       \
    using Self = decltype(_self_type_return_fn(&_self_helper_fn));

}
