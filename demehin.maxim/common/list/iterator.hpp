#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "node.hpp"
#include <cassert>

namespace demehin
{
  template< typename T >
  struct ListIterator: public std::iterator<
    std::bidirectional_iterator_tag, T >
  {
  public:
    using this_t = ListIterator< T >;

    ListIterator();
    ListIterator(const this_t&) = default;
    ListIterator(Node< T >* node);
    ~ListIterator() = default;
    this_t& operator=(const this_t&) = default;

    this_t& operator++();
    this_t operator++(int);

    this_t& operator--();
    this_t& operator--(int);

    T& operator*();
    T* operator->();

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

    Node< T >* getNode() const;

  private:
    Node< T >* node_;
  };

  template< typename T >
  ListIterator< T >::ListIterator():
    node_(nullptr)
  {}

  template< typename T >
  ListIterator< T >::ListIterator(Node< T >* node):
    node_(node)
  {}

  template< typename T >
  typename ListIterator< T >::this_t& ListIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  typename ListIterator< T >::this_t ListIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  typename ListIterator< T >::this_t& ListIterator< T >::operator--()
  {
    assert(node_ != nullptr);
    node_ = node_->prev_;
    return *this;
  }

  template< typename T >
  typename ListIterator< T >::this_t& ListIterator< T >::operator--(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    --(*this);
    return result;
  }

  template< typename T >
  T& ListIterator< T >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< typename T >
  T* ListIterator< T >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< typename T >
  bool ListIterator< T >::operator==(const this_t& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool ListIterator< T >::operator!=(const this_t& rhs) const
  {
    return !(rhs == *this);
  }

  template< typename T >
  Node< T >* ListIterator< T >::getNode() const
  {
    return node_;
  }

}

#endif
