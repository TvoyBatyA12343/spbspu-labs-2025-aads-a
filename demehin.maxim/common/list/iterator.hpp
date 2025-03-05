#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <cassert>
#include "node.hpp"

namespace demehin
{
  template< typename T >
  struct ListIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    using this_t = ListIterator< T >;

    ListIterator() noexcept;
    ListIterator(Node< T >* node) noexcept;

    this_t& operator++() noexcept;
    this_t operator++(int) noexcept;

    this_t& operator--() noexcept;
    this_t& operator--(int) noexcept;

    T& operator*() noexcept;
    T* operator->() noexcept;

    bool operator!=(const this_t&) const noexcept;
    bool operator==(const this_t&) const noexcept;

    Node< T >* getNode() const noexcept;

  private:
    Node< T >* node_;
  };

  template< typename T >
  ListIterator< T >::ListIterator() noexcept:
    node_(nullptr)
  {}

  template< typename T >
  ListIterator< T >::ListIterator(Node< T >* node) noexcept:
    node_(node)
  {}

  template< typename T >
  typename ListIterator< T >::this_t& ListIterator< T >::operator++() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  typename ListIterator< T >::this_t ListIterator< T >::operator++(int) noexcept
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  typename ListIterator< T >::this_t& ListIterator< T >::operator--() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->prev;
    return *this;
  }

  template< typename T >
  typename ListIterator< T >::this_t& ListIterator< T >::operator--(int) noexcept
  {
    assert(node_ != nullptr);
    this_t result(*this);
    --(*this);
    return result;
  }

  template< typename T >
  T& ListIterator< T >::operator*() noexcept
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  T* ListIterator< T >::operator->() noexcept
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  bool ListIterator< T >::operator==(const this_t& rhs) const noexcept
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool ListIterator< T >::operator!=(const this_t& rhs) const noexcept
  {
    return !(rhs == *this);
  }

  template< typename T >
  Node< T >* ListIterator< T >::getNode() const noexcept
  {
    return node_;
  }
}

#endif
