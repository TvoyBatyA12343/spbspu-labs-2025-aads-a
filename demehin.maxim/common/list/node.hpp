#ifndef NODE_HPP
#define NODE_HPP

namespace demehin
{
  template< typename T >
  struct Node
  {
    T data_;
    Node< T >* prev_;
    Node< T >* next_;

    Node();
    Node(const T&);
  };

  template< typename T >
  Node< T >::Node():
    data_(T()),
    prev_(nullptr),
    next_(nullptr)
  {}

  template< typename T >
  Node< T >::Node(const T& data):
    data_(data),
    prev_(nullptr),
    next_(nullptr)
  {}
}

#endif
