#pragma once

#if __cplusplus >= 201402L || _MSVC_LANG >= 201402L
#define __cpp14_enabled
#define __if_cpp14_enabled(true_value, false_value) true_value
#else 
#define __if_cpp14_enabled(true_value, false_value) false_value
#endif

#if __cplusplus >= 201703L || _MSVC_LANG >= 201703L
#define __cpp17_enabled
#define __if_cpp17_enabled(true_value, false_value) true_value
#else
#define __if_cpp17_enabled(true_value, false_value) false_value
#endif
