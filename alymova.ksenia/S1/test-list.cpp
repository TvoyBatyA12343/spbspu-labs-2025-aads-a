#include <boost/test/unit_test.hpp>
#include "list.hpp"
#include "iterators.hpp"
#include "listNode.hpp"

BOOST_AUTO_TEST_CASE(test_constructors_operators)
{
  using list_t = alymova::List< int >;

  list_t list1 = {3, 1};
  list_t list2(list1);
  BOOST_TEST(list1 == list2);

  list_t list3(std::move(list_t{3, 1}));
  BOOST_TEST(list1 == list3);

  list_t list4 = {5, 2};
  list3 = list4;
  BOOST_TEST(list3 == list4);

  list4 = list_t{3, 1};
  BOOST_TEST(list4 == list1);
  BOOST_TEST(list4 != list3);
}
BOOST_AUTO_TEST_CASE(test_list_iterators)
{
  using list_t = alymova::List< int >;

  list_t list = {3, 1};
  auto iter_b = list.begin();
  auto iter_e = list.end();
  BOOST_TEST(*iter_b == 1);
  BOOST_TEST(*iter_e == 0);

  const list_t list1 = {2, 3};
  auto citer_b = list1.cbegin();
  auto citer_e = list1.cend();
  BOOST_TEST(*citer_b == 3);
  BOOST_TEST(*citer_e == 0);

  citer_b = list1.begin();
  citer_e = list1.end();
  BOOST_TEST(*citer_b == 3);
  BOOST_TEST(*citer_e == 0);
}
BOOST_AUTO_TEST_CASE(test_size)
{
  using list_t = alymova::List< int >;

  list_t list;
  BOOST_TEST(list.size() == 0);

  int x = 1;
  list.push_back(x);
  BOOST_TEST(list.size() == 1);

  list.pop_back();
  BOOST_TEST(list.empty());
}
BOOST_AUTO_TEST_CASE(test_base_interface)
{
  using list_t = alymova::List< int >;

  list_t list;
  BOOST_TEST(list.size() == 0);
  BOOST_TEST(list.empty());

  list.push_front(1);
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.size() == 1);

  list.push_front(2);
  BOOST_TEST(list.back() == 1);

  list.pop_front();
  BOOST_TEST(list.front() == 1);

  list.pop_back();
  BOOST_TEST(list.empty());

  list.push_back(10);
  list.push_back(20);
  list.push_back(30);
  BOOST_TEST(list.front() == 10);
  BOOST_TEST(list.back() == 30);
  BOOST_TEST(*(++list.begin()) == 20);
  BOOST_TEST(list.size() == 3);

  list.pop_back();
  BOOST_TEST(list.back() == 20);

  const list_t list1 = {3, 1};
  BOOST_TEST(list1.front() == 1);
  BOOST_TEST(list1.back() == 1);
}
BOOST_AUTO_TEST_CASE(test_swap)
{
  using list_t = alymova::List< int >;

  list_t list1 = {2, 5};
  list_t list2 = {5, 2};
  list_t list3 = list2;
  list1.swap(list2);
  BOOST_TEST(list1 == list3);
}



bool single_digit(const int& value)
{
  return (value < 10 && value > -10);
}
struct SingleDigit
{
  bool operator()(const int& value)
  {
    return (value < 10 && value > -10);
  }
};
template< typename T >
struct EqualNode
{
  const T& value;
  EqualNode(const T& new_value):
    value(new_value)
  {}
  bool operator()(const T& data)
  {
    return value == data;
  }
};
BOOST_AUTO_TEST_CASE(test_remove)
{
  using list_t = alymova::List< int >;
  using list_str_t = alymova::List< std::string >;

  list_str_t list1 = {1, "cat"};
  list1.remove("cat");
  BOOST_TEST(list1.size() == 0);

  list1.push_back("dog");
  list1.push_back("student");
  list1.remove("student");
  BOOST_TEST(list1.back() == "dog");

  list_str_t list2 = {10, "cat"};
  list2.push_back("fox");
  list2.push_front("dolphin");
  list2.remove("cat");
  BOOST_TEST(list2.size() == 2);

  list_t list3 = {5, 10};
  list3.push_back(1);

  int value = 10;
  EqualNode< int > pred = EqualNode< int >{value};
  list3.remove_if< EqualNode< int > >(pred);

  SingleDigit sd = SingleDigit{};
  list3.remove_if< SingleDigit >(sd);
  BOOST_TEST(list3.size() == 6);
  BOOST_TEST(list3.front() == 10);
}
