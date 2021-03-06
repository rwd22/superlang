#pragma

#include "token.hpp"
#include "builder.hpp"
#include "scope.hpp"


class Expr;
class Stmt;
class Decl;
class Type;

class Actions
{
public:
  Expr* on_boolean_literal(Token const& tok);

  Expr* on_integer_literal(Token const& tok);

  Expr* on_id_expression(Token const& tok);

  Expr* on_negation_expression(Expr* arg); 
  
  Expr* on_reciprocal_expression(Expr* arg);

  Expr* on_multiplication_expression(Expr* e1, Expr* e2);

  Expr* on_division_expression(Expr* e1, Expr* e2);

  Expr* on_remainder_expression(Expr* e1, Expr* e2);

  Expr* on_less_expression(Expr* e1, Expr* e2);

  Expr* on_greater_expression(Expr* e1, Expr* e2);

  Expr* on_lte_expression(Expr* e1, Expr* e2);

  Expr* on_gte_expression(Expr* e1, Expr* e2);

  Expr* on_equal_equal_expression(Expr* e1, Expr* e2);

  Expr* on_bang_equal_expression(Expr* e1, Expr* e2);

  Expr* on_and_expression(Expr* e1, Expr* e2);

  Expr* on_or_expression(Expr* e1, Expr* e2);

  Expr* on_cond_expression(Expr* e1, Expr* e2, Expr* e3);

  Expr* on_not_expression(Expr* e1);

  Expr* on_post_expression(std::vector<Expr*> argl, Expr* e1);


  //statements

  Stmt* on_if_statement(Expr* e1, Stmt* s1, Stmt* s2);

  Stmt* on_while_statement(Expr* e1, Stmt* s1);

  Stmt* on_break_statement();

  Stmt* on_continue_statement();

  Stmt* on_skip_statement();

  Stmt* on_expression_statement(Expr* e1);

  Stmt* on_block_statement(std::vector<Stmt*> ss);

  //declarations

  Decl* on_object_declaration(Token id, Type* t1, Expr* e1);

  Decl* on_function_declaration(Token id,  std::vector<Decl*> parms, Type* t1, Stmt* s);

  Decl* on_reference_declaration(Token id, Type* t1, Expr* e1);

  Decl* on_identifier(Token const& tok);



//scope stuff here

  void enter_scope() { m_stack.emplace_back(); }
  
  void leave_scope() { m_stack.pop_back(); }
  
  Scope* get_current_scope() { return &m_stack.back(); }


private:
  Builder m_build;

  Scope_stack m_stack;
};