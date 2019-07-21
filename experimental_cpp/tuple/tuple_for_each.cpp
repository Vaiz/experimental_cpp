#include "tuple_for_each.h"

namespace experimental {

void tuple_iter_test() {
    std::cout << "Test " << __FILE__ << std::endl;
    tuple_print(std::make_tuple(1, -2, "aaa", 3.));
}

}