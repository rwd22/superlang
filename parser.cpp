#include "parser.hpp"
#include "stmt.hpp"
#include "expr.hpp"




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

  if (Token tok = match(Token::dec_literal))
    return m_act.on_integer_literal(tok);

  if (Token tok = match(Token::bool_literal))
    return m_act.on_boolean_literal(tok);

  if (Token tok = match(Token::identifier))
    return m_act.on_id_expression(tok);

  if (match(Token::lparen)) {
    Expr* expr = parse_expression();
    expect(Token::rparen);
    return expr;
  }

  throw std::runtime_error("expected integer");
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
      
      case Token::var_kw:
      case Token::ref_kw:
        return parse_declaration_statement();

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
Parser::parse_declaration_statement()
{
  Decl* d = parse_local_declaration();
  return new Loc_def_stmt(d);
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


//declarations

void
Parser::parse_program()
{
  m_act.enter_scope();
     parse_declaration_sequence();
  m_act.leave_scope();
}

Decl*
Parser::parse_local_declaration()
{
  return parse_variable_declaration();
}

Decl*
Parser::parse_declaration()
{
    switch (lookahead()) {
     case Token::var_kw:
        return parse_variable_declaration();

      case Token::fun_kw:
        return parse_function_definition();

      case Token::let_kw:
        return parse_variable_declaration();
    }
}

Decl* 
Parser::parse_variable_declaration()
{
  switch (lookahead()) {
     case Token::var_kw:
        return parse_object_definition();

      case Token::let_kw:
        return parse_reference_definition();

    }
}

Decl*
Parser::parse_reference_definition()
{
  Token tok = require(Token::let_kw);
  Token id = expect(Token::identifier);
  Token colon = expect(Token::colon);
  Type* type = parse_type();

  Token equal = expect(Token::equal);
  Expr* init = parse_expression();
  Token semi = expect(Token::semicolon);

  Decl* ref = m_act.on_reference_declaration(id, type, init); 

  return ref;
}

Decl*
Parser::parse_object_definition()
{
  Token tok = require(Token::var_kw);
  Token id = expect(Token::identifier);

  Token colon = expect(Token::colon);

  Type* type = parse_type();


  Token equal = expect(Token::equal);

  Expr* init = parse_expression();

  Token semi = expect(Token::semicolon);

  Decl* var = m_act.on_object_declaration(id, type, init); 

  return var;
}

Decl*
Parser::parse_function_definition()
{
  Token tok = require(Token::fun_kw);
  Token id = expect(Token::identifier);
  
  Token lparen = expect(Token::lparen);
  m_act.enter_scope();

  std::vector<Decl*> parms;
  if (next_token_is_not(Token::rparen))
  {
    while (next_token_is_not(Token::rparen)) {
        Token tok = m_lex.get_next_token();
        Decl* decl = m_act.on_identifier(tok);
        expect(Token::colon);
        Type* idtype = parse_type();
        parms.push_back(decl);


    }
  }

      expect(Token::rparen);

  Token rparen = expect(Token::rparen);

  Token arrow = expect(Token::arrow);
  Type* type = parse_type();




  Stmt* body = parse_statement();

  Decl* fn = m_act.on_function_declaration(id, parms, type, body);

  m_act.leave_scope();

  return nullptr; //var;
}



Decl*
Parser::parse_declaration_sequence()
{
  while(true)
  {

    if(Token end = match(Token::eof))
    {
      break;
    }
    else
      return parse_declaration();
  }
}

Type*
Parser::parse_type()
{
  if(Token tok = match(Token::bool_kw))
  {
    Type b = Bool_type();
    return &b;
  }
  if(Token tok = match(Token::int_kw))
  {
    Type i = Int_type();
    return &i;
  }
  if(Token tok = match(Token::float_kw))
  {
    Type f = Float_type();
    return &f;
  }
}