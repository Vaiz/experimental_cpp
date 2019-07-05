#pragma once
#include <type_traits>
#include "is_same.h"

namespace experimental {

template <typename T, typename = std::void_t<T>>
struct has_method_to_str : std::false_type {};

template <typename T>
struct has_method_to_str<T, std::void_t<decltype(T().to_str())>> : std::true_type {};

template <typename T>
constexpr bool has_method_to_str_v = has_method_to_str<T>::value;


template <typename T, typename TReturnType = const char*, typename = std::void_t<T>>
struct has_method_to_str_ex : std::false_type {};

template <typename T, typename TReturnType>
struct has_method_to_str_ex<T, TReturnType, std::void_t<is_same_t<decltype(T().to_str()), TReturnType>>> : std::true_type {};

template <typename T, typename TReturnType = const char*>
constexpr bool has_method_to_str_ex_v = has_method_to_str_ex<T, TReturnType>::value;

}