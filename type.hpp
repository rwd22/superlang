#pragma once

#include <iosfwd>
#include <vector>

class Type;
class Bool_type;
class Int_type;
class Ref_type;
class Name;

/// Represents all strings that spell a type.
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
  /// Constructs the type to have kind `k`.

public:
  Kind get_kind() const { return m_kind; }
  /// Returns the kind of the type.

private:
  Kind m_kind;
};


/// Represents the string `bool`.
class Bool_type : public Type
{
public:
  Bool_type()
    : Type(bool_type)
  { }
};


/// Represents the string `int`.
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



/// Represents strings of the form `ref t` where `t` is a type.
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


// Operators

std::ostream& operator<<(std::ostream& os, Type const& t);


// Operations

void print(std::ostream& os, Type const* t);
/// Prints `t` to the output stream.

bool equal(Type const* a, Type const* b);
/// Returns true when `a` and `b` denote the same type.



