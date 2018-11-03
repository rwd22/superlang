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



















































Expr*
Builder::require_bool(Expr* e)
{
  Expr* c = convert_to_value(e);

  Type* t = c->get_type();
  if (!t->is_bool())

    throw std::runtime_error("operand not boolean");

  return c;
}