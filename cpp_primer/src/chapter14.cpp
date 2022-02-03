#include <string>

int main() {
  auto a = [](const std::string &str1, const std::string &str2) {
    return str1.length() > str2.length();
  }; // lambda表达式
  class a {
  public:
    bool operator()(const std::string &str1, const std::string &str2) {
      return str1.length() > str2.length();
    }
  }; //类
  return a("Hello", "World");
}