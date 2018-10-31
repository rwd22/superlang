#pragma once

#include <iosfwd>


class Type;
class Name;

struct Expr
{
	enum Kind
	{
   		bool_lit,
   	 	int_lit,
   	 	id_expr,
   	 	add_expr,
   	 	sub_expr,
   	 	mul_expr,
   	 	div_expr,
   	 	rem_expr,
   	 	neg_expr,
   	 	rec_expr,
   	 	eq_expr,
    	ne_expr,
    	lt_expr,
    	gt_expr,
    	lte_expr,
    	gte_expr,
    	con_expr,
    	and_expr,
    	or_expr,
    	not_expr,
	};

protected:
  Expr(Kind k) : m_kind(k) { }
  

public:
  Kind get_kind() const { return m_kind; }

private:
  Kind m_kind;

};

//structures for expressions

struct Bool_lit : Expr
{

public:
  Bool_lit( bool val, Type* t)
    : Expr(bool_lit), m_val(val), m_type(t)
  { }

	bool get_val() const { return m_val; }
	Type* get_type() const { return m_type; }

private:

	bool m_val;
	Type* m_type;
};

struct Int_lit : Expr
{

public:
  Int_lit( int val, Type* t)
    : Expr(int_lit), m_val(val), m_type(t)
  { }

	int get_val() const { return m_val; }
	Type* get_type() const { return m_type; }

private:

	int m_val;
	Type * m_type;
};

struct Add_expr : Expr
{

public:
	Add_expr(Expr* e1, Expr* e2)
		: Expr(add_expr), m_e1(e1), m_e2(e2)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}


private:

	Expr* m_e1;
	Expr* m_e2;
	
};

struct Sub_expr : Expr
{

public:
	Sub_expr(Expr* e1, Expr* e2)
		: Expr(sub_expr), m_e1(e1), m_e2(e2)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}


private:

	Expr* m_e1;
	Expr* m_e2;
	
};

struct Mul_expr : Expr
{

public:
	Mul_expr(Expr* e1, Expr* e2)
		: Expr(mul_expr), m_e1(e1), m_e2(e2)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}


private:

	Expr* m_e1;
	Expr* m_e2;
	
};

struct And_expr : Expr
{

public:
	And_expr(Expr* e1, Expr* e2)
		: Expr(and_expr), m_e1(e1), m_e2(e2)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}


private:

	Expr* m_e1;
	Expr* m_e2;
	
};

struct Or_expr : Expr
{

public:
	Or_expr(Expr* e1, Expr* e2)
		: Expr(or_expr), m_e1(e1), m_e2(e2)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}


private:

	Expr* m_e1;
	Expr* m_e2;
	
};

struct Eq_expr : Expr
{

public:
	Eq_expr(Expr* e1, Expr* e2)
		: Expr(eq_expr), m_e1(e1), m_e2(e2)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}


private:

	Expr* m_e1;
	Expr* m_e2;
	
};

struct Ne_expr : Expr
{

public:
	Ne_expr(Expr* e1, Expr* e2)
		: Expr(ne_expr), m_e1(e1), m_e2(e2)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}


private:

	Expr* m_e1;
	Expr* m_e2;
	
};


struct Lt_expr : Expr
{

public:
	Lt_expr(Expr* e1, Expr* e2)
		: Expr(lt_expr), m_e1(e1), m_e2(e2)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}


private:

	Expr* m_e1;
	Expr* m_e2;
	
};

struct Gt_expr : Expr
{

public:
	Gt_expr(Expr* e1, Expr* e2)
		: Expr(gt_expr), m_e1(e1), m_e2(e2)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}


private:

	Expr* m_e1;
	Expr* m_e2;
	
};

struct Lte_expr : Expr
{

public:
	Lte_expr(Expr* e1, Expr* e2)
		: Expr(lte_expr), m_e1(e1), m_e2(e2)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}


private:

	Expr* m_e1;
	Expr* m_e2;
	
};

struct Gte_expr : Expr
{

public:
	Gte_expr(Expr* e1, Expr* e2)
		: Expr(gte_expr), m_e1(e1), m_e2(e2)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}


private:

	Expr* m_e1;
	Expr* m_e2;
	
};

struct Div_expr : Expr
{

public:
	Div_expr(Expr* e1, Expr* e2)
		: Expr(div_expr), m_e1(e1), m_e2(e2)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}


private:

	Expr* m_e1;
	Expr* m_e2;
	
};

struct Rem_expr : Expr
{

public:
	Rem_expr(Expr* e1, Expr* e2)
		: Expr(rem_expr), m_e1(e1), m_e2(e2)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}


private:

	Expr* m_e1;
	Expr* m_e2;
	
};

struct Not_expr : Expr
{

public:
	Not_expr(Expr* e1)
		: Expr(not_expr), m_e1(e1)
	{ }

	Expr* get_expr1() const {return m_e1;}


private:

	Expr* m_e1;
	
};

struct Neg_expr : Expr
{

public:
	Neg_expr(Expr* e1)
		: Expr(neg_expr), m_e1(e1)
	{ }

	Expr* get_expr1() const {return m_e1;}


private:

	Expr* m_e1;
	
};

struct Rec_expr : Expr
{

public:
	Rec_expr(Expr* e1)
		: Expr(rec_expr), m_e1(e1)
	{ }

	Expr* get_expr1() const {return m_e1;}


private:

	Expr* m_e1;
	
};

struct Id_expr : Expr
{

public:
	Id_expr(Name* id)
		: Expr(id_expr), m_id(id)
	{ }

	Name* get_id() const {return m_id;}


private:

	Name* m_id;
	
};

struct Con_expr : Expr
{

public:
	Con_expr(Expr* e1, Expr* e2, Expr* e3)
		: Expr(con_expr), m_e1(e1), m_e2(e2), m_e3(e3)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Expr* get_expr3() const {return m_e3;}


private:

	Expr* m_e1;
	Expr* m_e2;
	Expr* m_e3;
	
};

//operators and functions

std::ostream& operator<<(std::ostream& os, Expr const& e);

std::ostream& sexpr_r(std::ostream& os, Expr const& e);

std::ostream& debug_e(std::ostream& os, Expr const& e);

void print(std::ostream& os, Expr const* e);

void debug(std::ostream& os,Expr const* e);

void sexpr(std::ostream& os, Expr const *e);
