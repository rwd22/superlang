#pragma once

#include <vector>
#include <unordered_map>

#include "decl.hpp"
#include "symbol.hpp"

struct Scope : std::unordered_map<std::string, Decl*>
{
  Decl* lookup(std::string sym)
  {
    auto iter = find(sym);
    if (iter == end())
      return nullptr;
    return iter->second;
  }

  void declare(Decl* d, std::string s)
  {
    emplace(s, d);
  }
};


struct Scope_stack : std::vector<Scope>
{
  Decl* lookup(std::string sym)
  {
    for (auto iter = rbegin(); iter != rend(); ++iter) {
      if (Decl * d = iter->lookup(sym))
        return d;
    }
    return nullptr;
  }
};
