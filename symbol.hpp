#pragma once

#include <string>
#include <unordered_set>


class Symbol
{
  friend class Symbol_table;
  
  Symbol(std::string const* str) : m_str(str) { }

public:

  Symbol(): m_str() {}
  
  std::string const& str() const { return *m_str; }

  friend bool operator==(Symbol a, Symbol b) 
  {
    return a.m_str == b.m_str;
  }

  friend bool operator!=(Symbol a, Symbol b) 
  {
    return a.m_str != b.m_str;
  }

  virtual std::string get_str() const { return *m_str; }  

private:
  std::string const* m_str;  
};



class Symbol_table : std::unordered_set<std::string>
{
public:
   Symbol get(std::string const& str);
  
   Symbol get(char const* str);
};

inline Symbol
Symbol_table::get(std::string const& str)
{
  return &*emplace(str).first;
}

inline Symbol
Symbol_table::get(char const* str)
{
  return &*emplace(str).first;
}