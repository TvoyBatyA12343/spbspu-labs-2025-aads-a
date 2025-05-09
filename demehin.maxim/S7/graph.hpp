#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <string>
#include <unordered_map>
#include <list/list.hpp>
#include <tree/tree.hpp>

namespace demehin
{
  struct PairHash
  {
    size_t operator()(const std::pair< std::string, std::string >& p) const
    {
      return std::hash< std::string >()(p.first) ^ std::hash< std::string >()(p.second);
    }
  };

  class Graph
  {
  public:
    using PairOfStr = std::pair< std::string, std::string >;
    using Edges = std::unordered_map< PairOfStr, List< unsigned int >, PairHash >;

    void addEdge(const std::string&, const std::string&, unsigned int);
    bool deleteEdge(const std::string&, const std::string&, unsigned int);
    const Edges& getEdges() const;
    Tree< std::string, std::string > getVrts() const;
    Tree< std::string, Tree< unsigned int, size_t > > getOutbounds(const std::string&) const;
    Tree< std::string, Tree< unsigned int, size_t > > getInbounds(const std::string&) const;
    bool hasVrt(const std::string&) const;

  private:
    Edges edges;
  };
}

#endif
