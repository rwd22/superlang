#include "type.hpp"
#include "name.hpp"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

//basic prints

static void
print_str(std::ostream& os, char const* str)
{
  os << str;
}

static void
print_ref(std::ostream& os, Ref_type const* t)
{
  os << "ref " << *t->get_referent_type();
}

static void
print_fun(std::ostream& os, Fun_type const* t)
{
  if(t->get_param_types().size() == 0 )
  {
    os << "( )" << "-> " << *t->get_ret_type();
  }
  else
  {
    os <<"(";

    auto params = t->get_param_types();

    for(int i = 0; i < params.size(); i++)
    {
      os << *params[i];

      if (i == params.size()- 1)
        os << ") ->"<< *t->get_ret_type();
      else 
        os << ",";
    }

  }
}


void
print(std::ostream& os, Type const* t)
{
  switch (t->get_kind()) {
  case Type::bool_type:
    return print_str(os, "bool");
  
  case Type::int_type:
    return print_str(os, "int");

  case Type::float_type:
    return print_str(os, "float");
  
  case Type::ref_type:
    return print_ref(os, static_cast<Ref_type const*>(t));

  case Type::fun_type:
    return print_fun(os, static_cast<Fun_type const*>(t));
  }
}

//operators and functions

std::ostream&
operator<<(std::ostream& os, Type const& t)
{
  print(os, &t);
  return os;
}

std::ostream&
sexpr_t(std::ostream& os, Type const& t)
{
  sexpr(os, &t);
  return os;
}

std::ostream&
debug_t(std::ostream& os, Type const& t)
{
  debug(os, &t);
  return os;
}

//sexpression prints


static void
print_str_sexpr(std::ostream& os, char const* str)
{
  os << "( " << str << " )";
}

static void
print_ref_sexpr(std::ostream& os, Ref_type const* t)
{
  os << "( ref ";
  sexpr_t(os, *t->get_referent_type()) << " )";
}

static void
print_fun_sexpr(std::ostream& os, Fun_type const* t)
{
  if(t->get_param_types().size() == 0 )
  {
    os  << "-> " << "(( )"  << *t->get_ret_type() << " )";
  }
  else
  {
    os <<"(->(";

    auto params = t->get_param_types();

    for(int i = 0; i < params.size(); i++)
    {
      os << *params[i];

      if (i == params.size()- 1)
        os << ") "<< *t->get_ret_type() << " )";
      else 
        os << ",";
    }

  }
}


void
sexpr(std::ostream& os, Type const* t)
{
  switch (t->get_kind()) {
  case Type::bool_type:
    return print_str_sexpr(os, "bool");
  
  case Type::int_type:
    return print_str_sexpr(os, "int");

  case Type::float_type:
    return print_str_sexpr(os, "float");
  
  case Type::ref_type:
    return print_ref_sexpr(os, static_cast<Ref_type const*>(t));

  case Type::fun_type:
    return print_fun_sexpr(os, static_cast<Fun_type const*>(t));
  }
}

//debug prints

static void
print_ref_debug(std::ostream& os, Ref_type const* t)
{
  os << "(ref " << t->get_referent_type() << ")";
}

static void
print_bool_debug(std::ostream& os, Bool_type const* t)
{
  os << "(bool " << t << ")";
}

static void
print_int_debug(std::ostream& os, Int_type const* t)
{
  os << "(int " << t << ")";
}

static void
print_float_debug(std::ostream& os, Float_type const* t)
{
  os << "(float " << t << ")";
}

static void
print_fun_debug(std::ostream& os, Fun_type const* t)
{
  if(t->get_param_types().size() == 0 )
  {
    os << "(( )" << "-> " << *t->get_ret_type() << " "<< t->get_ret_type()<< ")";
  }
  else
  {
    os <<"((";

    auto params = t->get_param_types();

    for(int i = 0; i < params.size(); i++)
    {
      os << *params[i] << " " << params[i];

      if (i == params.size()- 1)
        os << ") ->"<< *t->get_ret_type()<< " "<< t->get_ret_type() << ")";
      else 
        os << ",";
    }

  }
}

void
debug(std::ostream& os, Type const* t)
{
  switch (t->get_kind()) {
  case Type::bool_type:
    return print_bool_debug(os, static_cast<Bool_type const*>(t));
  
  case Type::int_type:
    return print_int_debug(os, static_cast<Int_type const*>(t));

  case Type::float_type:
    return print_float_debug(os, static_cast<Float_type const*>(t));
  
  case Type::ref_type:
    return print_ref_debug(os, static_cast<Ref_type const*>(t));

  case Type::fun_type:
    return print_fun_debug(os, static_cast<Fun_type const*>(t));
  }
}


bool
Type::is_reference_to(Type const* that) const
{
  if (is_reference()) {
    Ref_type const* ref = static_cast<Ref_type const*>(this);
    if (ref->get_referent_type() == that)
      return true;
  }
  return false;
}


/*char const*
Type::get_kind_name() const
{
  switch (m_kind) {
  case bool_type: return "bool_type";
  case int_type: return "int_type";
  case float_type: return "float_type";
  case ref_type: return "ref_type";
  case fun_type: return "fn_type";
  }
}

bool
Type::is_reference_to(Type const* that) const
{
  if (is_reference()) {
    Ref_type const* ref = static_cast<Ref_type const*>(this);
    if (is_same(ref->get_referent_type(), that))
      return true;
  }
  return false;
}

bool
Type::is_same_as(Type const* that) const
{
  return is_same(this, that);
}



bool
is_same(Type const* a, Type const* b) 
{

  if (a->get_kind() != b->get_kind())
    return false;

  switch (a->get_kind()) {
  case Type::bool_type:
  case Type::int_type:
  case Type::float_type:
    return true;
  case Type::ref_type:
    return is_same_ref(static_cast<Ref_type const*>(a), 
                       static_cast<Ref_type const*>(b));
  case Type::fn_type:
    return is_same_fn(static_cast<Fn_type const*>(a), 
                      static_cast<Fn_type const*>(b));
  }
}

static bool
is_same_ref(Ref_type const* a, Ref_type const* b)
{
  return is_same(a->get_referent_type(), b->get_referent_type());
}

static bool
is_same_fn(Fun_type const* a, Fun_type const* b)
{
  return std::equal((a->get_param_types()).begin(), (a->get_param_types()).end(), (b->get_param_types()).begin(), (b->get_param_types()).end(), is_same);
}*/
