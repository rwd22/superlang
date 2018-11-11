
set(CMAKE_CXX_FLAGS -std="c++17")

add_executable(HelloWorld main.cpp  symbol.hpp symbol.cpp location.hpp token.hpp token.cpp lexer.hpp lexer.cpp)
