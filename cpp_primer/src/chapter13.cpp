#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

// 拷贝控制

// 每个类都定义了一个类型
// 和在此类型对象上可以执行的操作(拷贝控制操作)
// 一个类通过定义五种特殊成员函数来控制这种操作,包括
/* 拷贝构造函数 拷贝赋值运算符 移动构造函数
 移动赋值运算符 析构函数 */

// 如果没有显示实现这些函数,编译器会自动生成

/* 三/五法则
  三:拷贝构造函数 拷贝赋值运算符 析构函数
  五:新标准下再加 移动构造函数 移动赋值运算符 */

using std::string;

class Foo {
public:
  Foo(); //默认构造函数
  Foo(const int num) : num(num) {}
  Foo(const Foo &f); //拷贝函数
  /* 拷贝方式:
  对于类类型的成员调用其构造函数
  内置类型直接拷贝 */

  Foo &operator=(const Foo &f); //赋值运算符
  // 赋值运算符应该返回一个指向左侧运算对象的引用

  ~Foo(); //析构函数:不接受参数,释放资源
private:
  int num{};
  string str;
};

//等价于编译器自行生成的构造拷贝函数
Foo::Foo(const Foo &f)
    : num(f.num),           //拷贝元素num
      str(std::move(f.str)) //拷贝元素str
{}

//等价于编译器自行生成的构造拷贝运算符
Foo &Foo::operator=(const Foo &f) {
  num = f.num; // 赋值int
  str = f.str; // 拷贝str
  return *this;
}

//等价于编译器自行生成的析构函数
Foo::~Foo() {}

template <class T> class Hasptr {
private:
  T *ptr{};

public:
  Hasptr(T *p) : ptr(p){};

  inline T *get_ptr() { return ptr; }

  ~Hasptr() { delete ptr; }

  static inline Hasptr<T> f(Hasptr<T> hp) {
    Hasptr ret = hp; //拷贝hp
    return ret;      //拷贝一个ret返回
    // 原有ret销毁->ret指向被销毁->hp指向被销毁
    // 若不对拷贝构造函数显示声明
    // 那么会导致多次释放或访问无效内存
  }

  // 使用 = default 显示声明编译器自动生成函数
  Hasptr() = default;

  // 使用 = delete 表示删除成员
  // 表示不能以任何方式使用它们
  // Hasptr(Hasptr &) = delete;
  /* 注:析构函数不能为 = delete, 否则无法释放资源 */
};

// 行为像值的类:拷贝时拷贝对象本身而非指针,事后释放
// 行为像指针的类:拷贝时拷贝指针,析构函数释放

// 移动对象而非拷贝
class move_test {
public:
  move_test() = default;

  //拷贝指针
  move_test(move_test &&m) noexcept : f(m.f) {
    m.f = nullptr;
    // 确保对m运行系够函数是安全的
  }

  // 移动赋值运算符同理
  move_test &operator=(move_test &&m) noexcept {
    // 确保不为自赋值
    if (this != &m) {
      f = m.f;
      m.f = nullptr;
    }
    return *this;
  }

private:
  Foo *f{};
};

int main() {
  string str1("test1");          //直接初始化
  string str2(str1);             //直接初始化
  string str3 = str2;            //拷贝初始化
  string str4 = "test2";         //拷贝初始化
  string str5 = string("test3"); //拷贝初始化
  /* 直接初始化:编译器匹配最符合的构造函数
    拷贝初始化:将对象拷贝到正在创建的对象中 */

  int num(1);
  Hasptr<int> p(&num);
  Hasptr<int>::f(p);
  Hasptr<int> q(p);
  // p,q都指向无效内存

  int &&a = 1;
  // a 绑定到 1 上

  move_test m1;
  move_test m2 = std::move(m1);
  // m1移动到m2上

  return 0;
}