
set(CMAKE_CXX_FLAGS -std="c++17")

add_executable(HelloWorld main.cpp type.cpp expr.cpp name.cpp stmt.cpp decl.cpp builder.cpp builder.hpp symbol.hpp symbol.cpp location.hpp token.hpp token.cpp lexer.hpp lexer.cpp)
