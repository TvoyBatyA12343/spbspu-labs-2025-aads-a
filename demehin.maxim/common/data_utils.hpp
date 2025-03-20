#ifndef DATA_UTILS_HPP
#define DATA_UTILS_HPP
#include <cstddef>

namespace demehin::details
{
  template< typename T >
  T* copyData(const T* data, size_t size)
  {
    T* cpyData = new T[size];
    for (size_t i = 0; i < size; i++)
    {
      cpyData[i] = data[i];
    }
    return cpyData;
  }
}

#endif
