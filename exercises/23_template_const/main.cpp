#include "../exercise.h"
#include <cstring>
#include <cassert>  // 确保包含 assert

template<unsigned int N, class T>
struct Tensor {
    unsigned int shape[N];
    T *data;

    Tensor(unsigned int const shape_[N]) {
        unsigned int size = 1;
        // 填入正确的 shape 并计算 size
        std::memcpy(shape, shape_, N * sizeof(unsigned int));
        for (unsigned int i = 0; i < N; ++i) {
            size *= shape[i];
        }

        data = new T[size];
        std::memset(data, 0, size * sizeof(T));
    }

    ~Tensor() {
        delete[] data;
    }

    // 禁止复制和移动
    Tensor(Tensor const &) = delete;
    Tensor(Tensor &&) noexcept = delete;

    T &operator[](unsigned int const indices[N]) {
        return data[data_index(indices)];
    }

    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];
    }

private:
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        unsigned int multiplier = 1;
        // 从最后一个维度开始计算索引
        for (unsigned int i = N; i-- > 0; ) {
            assert(indices[i] < shape[i] && "Invalid index");
            index += indices[i] * multiplier;
            multiplier *= shape[i];  // 更新 multiplier 用于处理前一个维度
        }
        return index;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{2, 3, 4, 5};
        auto tensor = Tensor<4, int>(shape);

        unsigned int i0[]{0, 0, 0, 0};
        tensor[i0] = 1;
        assert(tensor[i0] == 1 && "tensor[i0] should be 1");
        assert(tensor.data[0] == 1 && "tensor[i0] should be 1");

        unsigned int i1[]{1, 2, 3, 4};
        tensor[i1] = 2;
        assert(tensor[i1] == 2 && "tensor[i1] should be 2");
        assert(tensor.data[119] == 2 && "tensor[i1] should be 2");
    }
    {
        unsigned int shape[]{7, 8, 128};
        auto tensor = Tensor<3, float>(shape);

        unsigned int i0[]{0, 0, 0};
        tensor[i0] = 1.f;
        assert(tensor[i0] == 1.f && "tensor[i0] should be 1");
        assert(tensor.data[0] == 1.f && "tensor[i0] should be 1");

        unsigned int i1[]{3, 4, 99};
        tensor[i1] = 2.f;
        assert(tensor[i1] == 2.f && "tensor[i1] should be 2");
        assert(tensor.data[3683] == 2.f && "tensor[i1] should be 2");
    }
    return 0;
}
