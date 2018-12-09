#pragma once

#include <iostream>

struct Decl;
struct Expr;
class Type;

struct Stmt
{
public:
  enum Kind
  {
    break_stmt,
    skip_stmt,
    cont_stmt,
    block_stmt,
    while_stmt,
    ternary_stmt,
    return_stmt,
    expr_stmt,
    loc_def_stmt
  };

protected:
  Stmt(Kind k) : m_kind(k) { }
  

public:
  Kind get_kind() const { return m_kind; }


private:
  Kind m_kind;
};

//structures for differnt statements

struct Break_stmt : public Stmt
{
public:
  Break_stmt()
    : Stmt(break_stmt)
  { }
};

struct Skip_stmt : public Stmt
{
public:
  Skip_stmt()
    : Stmt(skip_stmt)
  { }
};

struct Cont_stmt : public Stmt
{
public:
  Cont_stmt()
    : Stmt(cont_stmt)
  { }
};

struct Block_stmt : public Stmt
{
public:
  Block_stmt(std::vector<Stmt*> params)
    : Stmt(block_stmt), m_params(params)
  { }

  std::vector<Stmt*> get_param_stmts() const { return m_params; }

private:
    std::vector<Stmt*> m_params;
};

struct While_stmt : public Stmt
{
public:
  While_stmt(Expr* e, Stmt* s)
    : Stmt(while_stmt), m_expr(e),m_stmt(s)
  { }

  Expr* get_expr() const { return m_expr; }
  Stmt* get_stmt() const { return m_stmt; }

private:
    Expr* m_expr;
    Stmt* m_stmt;
};

struct Ternary_stmt : Stmt
{

public:
    Ternary_stmt(Expr* e1, Stmt* s1, Stmt* s2)
        : Stmt(ternary_stmt), m_e1(e1), m_s1(s1), m_s2(s2)
    { }

    Expr* get_expr1() const {return m_e1;}
    Stmt* get_stmt1() const {return m_s1;}
    Stmt* get_stmt2() const {return m_s2;}


private:

    Expr* m_e1;
    Stmt* m_s1;
    Stmt* m_s2;
    
};

struct Return_stmt : public Stmt
{
public:
  Return_stmt(Expr* e)
    : Stmt(return_stmt), m_expr(e)
  { }

  Expr* get_expr() const { return m_expr; }

private:
    Expr* m_expr;
};

struct Expr_stmt : public Stmt
{
public:
  Expr_stmt(Expr* e)
    : Stmt(expr_stmt), m_expr(e)
  { }

  Expr* get_expr() const { return m_expr; }

private:
    Expr* m_expr;
};

struct Loc_def_stmt : public Stmt
{
public:
  Loc_def_stmt(Decl* d)
    : Stmt(loc_def_stmt), m_decl(d)
  { }

  Decl* get_decl() const { return m_decl; }

private:
    Decl* m_decl;
};

//operators and functions

std::ostream& operator<<(std::ostream& os, Stmt const& s);

std::ostream& sexpr_s(std::ostream& os, Stmt const& s);

std::ostream& debug_s(std::ostream& os, Stmt const& s);

void sexpr(std::ostream& os, Stmt const* s);

void print(std::ostream& os, Stmt const* s);

void debug(std::ostream& os, Stmt const* s);
