#include "builder.hpp"
#include "type.hpp"
#include "expr.hpp"
#include "decl.hpp"

#include <iostream>


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