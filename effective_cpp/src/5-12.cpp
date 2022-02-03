// class empty{};
// 相当于(编译器自动生成)
#include <vector>
class empty {
public:
  empty() = default;
  ~empty() = default;
  empty &operator=(const empty &) = default;
  empty(const empty &) = default;
};

class base {
protected: // 允许 derived 对象 构造和析构
  base() = default;
  ~base() = default;

private:
  base(const base &) = default;
  base &operator=(base &) = default;
  // 不允访问
};

class derived : private base {};
// 注:继承的修饰符代表这个类对于继承的成员在这个类中的公开程度

class base2 {
protected:
  int base_num{};
};

class derived2 : public base2 {
private:
  int derived_num{};
};

class test {
public:
  test() = default;
  ~test() = default;

  void close() {
    try {
      this->~test();
    } catch (...) {
      // do something
    }
  }
};
// 假设test类的析构函数会抛出异常

class base3 {
public:
  virtual void test();

  base3() {
    // ...
    test();
    // 在构造base3期间调用虚函数
  }
};

class derived3 : public base3 {
public:
  void test() override {
    // ...
  }
};

class test2 {
public:
  /* test2 &operator=(const test2 &t) {
    delete ptr;
    ptr = t.ptr;
    // 若是自我赋值的话,那么指针将指向被删除的对象
    return *this;
  } */

  test2 &operator=(const test2 &t) {
    if (this == &t)
      return *this;
    //如果是自我赋值,便不做任何事

    delete ptr;
    ptr = t.ptr;
    // 若是自我赋值的话,那么指针将指向被删除的对象
    return *this;
  }

private:
  int *ptr{};
};

int main() {
  derived d;
  // 合法:构造和析构

  // derived d2(d); 报错

  base2 *d_test = new derived2;
  delete d_test;
  // 此时销毁调用 base2::~base2() , derived_num 无法释放资源!

  std::vector<test> v;
  for (int i = 0; i < 5; ++i) {
    v.push_back(test());
  }

  // 当v销毁时,其内5个test对象也会相应执行析构函数
  // 假设成真时,会导致抛出多个异常

  int a, b, c;
  a = b = c = 1;
  // 连续赋值

  return 0;
}