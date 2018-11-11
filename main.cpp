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

  std::string test = "if(red == true){blue = false;}";
  




  Lexer lexer(syms, test);

  for (std::string::iterator it = test.begin(); it!=test.end(); ++it) {
  	Token tok = lexer.get_next_token();
   std::cout << tok << '\n';
 }
}
















