#include <memory>
#include <string>

int main() {
  std::unique_ptr<std::string> unique_ptr(
      std::make_unique<std::string>(std::string("str")));
  // unique_ptr 在析构时会释放
  unique_ptr.get();
  return 0;
}