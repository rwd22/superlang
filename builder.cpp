#include "builder.hpp"
#include "type.cpp"
#include "expr.hpp"
#include "decl.hpp"
#include "stmt.hpp"
#include "name.hpp"

#include <iostream>
#include <vector>

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
Builder::make_cond(Expr* e1, Expr* e2, Expr* e3)
{
  e1 = require_bool(e1);
  std::tie(e2, e3) = require_common(e2, e3);
  return new Con_expr( e1, e2, e3, e2->get_type());
}


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
Builder::make_rec(Expr* e1)
{
  return new Rec_expr(e1, e1->get_type());
}

Expr*
Builder::make_neg(Expr* e1)
{
  e1 = require_arithmetic(e1);
  return new Neg_expr(e1, e1->get_type());
}

Expr*
Builder::make_assign(Expr* e1, Expr* e2)
{
  e2 = convert_to_value(e2);
  e1 = require_reference_to(e1, e2->get_type());
  return new Assign_expr(e1, e2,e1->get_type());
}

Expr*
Builder::make_call(std::vector<Expr*> const& es, Expr* e1)
{

  std::vector<Expr*> conv = es;

  Expr*& fn = conv[0];
  fn = require_function(fn);

  Fun_type* ft = static_cast<Fun_type*>(fn->get_type());

  auto parms = ft->get_param_types();
  auto args = std::vector<Expr*>( conv.begin() + 1, conv.end() );


  if (parms.size() < args.size())
    throw std::runtime_error("Too many arguments given");
  if (parms.size() > args.size())
    throw std::runtime_error("Too few arguments given");

  auto par = parms.begin();
  auto ar = args.begin();
  auto esi = conv.begin();
  while (par != parms.end()) {

    Name n;
    n.str = "Dummy";

    Var_decl dummy(&n, *par, *esi);
    copy_initialize(&dummy, *ar);
    *ar = dummy.get_initializer();

    ++par;
    ++ar;
    ++esi;
  }
  
  return new Fun_call(e1, std::move(conv), ft->get_ret_type());
}







Stmt*
Builder::make_block(std::vector<Stmt*> const& ss)
{
  return new Block_stmt(ss);
}

Stmt*
Builder::make_tern(Expr* e, Stmt* s1, Stmt* s2)
{
  e = require_bool(e);
  return new Ternary_stmt(e, s1, s2);
}

Stmt*
Builder::make_while(Expr* e, Stmt* s1)
{
  e = require_bool(e);
  return new While_stmt(e, s1);
}

Stmt*
Builder::make_break()
{
  return new Break_stmt();
}

Stmt*
Builder::make_continue()
{
  return new Cont_stmt();
}

Stmt*
Builder::make_expression(Expr* e)
{
  return new Expr_stmt(e);
}

Stmt*
Builder::make_local_def(Decl* d)
{
  return new Loc_def_stmt(d);
}

Stmt*
Builder::make_return(Decl* d, Expr* e)
{
  assert(d->is_variable());
  Var_decl* var = static_cast<Var_decl*>(d);
  
  copy_initialize(var, e);
  
  return new Return_stmt(var->get_initializer());
}






Decl*
Builder::make_variable(Name* n, Type* t, Expr* e)
{
  return new Var_decl(n, t, e);
}

Decl*
Builder::make_reference(Name* n, Type* t, Expr* e)
{
  return new Ref_decl(n, t, e);
}

Decl*
Builder::make_function(Name* n, Type* t, std::vector<Decl*> decls, Stmt* s)
{
  return new Func_decl(n, t, decls, s);
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

Expr*
Builder::require_reference_to(Expr* e, Type* t)
{
  Type* t1 = e->get_type();
  if (t1->is_reference_to(t))
    return e;
  throw std::runtime_error("invalid reference");
}

Expr*
Builder::require_value_of(Expr* e, Type* t)
{
  assert(t->is_object());

  e = convert_to_value(e);

  if (!(e->get_type() == t))
    throw std::runtime_error("invalid operand");

  return e;
}


Expr*
Builder::require_type(Expr* e, Type* t)
{
  if (t->is_reference())
    return require_reference_to(e, t);
  else
    return require_value_of(e, t);
}



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
}

Expr*
Builder::require_function(Expr* e)
{
  Expr* c = convert_to_value(e);

  Type* t = c->get_type();
  if (t->is_function())
    return c;

  throw std::runtime_error("Expression is not a function");
}

















void
Builder::copy_initialize(Decl* d, Expr* e)
{
  assert(d->is_variable());
  Var_decl* var = static_cast<Var_decl*>(d);

  if (d->is_reference())
    return reference_initialize(d, e);

  e = require_type(e, d->get_type());

  var->set_initializer(e);
}

void
Builder::reference_initialize(Decl* d, Expr* e)
{
  assert(d->is_variable());
  Var_decl* var = static_cast<Var_decl*>(d);

  e = require_type(e, d->get_type());

  var->set_initializer(e);
}