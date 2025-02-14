#include <iostream>
#include <utility>
#include <string>
#include <list>
#include <algorithm>

namespace
{
  using ListOfPairs = std::list< std::pair< std::string, std::list< int > > >;

  size_t defineMaxSize(ListOfPairs pairsList)
  {
    size_t max_size = 0;
    for (auto it = pairsList.begin(); it != pairsList.end(); ++it)
    {
      max_size = std::max(max_size, it->second.size());
    }
    return max_size;
  }

  int* copyNums(const int* nums, size_t nums_cnt)
  {
    int* new_nums = new int[nums_cnt];
    for (size_t i = 0; i < nums_cnt; i++)
    {
      new_nums[i] = nums[i];
    }
    return new_nums;
  }

  void printSumValues(std::ostream& out, const int* vals, size_t size)
  {
    if (size > 0)
    {
      out << vals[0];
      for (size_t i = 1; i < size; i++)
      {
        out << " " << vals[i];
      }
    }
    else
    {
      out << 0;
    }
  }

  void printValues(std::ostream& out, ListOfPairs pairsList)
  {
    size_t capacity = 128;
    int* sum_values = new int[capacity]();
    size_t max_size = defineMaxSize(pairsList);
    size_t sum_vals_cnt = 0;
    for (size_t i = 0; i < max_size; i++)
    {
      int sum = 0;
      bool isFirst = true;
      for (auto it = pairsList.begin(); it != pairsList.end(); it++)
      {
        if (!it->second.empty())
        {
          if (!isFirst)
          {
            out << "_";
          }
          else
          {
            isFirst = false;
          }
          out << it->second.front();
          sum += it->second.front();
          it->second.pop_front();
        }
      }
      if (i >= capacity)
      {
        capacity *= 2;
        int* new_values = nullptr;
        try
        {
          new_values = copyNums(sum_values, capacity);
        }
        catch (const std::bad_alloc&)
        {
          delete[] sum_values;
          throw;
        }
        delete[] sum_values;
        sum_values = new_values;
      }

      sum_values[sum_vals_cnt++] = sum;
      out << "\n";
    }
    printSumValues(out, sum_values, sum_vals_cnt);
    delete[] sum_values;
  }
}

int main()
{
  std::list< std::pair< std::string, std::list< int > > > pairsList;
  std::string nodeName;
  while (std::cin >> nodeName)
  {
    std::list< int > numsList;
    int num = 0;
    while (std::cin >> num)
    {
      numsList.push_back(num);
    }
    pairsList.push_back(std::make_pair(nodeName, numsList));
    std::cin.clear();
  }

  std::cout << pairsList.begin()->first;
  for (auto it = ++pairsList.begin(); it != pairsList.end(); ++it)
  {
    std::cout << " " << it->first;
  }
  std::cout << "\n";

  printValues(std::cout, pairsList);
  std::cout << "\n";
}
