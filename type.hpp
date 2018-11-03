#pragma once

#include <iosfwd>
#include <vector>

class Type;
class Bool_type;
class Int_type;
class Ref_type;
class Name;


class Type
{
public:
  enum Kind
  {
    bool_type,
    int_type,
    ref_type,
    fun_type,
    float_type,
  };

protected:
  Type(Kind k) : m_kind(k) { }
  

public:
  Kind get_kind() const { return m_kind; }
  bool is_reference() const { return m_kind == ref_type; }
  bool is_bool() const { return m_kind == bool_type; }


private:
  Kind m_kind;
};

//classes for types



class Bool_type : public Type
{
public:
  Bool_type()
    : Type(bool_type)
  { }
};


class Int_type : public Type
{
public:
  Int_type()
    : Type(int_type)
  { }
};

class Float_type : public Type
{
public:
  Float_type()
    : Type(float_type)
  { }
};

class Ref_type : public Type
{
public:
  Ref_type(Type* t)
    : Type(ref_type), m_ref(t)
  { }

  Type* get_referent_type() const { return m_ref; }

private:
  Type* m_ref;
};


class Fun_type : public Type
{
  public:
    Fun_type(std::vector<Type*> params, Type* ret)
      : Type(fun_type), m_params(params), m_ret_type(ret)
      {}

    std::vector<Type*> get_param_types() const { return m_params; }
    Type* get_ret_type() const { return m_ret_type; }

  private:
    std::vector<Type*> m_params;
    Type* m_ret_type;

};

//operators and functions

std::ostream& operator<<(std::ostream& os, Type const& t);

std::ostream& sexpr_t(std::ostream& os, Type const& t);

std::ostream& debug_t(std::ostream& os, Type const& t);

void print(std::ostream& os, Type const* t);

void sexpr(std::ostream& os, Type const* t);

void debug(std::ostream& os, Type const* t);