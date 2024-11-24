#include <iostream>
#include <functional>
// 普通函数
int add(int a, int b) {
    return a + b;
}

int main() {
    std::function<int(int, int)> func = add;  // 包装普通函数
    std::cout << "Result: " << func(2, 3) << std::endl;  // 调用 std::function

    return 0;
}
