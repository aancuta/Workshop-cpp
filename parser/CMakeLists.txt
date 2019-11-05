add_library(parser_library
    Lexer.hpp
    Lexer.cpp
    Parser.hpp
    Parser.cpp
)

target_include_directories(parser_library PUBLIC ${CMAKE_SOURCE_DIR})