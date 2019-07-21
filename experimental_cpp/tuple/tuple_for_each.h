#pragma once
#include <tuple>
#include <iostream>

namespace experimental {

template <size_t i, typename... T>
constexpr bool tuple_is_end_element_v = sizeof...(T) <= i;



template <size_t i, bool is_end_element, typename... T>
struct tuple_iterator;

template <size_t i, typename... T>
struct tuple_iterator<i, false, T...> {
    template <typename Functor>
    static void apply(Functor& f, const std::tuple<T...>& t) {
        f(std::get<i>(t));
        tuple_iterator<i + 1, tuple_is_end_element_v<i + 1, T...>, T...>::apply(f, t);
    }
};
template <size_t i, typename... T>
struct tuple_iterator<i, true, T...> {
    template <typename Functor>
    static void apply(Functor& f, const std::tuple<T...>& t) {
        // end loop
    }
};


template <typename Functor, typename... T>
void tuple_for_each(Functor& f, std::tuple<T...> t) {
    tuple_iterator<0, tuple_is_end_element_v<0, T...>, T...>::apply(f, t);
}



struct printer {
    template <typename T>
    void operator()(const T& t) {
        std::cout << t << std::endl;
    }
};

template <typename... T>
void tuple_print(std::tuple<T...> t) {
    printer p;
    tuple_for_each(p, t);
}

void tuple_iter_test();

}