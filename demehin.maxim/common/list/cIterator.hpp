#ifndef CITERATOR_HPP
#define CITERATOR_HPP
#include <cassert>
#include "node.hpp"

namespace demehin
{
  template< typename T >
  struct cListIterator
  {
  public:
    using this_t = cListIterator< T >;

    cListIterator() noexcept;
    cListIterator(Node< T >* node) noexcept;

    this_t& operator++() noexcept;
    this_t operator++(int) noexcept;

    this_t& operator--() noexcept;
    this_t operator--(int) noexcept;

    const T& operator*() const noexcept;
    const T* operator->() const noexcept;

    bool operator!=(const this_t&) const noexcept;
    bool operator==(const this_t&) const noexcept;

    Node< T >* getNode() const noexcept;

  private:
    Node< T >* node_;
  };

  template< typename T >
  cListIterator< T >::cListIterator() noexcept:
    node_(nullptr)
  {}

  template< typename T >
  cListIterator< T >::cListIterator(Node< T >* node) noexcept:
    node_(node)
  {}

  template< typename T >
  typename cListIterator< T >::this_t& cListIterator< T >::operator++() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  typename cListIterator< T >::this_t cListIterator< T >::operator++(int) noexcept
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  typename cListIterator< T >::this_t& cListIterator< T >::operator--() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->prev;
    return *this;
  }

  template< typename T >
  typename cListIterator< T >::this_t cListIterator< T >::operator--(int) noexcept
  {
    assert(node_ != nullptr);
    this_t result(*this);
    --(*this);
    return result;
  }

  template< typename T >
  const T& cListIterator< T >::operator*() const noexcept
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  const T* cListIterator< T >::operator->() const noexcept
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  bool cListIterator< T >::operator==(const this_t& rhs) const noexcept
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool cListIterator< T >::operator!=(const this_t& rhs) const noexcept
  {
    return !(rhs == *this);
  }

  template< typename T >
  Node< T >* cListIterator< T >::getNode() const noexcept
  {
    return node_;
  }

}

#endif
