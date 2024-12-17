#include "../exercise.h"
#include <cstring>
#include <stdexcept>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    // 构造函数
    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        for (int i = 0; i < 4; ++i) {
            shape[i] = shape_[i];
        }
        for (int i = 0; i < 4; ++i) {
            size *= shape[i];
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    // 析构函数
    ~Tensor4D() {
        delete[] data;
    }

    // 禁止复制和移动构造函数
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 处理广播加法
    Tensor4D &operator+=(Tensor4D const &others) {
        // 检查形状是否可以广播
        for (int i = 0; i < 4; ++i) {
            if (others.shape[i] != 1 && others.shape[i] != shape[i]) {
                throw std::invalid_argument("Shapes are not compatible for broadcasting");
            }
        }

        unsigned int this_index[4] = {0};
        unsigned int others_index[4] = {0};
        
        // 逐个维度进行加法运算
        for (unsigned int i = 0; i < shape[0]; ++i) {
            this_index[0] = i;
            others_index[0] = (others.shape[0] == 1) ? 0 : i;
            for (unsigned int j = 0; j < shape[1]; ++j) {
                this_index[1] = j;
                others_index[1] = (others.shape[1] == 1) ? 0 : j;
                for (unsigned int k = 0; k < shape[2]; ++k) {
                    this_index[2] = k;
                    others_index[2] = (others.shape[2] == 1) ? 0 : k;
                    for (unsigned int l = 0; l < shape[3]; ++l) {
                        this_index[3] = l;
                        others_index[3] = (others.shape[3] == 1) ? 0 : l;

                        // 计算扁平化的索引
                        unsigned int this_flat_index = ((this_index[0] * shape[1] + this_index[1]) * shape[2] + this_index[2]) * shape[3] + this_index[3];
                        unsigned int others_flat_index = ((others_index[0] * others.shape[1] + others_index[1]) * others.shape[2] + others_index[2]) * others.shape[3] + others_index[3];

                        // 执行加法
                        data[this_flat_index] += others.data[others_flat_index];
                    }
                }
            }
        }

        return *this;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,
            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24
        };
        auto t0 = Tensor4D<int>(shape, data);
        auto t1 = Tensor4D<int>(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,
            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6
        };
        unsigned int s1[]{1, 2, 3, 1};
        float d1[]{
            6, 5, 4,
            3, 2, 1
        };
        auto t0 = Tensor4D<float>(s0, d0);
        auto t1 = Tensor4D<float>(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,
            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24
        };
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        auto t0 = Tensor4D<double>(s0, d0);
        auto t1 = Tensor4D<double>(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}
