#include "self.h"

namespace experimental {
namespace {

struct TestStruct {
    ADD_SELF_TYPEDEF
};
static_assert(std::is_same_v<TestStruct, TestStruct::Self>, "");

}
}