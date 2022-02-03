// 运行时类型识别(RTTI)
// typeid 返回表达式类型
// dynamic_cast 将基类的指针或引用安全转换为派生类的指针或引用
// 当这两个运算符运用于含有虚函数的类型时,运算符将使用其绑定对象的动态类型

#include <iostream>

int main() {

  class base {
  public:
    virtual void say() { std::cout << "Base" << std::endl; }
  };

  class derived : public base {
  public:
    void say() override { std::cout << "Derived" << std::endl; }
  };

  // dynamic_cast<type*>(e)
  // dynamic_cast<type&>(e)
  // dynamic_cast<type&&>(e)

  // e条件:1.type的公有基类;type的公有派生类;就是type的类型
  // 符合转化成功,不符合转化失败

  /* 失败结果:
  1.指针:结果为0
  2.引用 抛出bad_cast异常 */
  base *bp = new base();
  if (derived *dp = dynamic_cast<derived *>(bp)) {
    // bp 转为 derived 类型(基类转派生类)
    dp->say();
    delete dp;
  }

  delete bp;

  // typeid(e)返回对象的类型
  derived *dp2 = new derived;
  base *bp2 = dp2;
  // 两个指针指向同一个 derived 对象

  if (typeid(*bp2) == typeid(*dp2)) {
    // 是否指向同一类型对象
    bp2->say();
    dp2->say();
  }

  if (typeid(*bp2) == typeid(derived)) {
    // 是否指向制定类型
    bp2->say();
  }
  // 注:typeid应用作对象而非指针

  delete bp2;
  delete dp2;
  return 0;
}