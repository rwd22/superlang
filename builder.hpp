#pragma once

#include <iosfwd>
#include <vector>

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

  Expr* require_bool(Expr* e);




private:
  Bool_type m_bool_type;

  Int_type m_int_type;

  Float_type m_float_type;

};

