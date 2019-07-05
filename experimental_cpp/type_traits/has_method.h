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
struct has_method_to_str_ex<T, TReturnType, std::void_t<is_same_t<TReturnType, decltype(T().to_str())>>> : std::true_type {};

template <typename T, typename TReturnType = const char*>
constexpr bool has_method_to_str_ex_v = has_method_to_str_ex<T, TReturnType>::value;


// still don't know how to pass method name :D
template <typename T, typename TReturnType, typename... TMethodArgs>
struct has_method_to_str_ex_ex : std::false_type {};

// pass return type twice to fix C2764 : template parameter not used or deducible in partial specialization 'specialization'
template <typename T, typename TReturnType, typename... TMethodArgs>
struct has_method_to_str_ex_ex<T, TReturnType, is_same_t<TReturnType, decltype(T().to_str(std::declval<TMethodArgs>()...))>, TMethodArgs...> : std::true_type {};

template <typename T, typename TReturnType, typename... TMethodArgs>
constexpr bool has_method_to_str_ex_ex_v = has_method_to_str_ex_ex<T, TReturnType, TReturnType, TMethodArgs...>::value;

}