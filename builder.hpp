#pragma once

#include <iosfwd>
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <tuple>

#include "type.hpp"

class Name;
class Type;
class Expr;
class Stmt;
class Decl;
class Var_decl;
class Func_decl;

class Builder
{
public:

  Expr* make_bool(bool b);

  Expr* make_true();

  Expr* make_false();

  Expr* make_int(int n);

  Expr* make_float(float f);

  Expr* convert_to_value(Expr* e);

  Expr* make_and(Expr* e1, Expr* e2);

  Expr* make_or(Expr* e1, Expr* e2);

  Expr* make_not(Expr* e1);

  Expr* make_eq(Expr* e1, Expr* e2);

  Expr* make_lt(Expr* e1, Expr* e2);

  Expr* make_gt(Expr* e1, Expr* e2);

  Expr* make_lte(Expr* e1, Expr* e2);

  Expr* make_gte(Expr* e1, Expr* e2);

  Expr* make_add(Expr* e1, Expr* e2);


Expr* make_sub(Expr* e1, Expr* e2);


Expr* make_mul(Expr* e1, Expr* e2);


Expr* make_div(Expr* e1, Expr* e2);


Expr* make_rem(Expr* e1, Expr* e2);


Expr* make_neg(Expr* e1);


  //Expr* make_cond(Expr* e1, Expr* e2, Expr* e3);









  Expr* require_bool(Expr* e);

  std::pair<Expr*, Expr*> require_common(Expr* e1, Expr* e2);

  std::pair<Expr*, Expr*> require_same_value(Expr* e1, Expr* e2);

  std::pair<Expr*, Expr*> require_same(Expr* e1, Expr* e2);

  std::pair<Expr*, Expr*> require_same_arithmetic(Expr* e1, Expr* e2);

  Expr* require_arithmetic(Expr* e);




private:
  Bool_type m_bool_type;

  Int_type m_int_type;

  Float_type m_float_type;

};

