#pragma once

#include <iostream>
#include <assert.h>  

class Type;
struct Expr;
struct Stmt;

struct Decl
{
public:
  enum Kind
  {
    var_decl,
    ref_decl,
    func_decl
  };

protected:
  Decl(Kind k) : m_kind(k) { }
  

public:
  Kind get_kind() const { return m_kind; }
  bool is_variable() const { return m_kind == var_decl; }
  bool is_reference() const {  return is_variable() && get_type()->is_reference();}
  virtual Type* get_type() const { return nullptr; }  
  bool is_object() const {return is_variable() && get_type()->is_object();}
  bool is_function() const { return m_kind == func_decl; }

private:
  Kind m_kind;
};







//declaration structures

struct Var_decl : public Decl
{
public:
  Var_decl(Name* n, Type* t, Expr* e)
    : Decl(var_decl), m_name(n), m_type(t), m_exp(e)
  { }

  Name* get_name() const { return m_name; }
  Type* get_type() const { return m_type; }
  Expr* get_e() const { return m_exp; }
  void set_initializer(Expr* e);
  Expr* get_initializer() const { return m_init; }

private:
  Type* m_type;
  Expr* m_exp;
  Name* m_name;
   Expr* m_init;
};

inline void
Var_decl::set_initializer(Expr* e)
{
  assert(!m_init);
  m_init = e;
}

struct Ref_decl : public Decl
{
public:
  Ref_decl(Name* n, Type* t, Expr* e)
    : Decl(ref_decl), m_name(n), m_type(t), m_exp(e)
  { }

  Name* get_name() const { return m_name; }
  Type* get_type() const { return m_type; }
  Expr* get_e() const { return m_exp; }

private:
  Type* m_type;
  Expr* m_exp;
  Name* m_name;
};

struct Func_decl : public Decl
{
public:
  Func_decl(Name* n, Type* t, std::vector<Decl*> decls, Stmt* s)
    : Decl(func_decl), m_name(n), m_type(t), m_decls(decls), m_stmt(s)
  { }

  Name* get_name() const { return m_name; }
  Type* get_type() const { return m_type; }
  std::vector<Decl*> get_decls() const { return m_decls; }
  Stmt* get_stmt() const { return m_stmt; }

private:
  Type* m_type;
  Name* m_name;
  std::vector<Decl*> m_decls;
  Stmt* m_stmt;
};

//operators and functions

std::ostream& operator<<(std::ostream& os, Decl const& d);

std::ostream& sexpr_d(std::ostream& os, Decl const& d);

std::ostream& debug_d(std::ostream& os, Decl const& d);

void print(std::ostream& os, Decl const* d);

void debug(std::ostream& os, Decl const* d);

void sexpr(std::ostream& os, Decl const* d);
