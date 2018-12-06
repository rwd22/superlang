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

Expr* make_ne(Expr* e1, Expr* e2);

Expr* make_lt(Expr* e1, Expr* e2);

Expr* make_gt(Expr* e1, Expr* e2);

Expr* make_lte(Expr* e1, Expr* e2);

Expr* make_gte(Expr* e1, Expr* e2);

Expr* make_add(Expr* e1, Expr* e2);

Expr* make_sub(Expr* e1, Expr* e2);

Expr* make_mul(Expr* e1, Expr* e2);

Expr* make_div(Expr* e1, Expr* e2);

Expr* make_rem(Expr* e1, Expr* e2);

Expr* make_rec(Expr* e1);

Expr* make_neg(Expr* e1);

Expr* make_cond(Expr* e1, Expr* e2, Expr* e3);

Expr* make_assign(Expr* e1, Expr* e2);

Expr* make_call(std::vector<Expr*> const& es, Expr* e1);










Stmt* make_block(std::vector<Stmt*> const& ss);

Stmt* make_tern(Expr* e, Stmt* s1, Stmt* s2);

Stmt* make_while(Expr* e, Stmt* s1);

Stmt* make_break();

Stmt* make_continue();

Stmt* make_expression(Expr* e);

Stmt* make_local_def(Decl* d);

Stmt* make_return(Decl* d, Expr* e);


Decl* make_variable(Name* n, Type* t, Expr* e);

Decl* make_function(Name* n, Type* t, std::vector<Decl*> decls, Stmt* s);

Decl* make_reference(Name* n, Type* t, Expr* e);











std::pair<Expr*, Expr*> require_common(Expr* e1, Expr* e2);

std::pair<Expr*, Expr*> require_same_value(Expr* e1, Expr* e2);

std::pair<Expr*, Expr*> require_same(Expr* e1, Expr* e2);

std::pair<Expr*, Expr*> require_same_arithmetic(Expr* e1, Expr* e2);

Expr* require_bool(Expr* e);

Expr* require_arithmetic(Expr* e);

Expr* require_reference_to(Expr* e, Type* t);

Expr* require_type(Expr* e, Type* t);

Expr* require_value_of(Expr* e, Type* t);

Expr* require_function(Expr* e);


void reference_initialize(Decl* d, Expr* e);

void copy_initialize(Decl* d, Expr* e);



private:
  Bool_type m_bool_type;

  Int_type m_int_type;

  Float_type m_float_type;

};

