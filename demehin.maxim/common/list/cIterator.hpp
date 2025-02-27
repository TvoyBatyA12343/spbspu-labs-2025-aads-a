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

    cListIterator();
    cListIterator(const this_t&) = default;
    cListIterator(Node< T >* node);
    ~cListIterator() = default;
    this_t& operator=(const this_t&) = default;

    this_t& operator++();
    this_t operator++(int);

    this_t& operator--();
    this_t operator--(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

    Node< T >* getNode() const;

  private:
    Node< T >* node_;
  };

  template< typename T >
  cListIterator< T >::cListIterator():
    node_(nullptr)
  {}

  template< typename T >
  cListIterator< T >::cListIterator(Node< T >* node):
    node_(node)
  {}

  template< typename T >
  typename cListIterator< T >::this_t& cListIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  typename cListIterator< T >::this_t cListIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  typename cListIterator< T >::this_t& cListIterator< T >::operator--()
  {
    assert(node_ != nullptr);
    node_ = node_->prev_;
    return *this;
  }

  template< typename T >
  typename cListIterator< T >::this_t cListIterator< T >::operator--(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    --(*this);
    return result;
  }

  template< typename T >
  const T& cListIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< typename T >
  const T* cListIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< typename T >
  bool cListIterator< T >::operator==(const this_t& rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool cListIterator< T >::operator!=(const this_t& rhs) const
  {
    return !(rhs == *this);
  }

  template< typename T >
  Node< T >* cListIterator< T >::getNode() const
  {
    return node_;
  }

}

#endif
