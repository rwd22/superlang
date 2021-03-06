#pragma once

#include "token.hpp"
#include "lexer.hpp"
#include "actions.hpp"
#include "type.hpp"
#include "expr.hpp"


#include <cassert>
#include <vector>

class Symbol_table;
class Stmt;
class Decl;

class Parser
{
public:
  Parser(Symbol_table& syms, std::string const& input);


private:

  bool is_eof() const { return m_lookahead == m_last; }

  const Token& peek() const { return *m_lookahead; }

  Token::Name lookahead() const { return peek().get_name(); }

  bool next_token_is(Token::Name n) const { return lookahead() == n; }

  bool next_token_is_not(Token::Name n) { return lookahead() != n; }

  Token consume();

  Token match(Token::Name n);

  Token expect(Token::Name n);

  Token require(Token::Name n);


public:

  void parse_program();

  Expr* parse_expression();

  Expr* parse_assignment_expression();

  Expr* parse_additive_expression();
  
  Expr* parse_multiplicative_expression();

  Expr* parse_relational_expression();

  Expr* parse_prefix_expression();

  Expr* parse_postfix_expression();

  Expr* parse_primary_expression();

  Expr* parse_equality_expression();

  Expr* parse_and_expression();

  Expr* parse_or_expression();

  Expr* parse_conditional_expression();

  //statements

  Stmt* parse_statement();

  Stmt* parse_if_statement();

  Stmt* parse_while_statement();

  Stmt* parse_break_statement();

  Stmt* parse_continue_statement();

  Stmt* parse_expression_statement();

  Stmt* parse_empty_statement();

  Stmt* parse_block_statement();

  Stmt* parse_return_statement();

  Stmt* parse_declaration_statement();

  //declarations

  Decl* parse_declaration();

 Decl* parse_declaration_sequence();

  Decl* parse_local_declaration();

  Decl* parse_object_definition();

  Decl* parse_function_definition();

  Decl* parse_variable_declaration();

  Decl* parse_reference_definition();

  Type* parse_type();


private:
  Lexer m_lex;

  std::vector<Token> m_toks;

  Token* m_lookahead;

  Token* m_last;

  Actions m_act;
};
