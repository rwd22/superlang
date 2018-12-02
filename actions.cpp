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


//Declaration Stuff here
