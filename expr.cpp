#include "expr.hpp"
#include "name.hpp"
#include "type.hpp"

#include <iostream>
#include <iterator>

//basic prints

static void
print_str(std::ostream& os, char const* str)
{
  os << str;
}

static void
print_bool_lit(std::ostream& os, Bool_lit const* e)
{
  os << e->get_val();
}

static void
print_int_lit(std::ostream& os, Int_lit const* e)
{
  os << e->get_val();
}

static void
print_fl_lit(std::ostream& os, Fl_lit const* e)
{
  os << e->get_val();
}

static void
print_add(std::ostream& os, Add_expr const* e)
{
  os << "(" << *e->get_expr1() << " + " << *e->get_expr2() << ")";
}

static void
print_sub(std::ostream& os, Sub_expr const* e)
{
  os << "(" << *e->get_expr1() << " - " << *e->get_expr2() << ")";
}

static void
print_mul(std::ostream& os, Mul_expr const* e)
{
  os << "(" << *e->get_expr1() << " * " << *e->get_expr2() << ")";
}

static void
print_div(std::ostream& os, Div_expr const* e)
{
  os << "(" << *e->get_expr1() << " div " << *e->get_expr2() << ")";
}

static void
print_rem(std::ostream& os, Rem_expr const* e)
{
  os << "(" << *e->get_expr1() << " rem " << *e->get_expr2() << ")";
}

static void
print_gt(std::ostream& os, Gt_expr const* e)
{
  os << "(" << *e->get_expr1() << " > " << *e->get_expr2() << ")";
}

static void
print_lt(std::ostream& os, Lt_expr const* e)
{
  os << "(" << *e->get_expr1() << " < " << *e->get_expr2() << ")";
}

static void
print_gte(std::ostream& os, Gte_expr const* e)
{
  os << "(" << *e->get_expr1() << " >= " << *e->get_expr2() << ")";
}

static void
print_lte(std::ostream& os, Lte_expr const* e)
{
  os << "(" << *e->get_expr1() << " <= " << *e->get_expr2() << ")";
}

static void
print_eq(std::ostream& os, Eq_expr const* e)
{
  os << "(" << *e->get_expr1() << " = " << *e->get_expr2() << ")";
}

static void
print_ne(std::ostream& os, Ne_expr const* e)
{
  os << "(" << *e->get_expr1() << " != " << *e->get_expr2() << ")";
}

static void
print_and(std::ostream& os, And_expr const* e)
{
  os << "(" << *e->get_expr1() << " AND " << *e->get_expr2() << ")";
}

static void
print_or(std::ostream& os, Or_expr const* e)
{
  os << "(" << *e->get_expr1() << " OR " << *e->get_expr2() << ")";
}

static void
print_neg(std::ostream& os, Neg_expr const* e)
{
  os << "(" <<  "-" << *e->get_expr1() << ")";
}

static void
print_rec(std::ostream& os, Rec_expr const* e)
{
  os << "(" << "/" << *e->get_expr1() << ")";
}

static void
print_not(std::ostream& os, Not_expr const* e)
{
  os << "(" << "NOT " << *e->get_expr1() << ")";
}

static void
print_id(std::ostream& os, Id_expr const* e)
{
  os << "("  << *e->get_id() << ")";
}

static void
print_con(std::ostream& os, Con_expr const* e)
{
  os << "(" << *e->get_expr1() << " ? " << *e->get_expr2() << " : " << *e->get_expr3() << ")";
}

static void
print_assign(std::ostream& os, Assign_expr const* e)
{
  os << "(" << *e->get_expr1() << " <- " << *e->get_expr2() << ")";
}

static void
print_fun_call(std::ostream& os, Fun_call const* e)
{
  if(e->get_params().size() == 0 )
  {
    os << *e->get_expr1() << "()";
  }
  else
  {
    os << *e->get_expr1() << "(";

    auto params = e->get_params();

    for(int i = 0; i < params.size(); i++)
    {
      os << *params[i];

      if (i == params.size()- 1)
        os << ")";
      else 
        os << ",";
    }

  }
}

static void
print_val_conv(std::ostream& os, Val_conv const* e)
{
  os << "val"  << *e->get_expr1();
}



void
print(std::ostream& os, Expr const* e)
{
  switch (e->get_kind()) {
  case Expr::bool_lit:
    return print_bool_lit(os, static_cast<Bool_lit const*>(e));
  
  case Expr::int_lit:
    return print_int_lit(os, static_cast<Int_lit const*>(e));

  case Expr::fl_lit:
    return print_fl_lit(os, static_cast<Fl_lit const*>(e));

  case Expr::add_expr:
    return print_add(os, static_cast<Add_expr const*>(e));

  case Expr::sub_expr:
    return print_sub(os, static_cast<Sub_expr const*>(e));

  case Expr::mul_expr:
    return print_mul(os, static_cast<Mul_expr const*>(e));

  case Expr::div_expr:
    return print_div(os, static_cast<Div_expr const*>(e));

  case Expr::rem_expr:
    return print_rem(os, static_cast<Rem_expr const*>(e));

  case Expr::gt_expr:
    return print_gt(os, static_cast<Gt_expr const*>(e));

  case Expr::lt_expr:
    return print_lt(os, static_cast<Lt_expr const*>(e));

  case Expr::gte_expr:
    return print_gte(os, static_cast<Gte_expr const*>(e));

  case Expr::lte_expr:
    return print_lte(os, static_cast<Lte_expr const*>(e));

  case Expr::eq_expr:
    return print_eq(os, static_cast<Eq_expr const*>(e));

  case Expr::ne_expr:
    return print_ne(os, static_cast<Ne_expr const*>(e));

  case Expr::and_expr:
    return print_and(os, static_cast<And_expr const*>(e));

  case Expr::or_expr:
    return print_or(os, static_cast<Or_expr const*>(e));

  case Expr::neg_expr:
    return print_neg(os, static_cast<Neg_expr const*>(e));

  case Expr::rec_expr:
    return print_rec(os, static_cast<Rec_expr const*>(e));

  case Expr::not_expr:
    return print_not(os, static_cast<Not_expr const*>(e));

  case Expr::id_expr:
    return print_id(os, static_cast<Id_expr const*>(e));

  case Expr::con_expr:
    return print_con(os, static_cast<Con_expr const*>(e));

  case Expr::assign_expr:
    return print_assign(os, static_cast<Assign_expr const*>(e));

  case Expr::fun_call:
    return print_fun_call(os, static_cast<Fun_call const*>(e));

  case Expr::val_conv:
    return print_val_conv(os, static_cast<Val_conv const*>(e));


  }
}



//operators and functions




std::ostream&
operator<<(std::ostream& os, Expr const& e)
{
  print(os, &e);
  return os;
}

std::ostream&
sexpr_r(std::ostream& os, Expr const& e)
{
  sexpr(os, &e);
  return os;
}

std::ostream&
debug_e(std::ostream& os, Expr const& e)
{
  debug(os, &e);
  return os;
}

//sexpression prints

static void
print_bool_sexpr(std::ostream& os, Bool_lit const* e)
{
  os << "(" << *e->get_type() << " " << e->get_val() << ")";
}

static void
print_int_sexpr(std::ostream& os, Int_lit const* e)
{
  os << "(" << *e->get_type() << " " << e->get_val() << ")";
}

static void
print_fl_sexpr(std::ostream& os, Fl_lit const* e)
{
  os << "(" << *e->get_type() << " " << e->get_val() << ")";
}

static void
print_add_sexpr(std::ostream& os, Add_expr const* e)
{
  os << "(" << "+ ";
  sexpr_r(os, *e->get_expr1()) << " ";
  sexpr_r(os, *e->get_expr2()) << ")";
}

static void
print_sub_sexpr(std::ostream& os, Sub_expr const* e)
{
  os << "(" << "- "; 
  sexpr_r(os, *e->get_expr1()) << " " ;
   sexpr_r(os, *e->get_expr2())  << ")";
}

static void
print_mul_sexpr(std::ostream& os, Mul_expr const* e)
{
  os << "(" << "* ";
   sexpr_r(os, *e->get_expr1()) << " " ;
   sexpr_r(os, *e->get_expr2())  << ")";
}

static void
print_div_sexpr(std::ostream& os, Div_expr const* e)
{
  os << "(" << "div "; 
  sexpr_r(os, *e->get_expr1()) << " " ;
  sexpr_r(os, *e->get_expr2())  << ")";
}

static void
print_rem_sexpr(std::ostream& os, Rem_expr const* e)
{
  os << "(" << "rem ";
   sexpr_r(os, *e->get_expr1()) << " ";
    sexpr_r(os, *e->get_expr2())  << ")";
}

static void
print_gt_sexpr(std::ostream& os, Gt_expr const* e)
{
  os << "(" << "> ";
  sexpr_r(os, *e->get_expr1()) << " ";
  sexpr_r(os, *e->get_expr2())  << ")";
}

static void
print_lt_sexpr(std::ostream& os, Lt_expr const* e)
{
  os << "(" << "< ";
  sexpr_r(os, *e->get_expr1()) << " ";
  sexpr_r(os, *e->get_expr2())  << ")";
}

static void
print_gte_sexpr(std::ostream& os, Gte_expr const* e)
{
  os << "(" << ">= "; 
  sexpr_r(os, *e->get_expr1()) << " ";
  sexpr_r(os, *e->get_expr2())  << ")";
}

static void
print_lte_sexpr(std::ostream& os, Lte_expr const* e)
{
  os << "(" << "<= ";
 sexpr_r(os, *e->get_expr1()) << " " ;
 sexpr_r(os, *e->get_expr2()) << ")";
}

static void
print_eq_sexpr(std::ostream& os, Eq_expr const* e)
{
  os << "(" << "= ";
  sexpr_r(os, *e->get_expr1()) << " " ;
  sexpr_r(os, *e->get_expr2())  << ")";
}

static void
print_ne_sexpr(std::ostream& os, Ne_expr const* e)
{
  os << "(" << "!= ";
  sexpr_r(os, *e->get_expr1()) << " " ;
  sexpr_r(os, *e->get_expr2()) << ")";
}

static void
print_and_sexpr(std::ostream& os, And_expr const* e)
{
  os << "(" << "AND ";
  sexpr_r(os, *e->get_expr1()) << " ";
  sexpr_r(os, *e->get_expr2())  << ")";
}

static void
print_or_sexpr(std::ostream& os, Or_expr const* e)
{
  os << "(" << "OR ";
  sexpr_r(os, *e->get_expr1()) << " " ;
  sexpr_r(os, *e->get_expr2()) << ")";
}

static void
print_neg_sexpr(std::ostream& os, Neg_expr const* e)
{
  os << "(" <<  "-";
  sexpr_r(os, *e->get_expr1()) << ")";
}

static void
print_rec_sexpr(std::ostream& os, Rec_expr const* e)
{
  os << "(" << "/";
  sexpr_r(os, *e->get_expr1()) << ")";
}

static void
print_not_sexpr(std::ostream& os, Not_expr const* e)
{
  os << "(" << "NOT ";
  sexpr_r(os, *e->get_expr1()) << ")";
}

static void
print_id_sexpr(std::ostream& os, Id_expr const* e)
{
  os << "("  << *e->get_id() << ")";
}

static void
print_con_sexpr(std::ostream& os, Con_expr const* e)
{
  os << "(Con " ;
  sexpr_r(os, *e->get_expr1()) << " ";
  sexpr_r(os, *e->get_expr2()) << " ";
  sexpr_r(os, *e->get_expr3()) << ")";
}

static void
print_assign_sexpr(std::ostream& os, Assign_expr const* e)
{
  os << "(Assignment " ;
  sexpr_r(os, *e->get_expr1()) << " ";
  sexpr_r(os, *e->get_expr2()) << ")";
}

static void
print_fun_call_sexpr(std::ostream& os, Fun_call const* e)
{
  if(e->get_params().size() == 0 )
  {
    os << "(Function Call ";
    sexpr_r(os, *e->get_expr1()) << "()";
  }
  else
  {
    sexpr_r(os, *e->get_expr1()) << "(";

    auto params = e->get_params();

    for(int i = 0; i < params.size(); i++)
    {
      sexpr_r(os, *params[i]);

      if (i == params.size()- 1)
        os << ")";
      else 
        os << ",";
    }

  }
}

static void
print_val_conv_sexpr(std::ostream& os, Val_conv const* e)
{
  os << "(Value Conversion of ";
  sexpr_r(os, *e->get_expr1()) << ")";
}

void
sexpr(std::ostream& os, Expr const* e)
{
  switch (e->get_kind()) {
  case Expr::bool_lit:
    return print_bool_sexpr(os, static_cast<Bool_lit const*>(e));
  
  case Expr::int_lit:
    return print_int_sexpr(os, static_cast<Int_lit const*>(e));

  case Expr::fl_lit:
    return print_fl_sexpr(os, static_cast<Fl_lit const*>(e));

  case Expr::add_expr:
    return print_add_sexpr(os, static_cast<Add_expr const*>(e));

  case Expr::sub_expr:
    return print_sub_sexpr(os, static_cast<Sub_expr const*>(e));

  case Expr::mul_expr:
    return print_mul_sexpr(os, static_cast<Mul_expr const*>(e));

  case Expr::div_expr:
    return print_div_sexpr(os, static_cast<Div_expr const*>(e));

  case Expr::rem_expr:
    return print_rem_sexpr(os, static_cast<Rem_expr const*>(e));

  case Expr::gt_expr:
    return print_gt_sexpr(os, static_cast<Gt_expr const*>(e));

  case Expr::lt_expr:
    return print_lt_sexpr(os, static_cast<Lt_expr const*>(e));

  case Expr::gte_expr:
    return print_gte_sexpr(os, static_cast<Gte_expr const*>(e));

  case Expr::lte_expr:
    return print_lte_sexpr(os, static_cast<Lte_expr const*>(e));

  case Expr::eq_expr:
    return print_eq_sexpr(os, static_cast<Eq_expr const*>(e));

  case Expr::ne_expr:
    return print_ne_sexpr(os, static_cast<Ne_expr const*>(e));

  case Expr::and_expr:
    return print_and_sexpr(os, static_cast<And_expr const*>(e));

  case Expr::or_expr:
    return print_or_sexpr(os, static_cast<Or_expr const*>(e));

  case Expr::neg_expr:
    return print_neg_sexpr(os, static_cast<Neg_expr const*>(e));

  case Expr::rec_expr:
    return print_rec_sexpr(os, static_cast<Rec_expr const*>(e));

  case Expr::not_expr:
    return print_not_sexpr(os, static_cast<Not_expr const*>(e));

  case Expr::id_expr:
    return print_id_sexpr(os, static_cast<Id_expr const*>(e));

  case Expr::con_expr:
    return print_con_sexpr(os, static_cast<Con_expr const*>(e));

  case Expr::assign_expr:
    return print_assign_sexpr(os, static_cast<Assign_expr const*>(e));

  case Expr::fun_call:
    return print_fun_call_sexpr(os, static_cast<Fun_call const*>(e));

  case Expr::val_conv:
    return print_val_conv_sexpr(os, static_cast<Val_conv const*>(e));

  }
}

//debug prints

static void
print_bool_debug(std::ostream& os, Bool_lit const* e)
{
  os << "(" << *e->get_type() << " " << e << ")";
}

static void
print_int_debug(std::ostream& os, Int_lit const* e)
{
  os << "(" << *e->get_type() << " " << e << ")";
}

static void
print_add_debug(std::ostream& os, Add_expr const* e)
{
  os << "(Add: " << e << " (";
  debug_e(os, *e->get_expr1()) << " + ";
  debug_e(os, *e->get_expr2()) << "))";
}

static void
print_sub_debug(std::ostream& os, Sub_expr const* e)
{
  os << "(Sub: " << e << " ("; 
  debug_e(os, *e->get_expr1()) << " - " ;
  debug_e(os, *e->get_expr2())  << " ))";
}

static void
print_mul_debug(std::ostream& os, Mul_expr const* e)
{
  os << "(Mul: " << e << " (";
   debug_e(os, *e->get_expr1()) << " * " ;
   debug_e(os, *e->get_expr2())  << "))";
}

static void
print_div_debug(std::ostream& os, Div_expr const* e)
{
  os << "(" << "Div: " << e << " ("; 
  debug_e(os, *e->get_expr1()) << " div " ;
  debug_e(os, *e->get_expr2())  << "))";
}

static void
print_rem_debug(std::ostream& os, Rem_expr const* e)
{
  os << "(" << "Rem: " << e << " (";
  debug_e(os, *e->get_expr1()) << " rem ";
  debug_e(os, *e->get_expr2())  << "))";
}

static void
print_gt_debug(std::ostream& os, Gt_expr const* e)
{
  os << "(GT: " << e << " (";
  debug_e(os, *e->get_expr1()) << " > ";
  debug_e(os, *e->get_expr2())  << "))";
}

static void
print_lt_debug(std::ostream& os, Lt_expr const* e)
{
  os << "(LT: " << e << " (";
  debug_e(os, *e->get_expr1()) << " < ";
  debug_e(os, *e->get_expr2())  << "))";
}

static void
print_gte_debug(std::ostream& os, Gte_expr const* e)
{
  os << "(GTE: " << e << " ("; 
  debug_e(os, *e->get_expr1()) << " >= ";
  debug_e(os, *e->get_expr2())  << "))";
}

static void
print_lte_debug(std::ostream& os, Lte_expr const* e)
{
  os << "(LTE: " << e << " ("; 
  debug_e(os, *e->get_expr1()) << " <= ";
  debug_e(os, *e->get_expr2())  << "))";
}

static void
print_eq_debug(std::ostream& os, Eq_expr const* e)
{
  os << "(Eq: " << e << " (";
  debug_e(os, *e->get_expr1()) << " = " ;
  debug_e(os, *e->get_expr2())  << "))";
}

static void
print_ne_debug(std::ostream& os, Ne_expr const* e)
{
  os << "(Not equal: " << e << " (";
  debug_e(os, *e->get_expr1()) << " != " ;
  debug_e(os, *e->get_expr2()) << "))";
}

static void
print_and_debug(std::ostream& os, And_expr const* e)
{
  os << "(AND: " << e << " (";
  debug_e(os, *e->get_expr1()) << " AND ";
  debug_e(os, *e->get_expr2())  << "))";
}

static void
print_or_debug(std::ostream& os, Or_expr const* e)
{
  os << "(OR: " << e << " (";
  debug_e(os, *e->get_expr1()) << " OR " ;
  debug_e(os, *e->get_expr2()) << "))";
}

static void
print_neg_debug(std::ostream& os, Neg_expr const* e)
{
  os << "(Negation: " << e << " (";
  debug_e(os, *e->get_expr1()) << "))";
}

static void
print_rec_debug(std::ostream& os, Rec_expr const* e)
{
  os << "(Recip: " << e << " (";
  debug_e(os, *e->get_expr1()) << "))";
}

static void
print_not_debug(std::ostream& os, Not_expr const* e)
{
  os << "(NOT: " << e << " (";
  debug_e(os, *e->get_expr1()) << "))";
}

static void
print_id_debug(std::ostream& os, Id_expr const* e)
{
  os << "(ID: ("  << *e->get_id() << e << "))";
}

static void
print_con_debug(std::ostream& os, Con_expr const* e)
{
  os << "(Conditional: " << e << "(" ;
  debug_e(os, *e->get_expr1()) << " ";
  debug_e(os, *e->get_expr2()) << " ";
  debug_e(os, *e->get_expr3()) << "))";
}

static void
print_assign_debug(std::ostream& os, Assign_expr const* e)
{
  os << "(Conditional: " << e << "(" ;
  debug_e(os, *e->get_expr1()) << " ";
  debug_e(os, *e->get_expr2()) << "))";
}

static void
print_fun_call_debug(std::ostream& os, Fun_call const* e)
{
  if(e->get_params().size() == 0 )
  {
    os << "(Function Call ";
    debug_e(os, *e->get_expr1()) << "()";
  }
  else
  {
    debug_e(os, *e->get_expr1()) << "(";

    auto params = e->get_params();

    for(int i = 0; i < params.size(); i++)
    {
      debug_e(os, *params[i]);

      if (i == params.size()- 1)
        os << ")";
      else 
        os << ",";
    }

  }
}

static void
print_val_conv_debug(std::ostream& os, Val_conv const* e)
{
  os << "(Value Conversion of ";
  debug_e(os, *e->get_expr1()) << ")";
}

void
debug(std::ostream& os, Expr const* e)
{
  switch (e->get_kind()) {
  case Expr::bool_lit:
    return print_bool_debug(os, static_cast<Bool_lit const*>(e));
  
  case Expr::int_lit:
    return print_int_debug(os, static_cast<Int_lit const*>(e));

  case Expr::add_expr:
    return print_add_debug(os, static_cast<Add_expr const*>(e));

  case Expr::sub_expr:
    return print_sub_debug(os, static_cast<Sub_expr const*>(e));

  case Expr::mul_expr:
    return print_mul_debug(os, static_cast<Mul_expr const*>(e));

  case Expr::div_expr:
    return print_div_debug(os, static_cast<Div_expr const*>(e));

  case Expr::rem_expr:
    return print_rem_debug(os, static_cast<Rem_expr const*>(e));

  case Expr::gt_expr:
    return print_gt_debug(os, static_cast<Gt_expr const*>(e));

  case Expr::lt_expr:
    return print_lt_debug(os, static_cast<Lt_expr const*>(e));

  case Expr::gte_expr:
    return print_gte_debug(os, static_cast<Gte_expr const*>(e));

  case Expr::lte_expr:
    return print_lte_debug(os, static_cast<Lte_expr const*>(e));

  case Expr::eq_expr:
    return print_eq_debug(os, static_cast<Eq_expr const*>(e));

  case Expr::ne_expr:
    return print_ne_debug(os, static_cast<Ne_expr const*>(e));

  case Expr::and_expr:
    return print_and_debug(os, static_cast<And_expr const*>(e));

  case Expr::or_expr:
    return print_or_debug(os, static_cast<Or_expr const*>(e));

  case Expr::neg_expr:
    return print_neg_debug(os, static_cast<Neg_expr const*>(e));

  case Expr::rec_expr:
    return print_rec_debug(os, static_cast<Rec_expr const*>(e));

  case Expr::not_expr:
    return print_not_debug(os, static_cast<Not_expr const*>(e));

  case Expr::id_expr:
    return print_id_debug(os, static_cast<Id_expr const*>(e));

  case Expr::con_expr:
    return print_con_debug(os, static_cast<Con_expr const*>(e));

  case Expr::assign_expr:
    return print_assign_debug(os, static_cast<Assign_expr const*>(e));

  case Expr::fun_call:
    return print_fun_call_debug(os, static_cast<Fun_call const*>(e));

  case Expr::val_conv:
    return print_val_conv_debug(os, static_cast<Val_conv const*>(e));


  }
}

