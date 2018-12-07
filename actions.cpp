#include "actions.hpp"
#include "expr.hpp"
#include "stmt.hpp"
#include "type.hpp"

Expr*
Actions::on_boolean_literal(Token const& tok)
{
  if (tok.get_name() == Token::true_kw)
    return m_build.make_true();
  else
    return m_build.make_false();
}

Expr*
Actions::on_integer_literal(Token const& tok)
{
  int n = std::stoi(tok.get_lexeme().str());
  return m_build.make_int(n);
}

//impliment this once stack stuff is done

/*Expr*
Actions::on_id_expression(Token const& tok)
{
  Decl* decl = m_stack.lookup(tok.get_lexeme());
  if (!decl)
    throw std::runtime_error("no matching declaration");
  return m_builder.make_id(decl);
}*/

Expr* 
Actions::on_negation_expression(Expr* arg)
{
  return m_build.make_neg(arg);
}

Expr*
Actions::on_reciprocal_expression(Expr* arg)
{
  return m_build.make_rec(arg);
}

Expr*
Actions::on_multiplication_expression(Expr* e1, Expr* e2)
{
  return m_build.make_mul(e1, e2);
}

Expr*
Actions::on_division_expression(Expr* e1, Expr* e2)
{
  return m_build.make_div(e1, e2);

}

Expr*
Actions::on_remainder_expression(Expr* e1, Expr* e2)
{
  return m_build.make_rem(e1, e2); 
}

Expr* 
Actions::on_less_expression(Expr* e1, Expr* e2)
{
	return m_build.make_lt(e1, e2);
}

Expr* 
Actions::on_greater_expression(Expr* e1, Expr* e2)
{
	return m_build.make_gt(e1, e2);
}

Expr* 
Actions::on_lte_expression(Expr* e1, Expr* e2)
{
	return m_build.make_lte(e1, e2);
}

Expr* 
Actions::on_gte_expression(Expr* e1, Expr* e2)
{
	return m_build.make_gte(e1, e2);
}

Expr* 
Actions::on_equal_equal_expression(Expr* e1, Expr* e2)
{
	return m_build.make_eq(e1, e2);
}

Expr* 
Actions::on_bang_equal_expression(Expr* e1, Expr* e2)
{
	return m_build.make_ne(e1, e2);
}

Expr* 
Actions::on_and_expression(Expr* e1, Expr* e2)
{
	return m_build.make_and(e1, e2);
}

Expr* 
Actions::on_or_expression(Expr* e1, Expr* e2)
{
	return m_build.make_or(e1, e2);
}

Expr* 
Actions::on_cond_expression(Expr* e1, Expr* e2, Expr* e3)
{
	return m_build.make_cond(e1, e2, e3);
}

Expr* 
Actions::on_not_expression(Expr* e1)
{
	return m_build.make_not(e1);
}

//statements

Stmt* 
Actions::on_if_statement(Expr* e1, Stmt* s1, Stmt* s2)
{
	return m_build.make_tern(e1, s1, s2);
}

Stmt* 
Actions::on_while_statement(Expr* e1, Stmt* s1)
{
	return m_build.make_while(e1, s1);
}

Stmt* 
Actions::on_break_statement()
{
	return m_build.make_break();
}

Stmt* 
Actions::on_continue_statement()
{
	return m_build.make_continue();
}

Stmt* 
Actions::on_expression_statement(Expr* e1)
{
	return m_build.make_expression(e1);
}
//Declaration Stuff here
