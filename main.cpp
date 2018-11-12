#include "token.hpp"
#include "lexer.hpp"

#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>

int
main()
{
 

  Symbol_table syms;

  std::string test = "0x1af";
  




  Lexer lexer(syms, test);

  for (Token tok; tok =lexer.get_next_token();) {
   std::cout << tok << '\n';
 }
}
















