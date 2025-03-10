#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <cassert>
#include <iterator>
#include <new>
#include "node.hpp"
namespace kiselev
{
  template< typename T >
  class List;

  template< typename T, bool IsConst >
  class ListIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class List< T >;
    friend class ListIterator< T, !IsConst >;
  public:
    using reference = std::conditional_t< IsConst, const T&, T& >;
    using pointer = std::conditional_t< IsConst, const T*, T* >;

    ListIterator(): node_(nullptr) {}
    ListIterator(Node< T >* node): node_(node) {}
    template< bool OtherIsConst, std::enable_if_t< IsConst && !OtherIsConst, int > = 0 >
    ListIterator(const ListIterator< T, OtherIsConst >& other): node_(other.node_) {}
    template< bool OtherIsConst, std::enable_if_t< IsConst && !OtherIsConst, int > = 0 >
    ListIterator< T, IsConst >& operator=(const ListIterator< T, OtherIsConst >& other);

    ListIterator< T, IsConst >& operator++() noexcept;
    ListIterator< T, IsConst > operator++(int) noexcept;

    ListIterator< T, IsConst >& operator--() noexcept;
    ListIterator< T, IsConst > operator--(int) noexcept;

    reference operator*() const noexcept;
    pointer operator->() const noexcept;

    bool operator==(const ListIterator< T, IsConst >&) const noexcept;
    bool operator!=(const ListIterator< T, IsConst >&) const noexcept;

  private:
    Node< T >* node_;
  };

  template< typename T, bool IsConst >
  template< bool OtherIsConst, std::enable_if_t< IsConst && !OtherIsConst, int > >
  ListIterator< T, IsConst >& ListIterator< T, IsConst >::operator=(const ListIterator< T, OtherIsConst >& other)
  {
    node_ = other.node_;
    return *this;
  }

  template< typename T, bool IsConst >
  ListIterator< T, IsConst >& ListIterator< T, IsConst >::operator++() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
  }

  template< typename T, bool IsConst >
  ListIterator< T, IsConst > ListIterator< T, IsConst >::operator++(int) noexcept
  {
    assert(node_ != nullptr);
    ListIterator< T, IsConst > result(*this);
    ++(*this);
    return result;
  }

  template< typename T, bool IsConst >
  ListIterator< T, IsConst >& ListIterator< T, IsConst >::operator--() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->prev_;
    return *this;
  }

  template< typename T, bool IsConst >
  ListIterator< T, IsConst > ListIterator< T, IsConst >::operator--(int) noexcept
  {
    assert(node_ != nullptr);
    ListIterator< T, IsConst > result(*this);
    --(*this);
    return result;
  }

  template< typename T, bool IsConst >
  typename ListIterator< T, IsConst >::reference ListIterator< T, IsConst >::operator*() const noexcept
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< typename T, bool IsConst >
  typename ListIterator< T, IsConst >::pointer ListIterator< T, IsConst >::operator->() const noexcept
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< typename T, bool IsConst >
  bool ListIterator< T, IsConst >::operator==(const ListIterator< T, IsConst >& it) const noexcept
  {
    return node_ == it.node_;
  }

  template< typename T, bool IsConst >
  bool ListIterator< T, IsConst >::operator!=(const ListIterator< T, IsConst >& it) const noexcept
  {
    return !(it == *this);
  }

}
#endif
