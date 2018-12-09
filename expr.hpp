#pragma once

#include <iosfwd>
#include <vector>


class Type;
class Name;

struct Expr
{
	enum Kind
	{
   		bool_lit,
   	 	int_lit,
   	 	fl_lit,
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
    	assign_expr,
    	fun_call,
    	val_conv
	};

protected:
  Expr(Kind k) : m_kind(k) { }
  

public:
  Kind get_kind() const { return m_kind; }
  Type* get_type() const { return m_type; }

private:
  Kind m_kind;
  Type* m_type;

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

struct Fl_lit : Expr
{

public:
  Fl_lit( float val, Type* t)
    : Expr(fl_lit), m_val(val), m_type(t)
  { }

	float get_val() const { return m_val; }
	Type* get_type() const { return m_type; }

private:

	int m_val;
	Type * m_type;
};

struct Add_expr : Expr
{

public:
	Add_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(add_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }

private:

	Expr* m_e1;
	Expr* m_e2;
	Type* m_type;
	
};

struct Sub_expr : Expr
{

public:
	Sub_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(sub_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
		Type* m_type;
	
};

struct Mul_expr : Expr
{

public:
	Mul_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(mul_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
		Type* m_type;
	
};

struct And_expr : Expr
{

public:
	And_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(and_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
		Type* m_type;
	
};

struct Or_expr : Expr
{

public:
	Or_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(or_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
	Type* m_type;
		
};

struct Eq_expr : Expr
{

public:
	Eq_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(eq_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
	Type* m_type;
		
};

struct Ne_expr : Expr
{

public:
	Ne_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(ne_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
		Type* m_type;
	
};


struct Lt_expr : Expr
{

public:
	Lt_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(lt_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
	Type* m_type;
	
};

struct Gt_expr : Expr
{

public:
	Gt_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(gt_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
		Type* m_type;
	
};

struct Lte_expr : Expr
{

public:
	Lte_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(lte_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
	Type* m_type;
		
};

struct Gte_expr : Expr
{

public:
	Gte_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(gte_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
	Type* m_type;
		
};

struct Div_expr : Expr
{

public:
	Div_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(div_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
		Type* m_type;
	
};

struct Rem_expr : Expr
{

public:
	Rem_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(rem_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
		Type* m_type;
	
};

struct Not_expr : Expr
{

public:
	Not_expr(Expr* e1, Type* t)
		: Expr(not_expr), m_e1(e1), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
		Type* m_type;
	
};

struct Neg_expr : Expr
{

public:
	Neg_expr(Expr* e1, Type* t)
		: Expr(neg_expr), m_e1(e1), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Type* m_type;
		
};

struct Rec_expr : Expr
{

public:
	Rec_expr(Expr* e1, Type* t)
		: Expr(rec_expr), m_e1(e1), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Type* m_type;
		
};

struct Id_expr : Expr
{

public:
	Id_expr(Decl* d, Type* t)
		: Expr(id_expr), m_d(d), m_type(t)
	{ }

	Decl* get_d() const {return m_d;}
	Type* get_type() const { return m_type; }


private:

	Decl* m_d;
	Type* m_type;
		
};

struct Con_expr : Expr
{

public:
	Con_expr(Expr* e1, Expr* e2, Expr* e3, Type* t)
		: Expr(con_expr), m_e1(e1), m_e2(e2), m_e3(e3), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Expr* get_expr3() const {return m_e3;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
	Expr* m_e3;
	Type* m_type;
		
};

struct Assign_expr : Expr
{

public:
	Assign_expr(Expr* e1, Expr* e2, Type* t)
		: Expr(assign_expr), m_e1(e1), m_e2(e2), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Expr* get_expr2() const {return m_e2;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Expr* m_e2;
	Type* m_type;
		
};

struct Fun_call : Expr
{

public:
	Fun_call(Expr* e1, std::vector<Expr*> params, Type* t)
		: Expr(fun_call), m_e1(e1), m_params(params), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	std::vector<Expr*> get_params() const { return m_params; }
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	std::vector<Expr*> m_params;
	Type* m_type;
		
};

struct Val_conv : Expr
{

public:
	Val_conv(Expr* e1, Type* t)
		: Expr(val_conv), m_e1(e1), m_type(t)
	{ }

	Expr* get_expr1() const {return m_e1;}
	Type* get_type() const { return m_type; }


private:

	Expr* m_e1;
	Type* m_type;
		
};


//operators and functions

std::ostream& operator<<(std::ostream& os, Expr const& e);

std::ostream& sexpr_r(std::ostream& os, Expr const& e);

std::ostream& debug_e(std::ostream& os, Expr const& e);

void print(std::ostream& os, Expr const* e);

void debug(std::ostream& os,Expr const* e);

void sexpr(std::ostream& os, Expr const *e);
