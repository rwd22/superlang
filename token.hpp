
#pragma once

#include "symbol.hpp"
#include "location.hpp"

class Token
{
public:
  enum Name
  {
    eof,


    // punctuation
    lbrace,
    rbrace,
    lparen,
    rparen,
    colon,
    semicolon,
    comma,
    arrow,

    // operators
    plus,
    minus,
    star,
    slash,
    percent,
    question,
    equal,
    equal_equal,
    bang_equal,
    less,
    greater,
    less_equal,
    greater_equal,
    and_op,
    or_op,
    not_op,

    // keywords
    and_kw,
    bool_kw,
    break_kw,
    continue_kw,
    else_kw,
    false_kw,
    fun_kw,
    float_kw,
    if_kw,
    int_kw,
    let_kw,
    not_kw,
    or_kw,
    ref_kw,
    return_kw,
    true_kw,
    var_kw,
    while_kw,

    // lit
    bool_literal,
    integer_literal,
    float_literal,
    hex_literal,
    bin_literal,
    dec_literal,

    
    // identifiers
    digit,
    nondigit,
    identifier,

    //comment
    comment,
    commentchar,
  };

  Token(Name n, Symbol sym, Location = {})
    : m_name(n), m_lex(sym), m_loc()
  { }

  Token() : m_name(eof), m_lex(), m_loc(){}

  explicit operator bool() const { return m_name != eof; }

  Name get_name() const { return m_name; }

  bool is_keyword() const;

  bool is_logical_operator() const;

  Symbol get_lexeme() const { return m_lex; }

private:
  Name m_name;
  Symbol m_lex;
  Location m_loc;
};

std::ostream& operator<<(std::ostream& os, Token const& tok);