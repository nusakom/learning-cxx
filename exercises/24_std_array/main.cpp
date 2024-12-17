#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}};
        // 确保数组大小正确
        ASSERT(arr.size() == 5, "Fill in the correct value.");
        // 确保数组总字节大小为 5 * sizeof(int) = 20
        ASSERT(sizeof(arr) == 20, "Fill in the correct value.");
        // 比较内存内容是否一致
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(arr.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
    }
    {
        std::array<double, 8> arr;
        // 确保数组大小为 8
        ASSERT(arr.size() == 8, "Fill in the correct value.");
        // 确保数组总字节大小为 8 * sizeof(double) = 64
        ASSERT(sizeof(arr) == 64, "Fill in the correct value.");
    }
    {
        std::array<char, 21> arr{"Hello, InfiniTensor!"};
        // 确保数组大小为 21（包括 '\0' 结束符）
        ASSERT(arr.size() == 21, "Fill in the correct value.");
        // 确保数组总字节大小为 21
        ASSERT(sizeof(arr) == 21, "Fill in the correct value.");
        // 使用 std::strcmp 进行字符串比较，确保字符串匹配
        ASSERT(std::strcmp(arr.data(), "Hello, InfiniTensor!") == 0, "Fill in the correct value.");
    }
    return 0;
    
}
