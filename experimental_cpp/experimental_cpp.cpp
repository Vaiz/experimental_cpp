#include <iostream>
#include "tuple/tuple_for_each.h"
#include "type_traits/member_pointer.h"

int main() {
    std::cout << "__cplusplus   : " << __cplusplus << std::endl;
#ifdef _MSVC_LANG
    std::cout << "_MSVC_LANG    : " << _MSVC_LANG << std::endl;
#endif
    std::cout << "cpp14         : " << __if_cpp14_enabled("enabled", "disabled") << std::endl;
    std::cout << "cpp17         : " << __if_cpp17_enabled("enabled", "disabled") << std::endl;
    experimental::tuple_iter_test();
    experimental::member_pointer_test();
}
