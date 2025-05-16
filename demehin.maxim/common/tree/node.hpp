#ifndef NODE_HPP
#define NODE_HPP
#include <utility>

namespace demehin
{
  template< typename Key, typename T >
  struct TreeNode
  {
    std::pair< Key, T > data;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    int height;

    template< typename... Args >
    explicit TreeNode(Args&&... args) noexcept;

    template< typename... Args >
    TreeNode(const TreeNode* parent, Args&&... args) noexcept;

  };

  template< typename Key, typename T >
  template< typename... Args >
  TreeNode< Key, T >::TreeNode(Args&&... args) noexcept:
    data(std::forward< Args >(args)...),
    parent(nullptr),
    left(nullptr),
    right(nullptr),
    height(1)
  {}

  template< typename Key, typename T >
  template< typename... Args >
  TreeNode< Key, T >::TreeNode(const TreeNode* prnt, Args&&... args) noexcept:
    TreeNode(std::forward< Args >(args)...)
  {
    parent = prnt;
  }

}

#endif
