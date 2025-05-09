#include "graph.hpp"

void demehin::Graph::addEdge(const std::string& from, const std::string& to, unsigned int weight)
{
  auto key = std::make_pair(from, to);
  edges[key].push_back(weight);
}

demehin::Tree< std::string, std::string > demehin::Graph::getVrts() const
{
  Tree< std::string, std::string > vrts;
  for (const auto& edge : edges)
  {
    vrts[edge.first.first];
    vrts[edge.first.second];
  }
  return vrts;
}

bool demehin::Graph::hasVrt(const std::string& vrt) const
{
  for (const auto& edge : edges)
  {
    if (edge.first.first == vrt || edge.first.second == vrt)
    {
      return true;
    }
  }
  return false;
}

demehin::Tree< std::string, demehin::Tree< unsigned int, size_t > > demehin::Graph::getOutbounds(const std::string& vrt) const
{
  Tree< std::string, Tree< unsigned int, size_t > > res;

  for (const auto& edge : edges)
  {
    if (edge.first.first == vrt)
    {
      std::string target = edge.first.second;
      for (auto weight : edge.second)
      {
        res[target][weight]++;
      }
    }
  }
  return res;
}

demehin::Tree< std::string, demehin::Tree< unsigned int, size_t > > demehin::Graph::getInbounds(const std::string& vrt) const
{
  Tree< std::string, Tree< unsigned int, size_t > > res;

  for (const auto& edge : edges)
  {
    if (edge.first.second == vrt)
    {
      std::string target = edge.first.first;
      for (auto weight : edge.second)
      {
        res[target][weight]++;
      }
    }
  }
  return res;
}

bool demehin::Graph::deleteEdge(const std::string& from, const std::string& to, unsigned int weight)
{
  auto key = std::make_pair(from, to);
  auto edgeIt = edges.find(key);

  if (edgeIt == edges.end())
  {
    return false;
  }

  auto& weights = edgeIt->second;
  bool isDeleted = false;
  for (auto it = weights.cbegin(); it != weights.cend();)
  {
    if (*it == weight)
    {
      it = weights.erase(it);
      isDeleted = true;
    }
    else
    {
      it++;
    }
  }

  if (weights.empty())
  {
    edges.erase(edgeIt);
    return true;
  }

  return isDeleted;
}


const demehin::Graph::Edges& demehin::Graph::getEdges() const
{
  return edges;
}
