#include "lexer.hpp"

#include <iostream>
#include <locale>

Lexer::Lexer(Symbol_table& syms,
    char const* first,
    char const* limit)
  : m_syms(&syms),
    m_first(first),
    m_limit(limit),
    m_line(1)
{
  m_kws.emplace("and", Token::and_kw);
  m_kws.emplace("bool", Token::bool_kw);
  m_kws.emplace("break", Token::break_kw);
  m_kws.emplace("continue", Token::continue_kw);
  m_kws.emplace("else", Token::else_kw);
  m_kws.emplace("false", Token::false_kw);
  m_kws.emplace("fun", Token::fun_kw);
  m_kws.emplace("float", Token::float_kw);
  m_kws.emplace("if", Token::if_kw);
  m_kws.emplace("int", Token::int_kw);
  m_kws.emplace("let", Token::let_kw);
  m_kws.emplace("not", Token::not_kw);
  m_kws.emplace("or", Token::or_kw);
  m_kws.emplace("ref", Token::ref_kw);
  m_kws.emplace("return", Token::return_kw);
  m_kws.emplace("true", Token::true_kw);
  m_kws.emplace("var", Token::var_kw);
  m_kws.emplace("while", Token::while_kw);
}

Lexer::Lexer(Symbol_table& syms, std::string const& str)
  : Lexer(syms, str.data(), str.data() + str.size())
{ }

static bool
is_nondigit(char c)
{
  return std::isalpha(c) || c == '_';
}

static bool
is_digit(char c)
{
  return std::isdigit(c);
}

static bool
is_nondigit_or_digit(char c)
{
  return is_nondigit(c) || isdigit(c);
}

static bool
is_hexdigit(char c)
{
  return std::isxdigit(c);
}

char 
Lexer::peek() const
{ 
  if (is_eof())
    return 0;
  return *m_first; 
}

char 
Lexer::peek(int n) const
{
  if (m_limit - m_first <= n)
    return 0;
  return *(m_first + n); 
}


Token
Lexer::match(Token::Name n, int len)
{
  std::string str(m_first, m_first + len);
  Symbol sym = m_syms->get(str);
  Token tok = Token(n, sym);

  m_first += len;
  
  return tok;
}



Token
Lexer::match_word()
{
  char const* iter1 = m_first + 1;
  while (!is_eof(iter1) && is_nondigit_or_digit(*iter1))
    ++iter1;

  

  std::string id(m_first, iter1);
  Symbol sym = m_syms->get(id);

  m_first = iter1;

  Token::Name kind;
  auto iter = m_kws.find(id);
  if (iter == m_kws.end())
    kind = Token::identifier;
  else
    kind = iter->second;

  return Token(kind, sym);
}


Token
Lexer::match_number() //TEMPORARY think it needs to look and see if its dec hex or float
{
  char const* iter1 = m_first + 1;
  Token::Name kind;
  if(*iter1 == '0')
  {
    iter1++;

    if(*iter1 == 'x' || *iter1 == 'X')
    {
      kind = Token::hex_literal;

      while (!is_eof(iter1) && is_hexdigit(*iter1))
        ++iter1;

      m_first = iter1;  //advance

      std::string id(m_first, iter1); //build
      Symbol sym = m_syms->get(id);

      return Token(kind, sym);
    }

    if(*iter1 == 'b' || *iter1 == 'B')
    {
      kind = Token::bin_literal;

      while (!is_eof(iter1) && (*iter1 == '1' || *iter1 == '0') )
        ++iter1;

      std::string id(m_first, iter1); //build
      Symbol sym = m_syms->get(id);

      return Token(kind, sym);
    }
  }
  
}

Token
Lexer::comment_match()
{
  char const* iter1 = m_first + 1;
  while(!is_eof(iter1) && *iter1!='\n')
    ++iter1;

  m_first = iter1;

  std::string id(m_first, iter1);
  Symbol sym = m_syms->get(id);

  Token::Name kind = Token::comment;

  return Token(kind, sym);
}


Token
Lexer::get_next_token()
{
  while (true) {
    switch (peek()) {
    case ' ':
    case '\t':
      consume();
      continue;

    case '\n':
      ++m_line;
      consume();
      continue;

    case '#':
        return comment_match();
    case '{':
      return match(Token::lbrace, 1);
    case '}':
      return match(Token::rbrace, 1);
    case '(':
      return match(Token::lparen, 1);
    case ')':
      return match(Token::rparen, 1);
    case ',':
      return match(Token::comma, 1);
    case ';':
      return match(Token::semicolon, 1);
    case ':':
      return match(Token::colon, 1);
    case '+':
      return match(Token::plus, 1);
    case '-':
      return match(Token::minus, 1);
    case '*':
      return match(Token::star, 1);
    case '/':
      return match(Token::slash, 1);
    case '%':
      return match(Token::percent, 1);
    case '<':
      if (peek(1) == '=')
        return match(Token::less_equal, 2);
      return match(Token::less, 1);
    case '>':
      if (peek(1) == '=')
        return match(Token::greater_equal, 2);
      return match(Token::lbrace, 1);
    case '=':
      if (peek(1) == '=')
        return match(Token::equal_equal, 2);
      return match(Token::equal, 1);
    case '!':
      if (peek(1) == '=')
        return match(Token::bang_equal, 2);
      
      consume();
      std::cerr << "error: " << m_line << ": " << "expected '=' after '!'\n";
      continue;



    default:
      if (is_nondigit(*m_first))
        return match_word();
      
      if (is_digit(*m_first))
       return match_number();

      std::cerr << "error: " << m_line << ": invalid character";
      consume();
      continue;
    }
  }
}

