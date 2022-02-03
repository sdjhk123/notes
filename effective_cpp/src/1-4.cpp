#include <iostream>
#include <vector>

#define PI 3.14
// 写作如下写法
const static double Pi = 3.14;

inline double getPI() { return Pi; }

class test {
private:
  const static int size = 10;
  // test::size
  // 只有test类内可访问

  enum { size2 = 10 };
  // 倘若说编译器不允许static常量初始化in class对象:

public:
#define SIZE 10
  int nums[size];
  int nums2[size2];
  // int nums[SIZE];
  // 此时在此句下所有地方都能访问到
};

#define MAX(a, b) (a) > (b) ? (a) : (b)
// 请替换为如下
template <class T> inline T &max(T &a, T &b) { return a > b ? a : b; }

const static int nums_begin = 0;

class test_class {
private:
  int num{};

public:
  int cget_num() const { return num; }
  // 不修改成员变量

  int get_num() { return cget_num(); }
  // 避免代码复用
};

class test2 {
public:
  int a;
  int b;
  test2(int a) : a(a), b(0) {}
  // 初始化每个成员(尽量地按照变量声明顺序去初始化)

  test2() = default;
};

// static test2 t;

// 调用时初始化t,不调用时t便不会初始化
test2 &get_test2() {
  static test2 t;
  return t;
}

// t.a 不保证被初始化
int test_f1(test2 &t) { return t.a; }

// vector保证初始化
std::vector<int> test_f2() {
  std::vector<int> v;
  return v;
}

int main() {
  // nums_begin = 1;// 报错

#define PI 3.14
  test2 t;

  int a(1);
  // 声明并初始化

  return t.a;
}