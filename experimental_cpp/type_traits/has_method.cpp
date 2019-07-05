#include "has_method.h"
#include <string>

using namespace experimental;

namespace {

struct StructWithoutMethod {};

static_assert(!has_method_to_str_v<StructWithoutMethod>);
static_assert(!has_method_to_str_ex_v<StructWithoutMethod>);
static_assert(!has_method_to_str_ex_ex_v<StructWithoutMethod, const char*>);


struct StructWithMethod {
    const char* to_str() const { return ""; }
};

static_assert(has_method_to_str_v<StructWithMethod>);
static_assert(has_method_to_str_ex_v<StructWithMethod>);
static_assert(has_method_to_str_ex_ex_v<StructWithMethod, const char*>);


struct StructWithStaticMethod {
    static const char* to_str() { return ""; }
};

static_assert(has_method_to_str_v<StructWithStaticMethod>);
static_assert(has_method_to_str_ex_v<StructWithStaticMethod>);
static_assert(has_method_to_str_ex_ex_v<StructWithStaticMethod, const char*>);


struct StructWithWrongMethod {
    int to_str() const { return 1; }
    const char* to_str(int) const { return ""; }
    const char* to_str(double) const = delete; // double -> int :(
    const char* to_str(int, std::string) const { return ""; }
};

static_assert(has_method_to_str_v<StructWithWrongMethod>);
static_assert(!has_method_to_str_ex_v<StructWithWrongMethod>);
static_assert(has_method_to_str_ex_v<StructWithWrongMethod, int>);

static_assert(!has_method_to_str_ex_ex_v<StructWithWrongMethod, const char*>);
static_assert(has_method_to_str_ex_ex_v<StructWithWrongMethod, const char*, int>);
static_assert(has_method_to_str_ex_ex_v<StructWithWrongMethod, const char*, bool>);    // :(
static_assert(!has_method_to_str_ex_ex_v<StructWithWrongMethod, const char*, double>); // :(
static_assert(!has_method_to_str_ex_ex_v<StructWithWrongMethod, const char*, std::string>);
static_assert(has_method_to_str_ex_ex_v<StructWithWrongMethod, const char*, int, std::string>);
static_assert(!has_method_to_str_ex_ex_v<StructWithWrongMethod, const char*, std::string, std::string>);


}