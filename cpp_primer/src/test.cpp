class base {
public:
  int pub_num{};

protected:
  int pro_num{};

private:
  int pri_num{};
};

class derived1 : public base {
  int *test() {
    // pub_num pro_num可用
    return new int[]{pub_num, pro_num};
  }
};

class derived2 : protected base {
  int *test() {
    // pub_num pro_num可用
    return new int[]{pub_num, pro_num};
  }
};

class derived3 : private base {
  int *test() { return new int[1]; }
};

// 继承的修饰符代表这个类对于继承的成员在这个类中的公开程度

int main() {
  derived1 d1;
  derived2 d2;
  derived3 d3;

  // d1可访问pub_num
  d1.pub_num = 1;

  // d2皆不可访问

  // d3皆不可访问

  return 0;
}
