#include "../exercise.h"
#include <map>

// READ: `std::map` <https://zh.cppreference.com/w/cpp/container/map>
// READ: `std::unordered_map` <https://zh.cppreference.com/w/cpp/container/unordered_map>

// 检查给定键是否存在于 map 中
template<class k, class v>
bool key_exists(std::map<k, v> const &map, k const &key) {
    // 使用 map.find(key) 来判断键是否存在
    return map.find(key) != map.end();
}

// 设置键值对，若键已存在，则更新值
template<class k, class v>
void set(std::map<k, v> &map, k key, v value) {
    // 使用 map[key] = value 来插入或更新键值对
    map[key] = value;
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    using namespace std::string_literals;

    std::map<std::string, std::string> secrets;

    // 插入初始键值对
    set(secrets, "hello"s, "world"s);
    // 验证 "hello" 是否存在
    ASSERT(key_exists(secrets, "hello"s), "\"hello\" should be in `secrets`");
    // 验证 "foo" 不存在
    ASSERT(!key_exists(secrets, "foo"s), "\"foo\" should not be in `secrets`");

    // 插入其他键值对
    set(secrets, "foo"s, "bar"s);
    set(secrets, "Infini"s, "Tensor"s);

    // 验证各个键的值是否正确
    ASSERT(secrets["hello"] == "world", "hello -> world");
    ASSERT(secrets["foo"] == "bar", "foo -> bar");
    ASSERT(secrets["Infini"] == "Tensor", "Infini -> Tensor");

    // 更新已有键 "hello" 的值
    set(secrets, "hello"s, "developer"s);
    ASSERT(secrets["hello"] == "developer", "hello -> developer");

    return 0;
}
