#include "token.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>

int
main()
{
 

  Symbol_table syms;

  std::string test = "if(a==true);";
  




  Lexer lexer(syms, test);

  for (Token tok; tok =lexer.get_next_token();) {
   std::cout << tok << '\n';
 }
}
















