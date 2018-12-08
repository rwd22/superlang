#include "parser.hpp"
#include "stmt.hpp"



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
  Expr *expr = parse_conditional_expression();
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
Parser::parse_relational_expression() 
{
  parse_additive_expression();

  Expr* lhs = parse_relational_expression();  
  while (true) {
    if (Token lt = match(Token::less)) {      
      Expr* rhs = parse_additive_expression();
      lhs = m_act.on_less_expression(lhs, rhs); 
    }
    if (Token gt = match(Token::greater)) {      
      Expr* rhs = parse_additive_expression();
      lhs = m_act.on_greater_expression(lhs, rhs); 
    }
    if (Token lte = match(Token::less_equal)) {      
      Expr* rhs = parse_additive_expression();
      lhs = m_act.on_lte_expression(lhs, rhs); 
    }
    if (Token gte = match(Token::greater_equal)) {      
      Expr* rhs = parse_additive_expression();
      lhs = m_act.on_gte_expression(lhs, rhs); 
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
  if (Token op = match(Token::not_kw)) {
    Expr* arg = parse_prefix_expression();
    return m_act.on_not_expression(arg);
  }
  parse_postfix_expression();
}

Expr*
Parser::parse_postfix_expression()
{
  Expr* lhs = parse_primary_expression();
  while (true) {
    if (match(Token::lparen)) {
      std::vector<Expr*> argl;
      while (next_token_is_not(Token::rparen)) {
        Expr * e = parse_expression();
        argl.push_back(e);
    }

      expect(Token::rparen);
      return m_act.on_post_expression(std::move(argl),lhs);
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

Expr*
Parser::parse_equality_expression()
{
  parse_relational_expression();

  Expr* lhs = parse_equality_expression();  
  while (true) {
    if (Token equal = match(Token::equal_equal)) {      
      Expr* rhs = parse_relational_expression();
      lhs = m_act.on_equal_equal_expression(lhs, rhs);
    }
    if (Token no_eq = match(Token::bang_equal)) {      
      Expr* rhs = parse_relational_expression();
      lhs = m_act.on_bang_equal_expression(lhs, rhs);
    }
  }
}

Expr*
Parser::parse_and_expression()
{
  parse_equality_expression();

  Expr* lhs = parse_and_expression();  
  while (true) {
    if (Token kwand = match(Token::and_kw)) {      
      Expr* rhs = parse_equality_expression();
      lhs = m_act.on_and_expression(lhs, rhs); 
    }
  }
}

Expr*
Parser::parse_or_expression()
{
  parse_and_expression();

  Expr* lhs = parse_or_expression();  
  while (true) {
    if (Token kwor = match(Token::or_kw)) {      
      Expr* rhs = parse_and_expression();
      lhs = m_act.on_or_expression(lhs, rhs); 
    }
  }
}

Expr*
Parser::parse_conditional_expression()
{
  parse_or_expression();

  Expr* lhs = parse_or_expression();  
  while (true) {
    if (Token quest = match(Token::question)) {      
      Expr* rhs1 = parse_expression();
      if(Token col = match(Token::colon))
      {
        Expr* rhs2 = parse_and_expression();
        lhs = m_act.on_cond_expression(lhs, rhs1, rhs2);
      }
      
    }
  }
}



//statements

Stmt*
Parser::parse_statement()
{
  switch (lookahead()) {
     case Token::semicolon:
        return parse_empty_statement();

      case Token::lbrace:
        return parse_block_statement();

      case Token::if_kw:
        return parse_if_statement();

      case Token::while_kw:
        return parse_while_statement();
      
      case Token::break_kw:
        return parse_break_statement();

      case Token::continue_kw:
        return parse_continue_statement();

      case Token::return_kw:
        return parse_return_statement();
      
     // case Token::var_kw:
      //case Token::ref_kw:
       // return parse_declaration_statement();

      default:
        return parse_expression_statement();
    }
}


Stmt*
Parser::parse_if_statement()
{
    require(Token::if_kw);
    expect(Token::lparen);
    Expr* expr = parse_expression();
    expect(Token::rparen);
    Stmt* stmt1 = parse_statement();
    expect(Token::else_kw);
    Stmt* stmt2 = parse_statement();

    return m_act.on_if_statement(expr, stmt1, stmt2);
    
}

Stmt*
Parser::parse_while_statement()
{
    require(Token::while_kw);
    expect(Token::lparen);
    Expr* expr = parse_expression();
    expect(Token::rparen);
    Stmt* stmt = parse_statement();

    return m_act.on_while_statement(expr, stmt);
    
}

Stmt*
Parser::parse_break_statement()
{
  require(Token::break_kw);
  expect(Token::semicolon);

  return m_act.on_break_statement();
}

Stmt*
Parser::parse_continue_statement()
{
  require(Token::continue_kw);
  expect(Token::semicolon);

  return m_act.on_continue_statement();
}

Stmt*
Parser::parse_expression_statement()
{
  Expr* expr = parse_expression();
  expect(Token::semicolon);

  return m_act.on_expression_statement(expr);
}

Stmt*
Parser::parse_empty_statement()
{
  require(Token::semicolon);
  return m_act.on_skip_statement();
}

Stmt*
Parser::parse_block_statement()
{
  require(Token::lbrace);

  std::vector<Stmt*> ss;
  while (next_token_is_not(Token::rbrace)) {
    Stmt * s = parse_statement();
    ss.push_back(s);
  }

  expect(Token::rbrace);
  return m_act.on_block_statement(std::move(ss));
}

Stmt*
Parser::parse_return_statement()
{
  require(Token::return_kw);
  Expr* ret = parse_expression();
  expect(Token::semicolon);
  return new Return_stmt(ret);
}


