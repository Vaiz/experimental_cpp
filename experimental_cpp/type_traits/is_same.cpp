#include "is_same.h"

using namespace experimental;

namespace {

static_assert(is_same_v<bool, bool>);
static_assert(!is_same_v<bool, int>);
static_assert(!is_same_v<const char*, int>);

static_assert(is_same_v<bool, is_same_t<bool, bool>>);
static_assert(is_same_v<int, is_same_t<int, int>>);
//is_same_t<const char*, int>; // compile error

}