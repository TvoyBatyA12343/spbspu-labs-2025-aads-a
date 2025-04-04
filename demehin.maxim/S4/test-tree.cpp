#include <boost/test/unit_test.hpp>
#include <sstream>
#include <tree/tree.hpp>

namespace
{
  void printTreeValues(std::ostream& out, demehin::Tree< size_t, std::string > tree)
  {
    for (auto it = tree.begin(); it != tree.end(); it++)
    {
      out << (*it).second;
    }
  }
}

BOOST_AUTO_TEST_CASE(tree_test)
{
  demehin::Tree< size_t, std::string > t;
  demehin::Tree< size_t, std::string > tree(std::move(t));
  tree.insert(std::make_pair(1, "1"));
  tree.insert(std::make_pair(3, "4"));
  tree.insert(std::make_pair(10, "11"));
  tree.insert(std::make_pair(2, "3"));
  tree.insert(std::make_pair(4, "5"));
  BOOST_TEST(tree.count(3) == 1);

  /*for (auto it = tree.begin(); it != tree.end(); ++it)
  {
    std::cout << (*it).second << "\n";
  }
  demehin::Tree< size_t, std::string > cpy_tree(tree);

  tree.swap(cpy_tree);
  for (auto it = cpy_tree.begin(); it != cpy_tree.end(); ++it)
  {
    std::cout << (*it).second << "\n";
  }*/
}


BOOST_AUTO_TEST_CASE(tree_construct_test)
{
  demehin::Tree< size_t, std::string > tree;
  tree.insert(std::make_pair(1, "1"));
  tree.insert(std::make_pair(10, "10"));
  tree.insert(std::make_pair(3, "3"));
  demehin::Tree< size_t, std::string > tree_cpy(tree);
  BOOST_TEST(tree_cpy.size() == 3);
  BOOST_TEST((*tree_cpy.begin()).second == "1");
  demehin::Tree< size_t, std::string > tree_mv(std::move(tree_cpy));

  demehin::Tree< size_t, std::string > range_tree(++tree_mv.begin(), tree_mv.end());
  std::ostringstream out;
  printTreeValues(out, range_tree);
  BOOST_TEST(out.str() == "310");

}

BOOST_AUTO_TEST_CASE(tree_modifiers_test)
{
  demehin::Tree< size_t, std::string > tree1;
  demehin::Tree< size_t, std::string > tree2;
  tree1.insert(std::make_pair(2, "2"));
  tree1.insert(std::make_pair(6, "6"));
  tree1.insert(std::make_pair(4, "4"));
  tree2.emplace(std::make_pair(10, "10"));
  tree2.emplace(std::make_pair(3, "3"));
  tree2.emplace(std::make_pair(5, "5"));
  tree2.emplace(std::make_pair(1, "1"));

  std::ostringstream out1;
  std::ostringstream out2;
  printTreeValues(out1, tree1);
  printTreeValues(out2, tree2);
  BOOST_TEST(out1.str() == "246");
  BOOST_TEST(out2.str() == "13510");

  tree2.insert(std::make_pair(7, "7"));
  tree2.insert(std::make_pair(11, "11"));
  tree2.erase(++tree2.begin());
  tree2.erase(10);
  std::ostringstream out3;
  printTreeValues(out3, tree2);
  BOOST_TEST(out3.str() == "15711");

  tree1.swap(tree2);
  std::ostringstream out4;
  std::ostringstream out5;
  printTreeValues(out4, tree1);
  printTreeValues(out5, tree2);
  BOOST_TEST(tree1.size() == 4);
  BOOST_TEST(tree2.size() == 3);
  BOOST_TEST(out4.str() == "15711");
  BOOST_TEST(out5.str() == "246");


  tree1.erase(++tree1.begin(), ++(++(++(tree1.begin()))));
  std::ostringstream out6;
  printTreeValues(out6, tree1);
  BOOST_TEST(out6.str() == "1711");
}
