#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <utility>

namespace demehin
{
  template< typename T >
  class Queue
  {
  public:

    Queue();
    Queue(const Queue&);
    Queue(Queue&&) noexcept;
    ~Queue();

    void push(const T& rhs) noexcept;
    void pop();
    T& front() const;
    T& back() const;

    bool empty() const noexcept;
    size_t size() const noexcept;

  private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void resize();
  };

  template< typename T >
  Queue< T >::Queue():
    data_(nullptr),
    size_(0),
    capacity_(100)
  {
    data_ = new T[capacity_];
  }

  template< typename T >
  Queue< T >::Queue(const Queue& rhs):
  data_(nullptr),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
  {
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; i++)
    {
      data_[i] = rhs.data_[i];
    }
  }

  template< typename T >
  Queue< T >::Queue(Queue&& rhs) noexcept:
    data_(rhs.data_),
    size_(rhs.size_),
    capacity_(rhs.capacity_)
  {
    std::exchange(rhs.data_, nullptr);
    std::exchange(rhs.size_, 0);
    std::exchange(rhs.capacity_, 0);
  }

  template< typename T >
  Queue< T >::~Queue()
  {
    delete[] data_;
  }

  template< typename T >
  void Queue< T >::push(const T& rhs) noexcept
  {
    if (size_ == capacity_)
    {
      resize();
    }

    data_[size_++] = rhs;
  }

  template< typename T >
  void Queue< T >::pop()
  {
    if (empty())
    {
      throw std::logic_error("error: empty");
    }

    for (size_t i = 1; i < size_; i++)
    {
      data_[i - 1] = data_[i];
    }
    size_--;
  }

  template< typename T >
  T& Queue< T >::back() const
  {
    if (empty())
    {
      throw std::logic_error("error: empty");
    }
    return data_[size_ - 1];
  }

  template< typename T >
  T& Queue< T >::front() const
  {
    if (empty())
    {
      throw std::logic_error("error: empty");
    }
    return data_[0];
  }

  template< typename T >
  size_t Queue< T >::size() const noexcept
  {
    return size_;
  }

  template< typename T >
  bool Queue< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename T >
  void Queue< T >::resize()
  {
    capacity_ *= 2;
    T* newData = new T[capacity_];
    for (size_t i = 0; i < size_; i++)
    {
      newData[i] = data_[i];
    }
    delete[] data_;
    data_ = newData;
  }
}

#endif
