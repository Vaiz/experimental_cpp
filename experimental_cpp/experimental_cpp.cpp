#include <iostream>
#include "tuple/tuple_for_each.h"
#include "type_traits/member_pointer.h"

int main()
{
    std::cout << "Hello World!\n";
    experimental::tuple_iter_test();
    experimental::member_pointer_test();
}

