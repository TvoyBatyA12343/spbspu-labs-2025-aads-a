#include <iostream>
#include <utility>
#include <string>
#include <list>
#include <algorithm>
#include <list/list.hpp>

namespace
{
  using ListOfPairs = demehin::List<std::pair<std::string, demehin::List<unsigned long long>>>;

  size_t defineMaxSize(ListOfPairs pairsList)
  {
    size_t max_size = 0;
    for (auto it = pairsList.begin(); it != pairsList.end(); ++it)
    {
      max_size = std::max(max_size, it->second.size());
    }
    return max_size;
  }

  unsigned long long calculateSum(demehin::List<unsigned long long> nums)
  {
    unsigned long long sum = 0;
    if (nums.empty())
    {
      return 0;
    }
    unsigned long long max = std::numeric_limits<unsigned long long>::max();
    for (auto it = nums.begin(); it != nums.end(); it++)
    {
      if (sum > max - *it)
      {
        throw std::overflow_error("error: overflow");
      }
      sum += *it;
    }

    return sum;
  }

  void printValues(std::ostream& out, ListOfPairs pairsList)
  {
    size_t max_size = defineMaxSize(pairsList);
    if (max_size == 0)
    {
      out << "0";
      return;
    }
    demehin::List<unsigned long long> sumList;
    for (size_t i = 0; i < max_size; i++)
    {
      demehin::List<unsigned long long> numsList;
      for (auto it = pairsList.begin(); it != pairsList.end(); it++)
      {
        if (!it->second.empty())
        {
          numsList.push_back(it->second.front());
          it->second.pop_front();
        }
      }

      if (!numsList.empty())
      {
        out << numsList.front();
        for (auto it = ++numsList.begin(); it != numsList.end(); it++)
        {
          out << " " << *it;
        }
        out << "\n";
        sumList.push_back(calculateSum(numsList));
      }
    }

    out << sumList.front();
    for (auto it = ++sumList.begin(); it != sumList.end(); it++)
    {
      out << " " << *it;
    }
  }
}

int main()
{
  demehin::List< std::pair< std::string, demehin::List< unsigned long long > > > pairsList;
  std::string nodeName;
  while (std::cin >> nodeName)
  {
    demehin::List< unsigned long long > numsList;
    unsigned long long num = 0;
    while (std::cin >> num)
    {
      numsList.push_back(num);
    }
    pairsList.push_back(std::make_pair(nodeName, numsList));
    std::cin.clear();
  }

  if (pairsList.size() == 0)
  {
    std::cout << "0\n";
    return 0;
  }

  std::cout << pairsList.begin()->first;
  for (auto it = ++pairsList.begin(); it != pairsList.end(); ++it)
  {
    std::cout << " " << it->first;
  }
  std::cout << "\n";
  try
  {
    printValues(std::cout, pairsList);
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  std::cout << "\n";
}
