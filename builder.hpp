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




private:
  Bool_type m_bool_type;

  Int_type m_int_type;

  Float_type m_float_type;
};

