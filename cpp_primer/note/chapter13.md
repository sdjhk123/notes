# 拷贝控制



## 拷贝 赋值 与销毁

> 每个类都定义了一个类型和在此类型对象上可以执行的操作(拷贝控制操作)  一个类通过定义五种特殊成员函数来控制这种操作,包括    
> 拷贝构造函数 拷贝赋值运算符 移动构造函数 移动赋值运算符  析构函数

> *如果没有显示实现这些函数,编译器会自动生成*

```c++
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
    : num(f.num), //拷贝元素num
      str(f.str)  //拷贝元素str
{}

//等价于编译器自行生成的构造拷贝运算符
Foo &Foo::operator=(const Foo &f) {
  num = f.num; // 赋值int
  str = f.str; // 拷贝str
  return *this;
}

//等价于编译器自行生成的析构函数
Foo::~Foo() {}
```

> 直接初始化:编译器匹配最符合的构造函数
>
> 拷贝初始化:将对象拷贝到正在创建的对象中

```c++
string str1("test1");               //直接初始化
string str2(str1);                  //直接初始化
string str3 = str2;                 //拷贝初始化
string str4 = "test2";              //拷贝初始化
string str5 = string("test3");      //拷贝初始化
```



### 三/五法则

> 三:拷贝构造函数 拷贝赋值运算符 析构函数
>
> 五:新标准下再加 移动构造函数 移动赋值运算符

****

通常,我们应将拷贝控制看作一个整体,很少有单独实现其中某一个的情况

如下,便是缺少一种的危害

``` c++
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
  }
};

int num(1);
Hasptr<int> p(&num);
Hasptr<int>::f(p);
Hasptr<int> q(p);
// p,q都指向无效内存
```



### 使用=default

> 使用 =default 显式要求编译器生成合成的拷贝控制

****

```c++
// 使用 = default 显示声明编译器自动生成函数
Hasptr() = default;
```



### 阻止拷贝

>   使用 = delete 表示删除成员
>
>   表示不能以任何方式使用它们

```c++
Hasptr(Hasptr &) = delete;
/* 注:析构函数不能为 = delete, 否则无法释放资源 */
```



### 对象移动

> 为了性能,有时对象可以选择不去拷贝而是去移动

****

为了移动对象,新标准推出了**右值引用**,使用*&&*而非*&*表示

```c++
int &&a = 1;
// a 绑定到 1 上
```

****

> 左值稳定,右值短暂

变量是左值

对于一个左值,可以使用函数std::move()获取其右值引用

```c++
class move_test {};
move_test m1;
move_test m2 = std::move(m1);
// m1移动到m2上
```

> 对于一个移后源对象,我们可以销毁也可以赋予新值,但不能使用

****

对于**移动构造函数**,通常其**不分配内存**也**不抛出异常**

移动构造函数一般**拷贝指针**(接管被移动对象的内存)

然后将被移动对象的指针置为**nullptr**(确保销毁被移动对象是没有危害的)

```c++
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
```

