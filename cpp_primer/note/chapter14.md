### lambda表达式

> lambda表达式可视作一个函数对象,(重载了调用函数运算符的类)
>
> 调用时调用里面的bool operator()=函数

```c++
auto a = [](const std::string &str1, const std::string &str2) {
    return str1.length() > str2.length();
}; // lambda表达式

class a {
  public:
    bool operator()(const std::string &str1, const std::string &str2) {
      return str1.length() > str2.length();
    }
}; // 类
```

