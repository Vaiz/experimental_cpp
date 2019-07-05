#pragma once
#include <type_traits>

namespace experimental {

template <typename T, typename U>
constexpr bool is_same_v = std::is_same<T, U>::value;

template <typename T, typename U, typename ResultType = T>
using is_same_t = std::enable_if_t<is_same_v<T, U>, ResultType>;

}