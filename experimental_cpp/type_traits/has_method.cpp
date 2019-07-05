#include "has_method.h"

using namespace experimental;

namespace {

struct StructWithoutMethod {};

static_assert(!has_method_to_str_v<StructWithoutMethod>);
static_assert(!has_method_to_str_ex_v<StructWithoutMethod>);


struct StructWithMethod {
    const char* to_str() const { return ""; }
};

static_assert(has_method_to_str_v<StructWithMethod>);
static_assert(has_method_to_str_ex_v<StructWithMethod>);


struct StructWithStaticMethod {
    static const char* to_str() { return ""; }
};

static_assert(has_method_to_str_v<StructWithStaticMethod>);
static_assert(has_method_to_str_ex_v<StructWithStaticMethod>);


struct StructWithWrongMethod {
    int to_str() const { return 1; }
};

static_assert(has_method_to_str_v<StructWithWrongMethod>);
static_assert(!has_method_to_str_ex_v<StructWithWrongMethod>);
static_assert(has_method_to_str_ex_v<StructWithWrongMethod, int>);

}