#include "../exercise.h"
#include <string>
#include <type_traits>
#include <cassert>  // 确保包含 assert

// READ: 字符串 <https://zh.cppreference.com/w/cpp/string/basic_string>

int main(int argc, char **argv) {
    // READ: 字符串字面量 <https://zh.cppreference.com/w/cpp/string/basic_string/operator%22%22s>
    using namespace std::string_literals;
    auto hello = "Hello"s;  // 这将是 std::string 类型
    auto world = "world";   // 这将是 const char* 类型
    
    // READ: `decltype` 表达式 <https://zh.cppreference.com/w/cpp/language/decltype>
    // READ: `std::is_same_v` 元编程判别 <https://zh.cppreference.com/w/cpp/types/is_same>
    assert((std::is_same_v<decltype(hello), std::string>));  // 用 assert 替换 ASSERT
    assert((std::is_same_v<decltype(world), const char*>));  // 用 assert 替换 ASSERT
    
    // 正确拼接字符串
    assert((hello + ", " + std::string(world) + '!') == "Hello, world!");  // 用 assert 替换 ASSERT
    
    return 0;
}
