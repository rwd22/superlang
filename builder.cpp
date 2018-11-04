#include "builder.hpp"
#include "type.hpp"
#include "expr.hpp"
#include "decl.hpp"

#include <iostream>

Expr*
Builder::convert_to_value(Expr* e)
{
  Type* t = e->get_type();
  if (t->is_reference()) {
    Ref_type* ref = static_cast<Ref_type*>(t);
    return new Val_conv(e, ref->get_referent_type());
  }
  return e;
}

Expr*
Builder::make_bool(bool b)
{
  Type bt = Bool_type();

  return new Bool_lit(b, &bt);
}

Expr*
Builder::make_true()
{
  return make_bool(true);
}

Expr*
Builder::make_false()
{
  return make_bool(false);
}

Expr*
Builder::make_int(int n)
{

  Type i = Int_type();

  return new Int_lit(n, &i);
}

Expr*
Builder::make_float(float f)
{

  Type i = Float_type();

  return new Fl_lit(f, &i);
}

Expr*
Builder::make_and(Expr* e1, Expr* e2)
{
  e1 = require_bool(e1);
  e2 = require_bool(e2);
  return new And_expr(e1, e2, e1->get_type());
}

Expr*
Builder::make_or(Expr* e1, Expr* e2)
{
  e1 = require_bool(e1);
  e2 = require_bool(e2);
  return new Or_expr(e1, e2, e1->get_type());
}

Expr*
Builder::make_not(Expr* e1)
{
  e1 = require_bool(e1);
  return new Not_expr(e1, e1->get_type());
}

/*Expr*
Builder::make_cond(Expr* e1, Expr* e2, Expr* e3)
{
  e1 = require_bool(e1);
  std::tie(e2, e3) = require_common(e2, e3);
  return new Con_expr( e1, e2, e3, e2->get_type());
}*/


Expr*
Builder::make_eq(Expr* e1, Expr* e2)
{
  Type bt = Bool_type();
  std::tie(e1, e2) = require_same(e1, e2);
  return new Eq_expr( e1, e2, &bt);
}

Expr*
Builder::make_lt(Expr* e1, Expr* e2)
{
  Type bt = Bool_type();
  std::tie(e1, e2) = require_same(e1, e2);
  return new Lt_expr( e1, e2, &bt);
}

Expr*
Builder::make_gt(Expr* e1, Expr* e2)
{
  Type bt = Bool_type();
  std::tie(e1, e2) = require_same(e1, e2);
  return new Gt_expr(e1, e2, &bt);
}

Expr*
Builder::make_lte(Expr* e1, Expr* e2)
{
  Type bt = Bool_type();
  std::tie(e1, e2) = require_same(e1, e2);
  return new Lte_expr(e1, e2, &bt);
}

Expr*
Builder::make_gte(Expr* e1, Expr* e2)
{
  Type bt = Bool_type();
  std::tie(e1, e2) = require_same(e1, e2);
  return new Gte_expr(e1, e2, &bt);
}

Expr*
Builder::make_add(Expr* e1, Expr* e2)
{
  std::tie(e1, e2) = require_same_arithmetic(e1, e2);
  return new Add_expr( e1, e2,e1->get_type());
}

Expr*
Builder::make_sub(Expr* e1, Expr* e2)
{
  std::tie(e1, e2) = require_same_arithmetic(e1, e2);
  return new Sub_expr( e1, e2, e1->get_type());
}

Expr*
Builder::make_mul(Expr* e1, Expr* e2)
{
  std::tie(e1, e2) = require_same_arithmetic(e1, e2);
  return new Mul_expr(e1, e2, e1->get_type());
}

Expr*
Builder::make_div(Expr* e1, Expr* e2)
{
  std::tie(e1, e2) = require_same_arithmetic(e1, e2);
  return new Div_expr(e1, e2, e1->get_type());
}

Expr*
Builder::make_rem(Expr* e1, Expr* e2)
{
  std::tie(e1, e2) = require_same_arithmetic(e1, e2);
  return new Rem_expr(e1, e2, e1->get_type());
}

Expr*
Builder::make_neg(Expr* e1)
{
  e1 = require_arithmetic(e1);
  return new Neg_expr(e1, e1->get_type());
}













































Expr*
Builder::require_bool(Expr* e)
{
  Expr* c = convert_to_value(e);

  Type* t = c->get_type();
  if (!t->is_bool())

    throw std::runtime_error("operand not boolean");

  return c;
}

std::pair<Expr*, Expr*>
Builder::require_same(Expr* e1, Expr* e2)
{
  Type* t1 = e1->get_type();
  Type* t2 = e2->get_type();
  if (t1 != t2)
    throw std::runtime_error("operands differ in type");
  return {e1, e2};
}

std::pair<Expr*, Expr*>
Builder::require_same_arithmetic(Expr* e1, Expr* e2)
{
  e1 = convert_to_value(e1);
  e2 = convert_to_value(e2);
  auto p = require_same(e1, e2);

  Type* t = p.first->get_type();
  if (!t->is_arithmetic())
    throw std::runtime_error("operands are not arithmetic");
  
  return p;
}

Expr*
Builder::require_arithmetic(Expr* e)
{
  Expr* c = convert_to_value(e);

  Type* t = c->get_type();
  if (!t->is_arithmetic())
    throw std::runtime_error("operand not arithmetic");

  return c;
}

/*
std::pair<Expr*, Expr*>
Builder::require_same_value(Expr* e1, Expr* e2)
{
  e1 = convert_to_value(e1);
  e2 = convert_to_value(e2);
  return require_same(e1, e2);
}


std::pair<Expr*, Expr*>
Builder::require_common(Expr* e1, Expr* e2)
{
  Type* t1 = e1->get_type();
  Type* t2 = e2->get_type();
  
  if (t1->is_reference() && t2->is_reference())
    return require_same(e1, e2);

  return require_same_value(e1, e2);
}*/