#include "member_pointer.h"
#include <string>
#include <iostream>



namespace experimental {

namespace compile_time_check {
struct some_trivial_struct {
    int i;
    bool b;
};
using i_pointer = member_pointer_t<some_trivial_struct, int, &some_trivial_struct::i>;
constexpr auto i_pointer_v = member_pointer_v<some_trivial_struct, int, &some_trivial_struct::i>;
using b_pointer = member_pointer_t<some_trivial_struct, bool, &some_trivial_struct::b>;
constexpr auto b_pointer_v = member_pointer_v<some_trivial_struct, bool, &some_trivial_struct::b>;
using i_macro_pointer = MEMBER_POINTER_T(some_trivial_struct, i);

static_assert(std::is_same<i_pointer, i_macro_pointer>::value, "");

#ifdef __cpp17_enabled
static_assert(std::is_same<i_pointer, member_pointer_tt<&some_trivial_struct::i>>::value, "");
static_assert(std::is_same<b_pointer, member_pointer_tt<&some_trivial_struct::b>>::value, "");
static_assert(i_pointer_v == member_pointer_vv<&some_trivial_struct::i>, "");
static_assert(b_pointer_v == member_pointer_vv<&some_trivial_struct::b>, "");
#endif // __cpp17_enabled


static_assert(i_pointer::get(some_trivial_struct{ 1 }) == 1, "");
static_assert(i_pointer::get(some_trivial_struct{ 1 }) != 2, "");
static_assert(b_pointer::get(some_trivial_struct{ 1, true }), "");
static_assert(!b_pointer::get(some_trivial_struct{ 1, false }), "");
}

namespace {
struct some_struct {
    int i;
    double d;
    std::string s;
};
using i_pointer = member_pointer_t<some_struct, int, &some_struct::i>;
using d_pointer = member_pointer_t<some_struct, double, &some_struct::d>;
using s_pointer = member_pointer_t<some_struct, std::string, &some_struct::s>;
constexpr auto i_pointer_v = member_pointer_v<some_struct, int, &some_struct::i>;
static auto d_pointer_v = member_pointer_v<some_struct, double, &some_struct::d>;
static auto s_pointer_v = member_pointer_v<some_struct, std::string, &some_struct::s>;

}

void member_pointer_test() {
    std::cout << "Test " << __FILE__ << std::endl;
    some_struct s{ 10, 0.1, "1" };

    const auto& const_s = s;
    std::cout << i_pointer::get(const_s) << " " << d_pointer::get(const_s) << " " << s_pointer::get(const_s) << std::endl;
    i_pointer::get(s) = 20;
    d_pointer::get(s) = 0.2;
    s_pointer::get(s) = "2";
    std::cout << i_pointer::get(const_s) << " " << d_pointer::get(const_s) << " " << s_pointer::get(const_s) << std::endl;
    i_pointer::set(s, 30);
    d_pointer::set(s, 0.3);
    s_pointer::set(s, "3");
    std::cout << i_pointer::get(const_s) << " " << d_pointer::get(const_s) << " " << s_pointer::get(const_s) << std::endl;

    i_pointer_v.get(s) = 40; // operator () cause compile error if pointer is constexpr
    d_pointer_v(s) = 0.4;
    s_pointer_v(s) = "4";
    std::cout << i_pointer_v.get(const_s) << " " << d_pointer_v(const_s) << " " << s_pointer_v(const_s) << std::endl;
	
	s % i_pointer_v = 50;
    s % d_pointer_v = 0.5;
    s % s_pointer_v = "5";
    std::cout << const_s % i_pointer_v << " " << const_s % d_pointer_v << " " << const_s % s_pointer_v << std::endl;
}
}