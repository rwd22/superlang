#include "expr.hpp"
#include "name.hpp"
#include "type.hpp"
#include "decl.hpp"
#include "stmt.hpp"

#include <iostream>
#include <iterator>


//basic prints

static void
print_str(std::ostream& os, char const* str)
{
  os << str;
}

static void
print_var(std::ostream& os, Var_decl const* d)
{
  os << "( " << *d->get_name()<< " : " << *d->get_type() << " = "<< *d->get_e() << " )";
}

static void
print_ref(std::ostream& os, Ref_decl const* d)
{
  os << "( " << *d->get_name()<< " : " << *d->get_type() << " = "<< *d->get_e() << " )";
}

static void
print_func(std::ostream& os, Func_decl const* d)
{
  if(d->get_decls().size() == 0 )
  {
    os << *d->get_name() << "( )" << "-> " << *d->get_type() << " " << *d->get_stmt();
  }
  else
  {
    os << *d->get_name() <<"(";

    auto decls = d->get_decls();

    for(int i = 0; i < decls.size(); i++)
    {
      os << *decls[i];

      if (i == decls.size()- 1)
        os << ") ->"<< *d->get_type() << " " << *d->get_stmt();
      else 
        os << ",";
    }

  }
}

void
print(std::ostream& os, Decl const* d)
{
  switch (d->get_kind()) {
  case Decl::var_decl:
    return print_var(os, static_cast<Var_decl const*>(d));

  case Decl::ref_decl:
    return print_ref(os, static_cast<Ref_decl const*>(d));

  case Decl::func_decl:
    return print_func(os, static_cast<Func_decl const*>(d));

  }
}

//operators and functions

std::ostream&
operator<<(std::ostream& os, Decl const& d)
{
  print(os, &d);
  return os;
}

std::ostream&
sexpr_d(std::ostream& os, Decl const& d)
{
  sexpr(os, &d);
  return os;
}

std::ostream&
debug_d(std::ostream& os, Decl const& d)
{
  debug(os, &d);
  return os;
}

//sexpression prints

static void
print_var_sexpr(std::ostream& os, Var_decl const* d)
{
  os << "(( " << *d->get_name()<< " : " << *d->get_type() << " = ";
  sexpr_r(os, *d->get_e()) << " ))";
}

static void
print_ref_sexpr(std::ostream& os, Ref_decl const* d)
{
  os << "(( " << *d->get_name()<< " : " << *d->get_type() << " = ";
  sexpr_r(os, *d->get_e()) << " ))";
}

static void
print_func_sexpr(std::ostream& os, Func_decl const* d)
{
  if(d->get_decls().size() == 0 )
  {
    os << *d->get_name() << "(( )" << "-> " << *d->get_type() << " " << *d->get_stmt() << ")";
  }
  else
  {
    os << *d->get_name() <<"((";

    auto decls = d->get_decls();

    for(int i = 0; i < decls.size(); i++)
    {
      os << *decls[i];

      if (i == decls.size()- 1)
        os << ") ->"<< *d->get_type() << " " << *d->get_stmt() << ")";
      else 
        os << ",";
    }

  }
}

void
sexpr(std::ostream& os, Decl const* d)
{
  switch (d->get_kind()) {
  case Decl::var_decl:
    return print_var_sexpr(os, static_cast<Var_decl const*>(d));

  case Decl::ref_decl:
    return print_ref_sexpr(os, static_cast<Ref_decl const*>(d));

  case Decl::func_decl:
    return print_func_sexpr(os, static_cast<Func_decl const*>(d));

  }
}

//debug prints

static void
print_var_debug(std::ostream& os, Var_decl const* d)
{
  os << "(Var: " << d << "(" << *d->get_name()<< " : " << *d->get_type() << d << " = ";
  debug_e(os, *d->get_e()) << " ))";
}

static void
print_ref_debug(std::ostream& os, Ref_decl const* d)
{
  os << "(Ref: " << d << "(" << *d->get_name()<< " : " << *d->get_type() << d << " = ";
  debug_e(os, *d->get_e()) << " ))";
}

static void
print_func_debug(std::ostream& os, Func_decl const* d)
{
  if(d->get_decls().size() == 0 )
  {
    os << "(Func: " << d << "(" << *d->get_name() << "(( )" << "-> " << *d->get_type() << " " << *d->get_stmt() <<  ")";
  }
  else
  {
    os << "(Func: " << d  << "(" << *d->get_name() <<"((";

    auto decls = d->get_decls();

    for(int i = 0; i < decls.size(); i++)
    {
      os << *decls[i] << decls[i];

      if (i == decls.size()- 1)
      {
        os << ") ->"<< *d->get_type() << " ";
        debug_s(os, *d->get_stmt()) << ")";
      }
      else 
        os << ",";
    }

  }
}

void
debug(std::ostream& os, Decl const* d)
{
  switch (d->get_kind()) {
  case Decl::var_decl:
    return print_var_debug(os, static_cast<Var_decl const*>(d));

  case Decl::ref_decl:
    return print_ref_debug(os, static_cast<Ref_decl const*>(d));

  case Decl::func_decl:
    return print_func_debug(os, static_cast<Func_decl const*>(d));

  }
}


bool
Decl::is_reference() const
{
  return is_variable() && get_type()->is_reference();
}