#pragma once

#include "token.hpp"

#include <unordered_map>

class Lexer
{
public:
  Lexer(Symbol_table& syms, char const* first, char const* limit);
  
  Lexer(Symbol_table& syms, std::string const& str);

  Token get_next_token();

private:
  bool is_eof(char const* ptr) const { return ptr == m_limit; }

  bool is_eof() const { return is_eof(m_first); }

  char peek() const;

  char peek(int n) const;

  char consume() { return *m_first++; }

  Token match(Token::Name n, int len);

  Token match_word();

  Token match_number();

  Token comment_match();

private:
  Symbol_table* m_syms;

  char const* m_first;
  char const* m_limit;

  int m_line;

  std::unordered_map<std::string, Token::Name> m_kws;
};

