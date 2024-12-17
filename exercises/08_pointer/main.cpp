#include <iostream>
#include <cassert>

// 辅助宏定义：用于检查条件，如果不成立则报错
#define ASSERT(condition, message) \
    if (!(condition)) { \
        std::cerr << "Assertion failed: " << message << std::endl; \
        std::abort(); \
    }

bool is_fibonacci(int *ptr, int len, int stride) {
    ASSERT(len >= 3, "`len` should be at least 3");

    // 检查从 ptr 开始，每 stride 个元素取 1 个元素，是否符合斐波那契数列
    int i = 0;
    for (int count = 2; count < len; ++count) {
        // 打印调试信息，查看当前比较的元素
        std::cout << "Checking: " << ptr[i] << " + " << ptr[i + stride] 
                  << " == " << ptr[i + 2 * stride] << std::endl;

        if (ptr[i + 2 * stride] != ptr[i] + ptr[i + stride]) {
            return false;
        }
        i += stride;
    }
    return true;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    int arr0[]{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55},
        arr1[]{0, 1, 2, 3, 4, 5, 6},
        arr2[]{99, 98, 4, 1, 7, 2, 11, 3, 18, 5, 29, 8, 47, 13, 76, 21, 123, 34, 199, 55, 322, 0, 0};

    // clang-format off
    ASSERT( is_fibonacci(arr0    , sizeof(arr0) / sizeof(*arr0)    , 1),         "arr0 is Fibonacci"    );
    ASSERT( is_fibonacci(arr0 + 2, sizeof(arr0) / sizeof(*arr0) - 4, 1), "part of arr0 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr1    , sizeof(arr1) / sizeof(*arr1)    , 1),         "arr1 is not Fibonacci");
    ASSERT( is_fibonacci(arr1 + 1,  3                              , 1), "part of arr1 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr2    , sizeof(arr2) / sizeof(*arr2)    , 1),         "arr2 is not Fibonacci");
    ASSERT( is_fibonacci(arr2 + 2, 10                              , 2), "part of arr2 is Fibonacci"    );
    ASSERT( is_fibonacci(arr2 + 3,  9                              , 2), "part of arr2 is Fibonacci"    );
    ASSERT(!is_fibonacci(arr2 + 3, 10                              , 2), "guard check"                  );
    ASSERT(!is_fibonacci(arr2 + 1, 10                              , 2), "guard check"                  );
    // clang-format on

    return 0;
}
