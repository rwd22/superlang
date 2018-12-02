#include "parser.hpp"

#include <iostream>

Parser::Parser(Symbol_table& syms, 
               std::string const& input)
  : m_lex(syms, input)
{
  while (Token tok = m_lex.get_next_token())
    m_toks.push_back(tok);

  m_lookahead = m_toks.data();
  m_last = m_lookahead + m_toks.size();
}

Token 
Parser::consume()
{
  assert(!is_eof());
  Token ret = *m_lookahead;
  ++m_lookahead;
  return ret;
}

Token 
Parser::match(Token::Name n)
{
  if (next_token_is(n))
    return consume();
  return Token();
}

Token 
Parser::expect(Token::Name n)
{
  if (next_token_is(n))
    return consume();

  throw std::runtime_error("syntax error");
  return Token();
}

Token 
Parser::require(Token::Name n)
{
  assert(next_token_is(n));
  return consume();
}

//Expressions

Expr*
Parser::parse_expression()
{
  return parse_assignment_expression();
}

Expr*
Parser::parse_assignment_expression()
{
  Expr *expr = parse_additive_expression();
  if (match(Token::equal))
    return parse_assignment_expression();
  return expr;
}

Expr* 
Parser::parse_additive_expression()
{
  parse_multiplicative_expression();

  while (match(Token::plus) || match(Token::minus))
    parse_multiplicative_expression();
}

Expr*
Parser::parse_multiplicative_expression()
{
  Expr* lhs = parse_prefix_expression();  
  while (true) {
    if (Token star = match(Token::star)) {      
      Expr* rhs = parse_prefix_expression();
      lhs = m_act.on_multiplication_expression(lhs, rhs);
    }
    if (Token slash = match(Token::slash)) {      
      Expr* rhs = parse_prefix_expression();
      lhs = m_act.on_division_expression(lhs, rhs);
    }
    if (Token percent = match(Token::percent)) {      
      Expr* rhs = parse_prefix_expression();
      lhs = m_act.on_remainder_expression(lhs, rhs);
    }
  }
}

Expr*
Parser::parse_prefix_expression()
{
  if (Token op = match(Token::minus)) {
    Expr* arg = parse_prefix_expression();
    return m_act.on_negation_expression(arg);
  }
  if (Token op = match(Token::slash)) {
    Expr* arg = parse_prefix_expression();
    return m_act.on_reciprocal_expression(arg);
  }
  parse_postfix_expression();
}

Expr*
Parser::parse_postfix_expression()
{
  parse_primary_expression();
  while (true) {
    if (match(Token::lparen)) {
      // parse list of arguments here
      expect(Token::rparen);
      // return nullptr
    }
    else {
      break;
    }
  }
  return nullptr;
}


Expr*
Parser::parse_primary_expression()
{
  if (Token tok = match(Token::integer_literal))
    return m_act.on_integer_literal(tok);

  //if (Token tok = match(Token::identifier)) //impliment later
   // return m_act.on_id_expression(tok);

  if (match(Token::lparen)) {
    Expr* expr = parse_expression();
    expect(Token::rparen);
    return expr;
  }

  throw std::runtime_error("expected factor");
}