#include <iostream>

template <typename T, size_t size>
class fixed_vector
{
public:
  typedef T* iterator;
  typedef const T* const_iterator;


  fixed_vector(): v_(new T[size]) {} // bc default will be deleted
  ~fixed_vector() { delete[] v_; }

  template <typename O, size_t osize>
  fixed_vector(const fixed_vector<O, osize>& other):
    v_(new T[size])
  {
    try
    {
      std::copy(other.begin(), other.begin() + std::min(size, osize),
        begin());
    }
    catch(...)
    {
      delete [] v_;
      throw;
    }
  }

  fixed_vector(const fixed_vector<T, size>& other):
    v_(new T[size])
  {
    try
    {
      std::copy(other.begin(), other.end(), begin());
    }
    catch(...)
    {
      delete[] v_;
      throw;
    }
  }

  void Swap(fixed_vector<T, size>& other) noexcept
  {
    std::swap(v_, other.v_);
  }

  template <typename O, size_t osize>
  fixed_vector<T, size>& operator=(const fixed_vector<O, osize>& other)
  {
    fixed_vector<T, size> temp(other);
    Swap(temp);
    return *this;
  }

  fixed_vector<T, size>& operator=(const fixed_vector<T, size>& other)
  {
    fixed_vector<T, size> temp(other);
    Swap(temp);
    return *this;
  }

  template <class RAIter> // Constructing with modifying standard style
  fixed_vector(RAIter first, RAIter last):
    v_(new T[size])
  {
    try
    {
      std::copy(first, first + std::min(size, (size_t)(last - first)),
        begin());
    }
    catch(...)
    {
      delete[] v_;
      throw;
    }
  }

  template <class Iter>
  fixed_vector<T, size>& assign(Iter first, Iter last)
  {
    std::copy(first, first + std::min(size, (size_t)(last - first)),
      begin());
    return *this;
  }

  iterator begin() { return v_; }
  iterator end() { return v_ + size; }
  const_iterator begin() const { return v_; }
  const_iterator end() const { return v_ + size;}
private:
  T* v_;
};

int main()
{
  fixed_vector<char, 4> v;
  fixed_vector<int, 4> w;
  fixed_vector<int, 4> w2(w); // default copy constructor
  fixed_vector<int, 4> w3(v); //template constructor with modifying

  w = w2; // default copy assignment operator
  w = w2; // template assignment operator with modifying

  class B {};
  class D: public B {};

  fixed_vector<D*, 4> x;
  fixed_vector<B*, 4> y(x); // template constructor
  y = x;                    // template assignment operator4

  fixed_vector<char, 6> s;
  fixed_vector<int, 4> c(s.begin(), s.end());
  s.assign(c.begin(), c.end());
}