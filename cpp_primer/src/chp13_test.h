namespace test {
using ugInt = unsigned int;

template <class T> class shared_ptr {
public:
  shared_ptr() = delete;

  shared_ptr(T *t) : ptr(t), times(times + 1), use(new ugInt(1)) {}
  // 计数器设置为1

  shared_ptr(shared_ptr &ptr) : ptr(ptr.ptr), times(times + 1), use(use) {
    ++*use;
    // 拷贝过来use指针后递增它的值
  }

  ~shared_ptr() {
    // 计数器的值-1,如果计数器-1后为0释放资源
    if (--*use == 0) {
      delete use;
      delete ptr;
    }
  }

  shared_ptr<T> &operator=(const shared_ptr<T> &ptr) {
    ++*ptr.use;
    if (--*use == 0) {
      delete this->ptr;
      delete use;
    }

    this->ptr = ptr.ptr;
    this->times = ptr.times;
    this->use = ptr.use;
    // 拷贝
    return *this;
  }

private:
  T *ptr{};
  ugInt times{};
  // 计数器
  ugInt *use{};
  // 多少共享ptr的对象
};

} // namespace test