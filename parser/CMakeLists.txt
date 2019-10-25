add_library(parser_library
    Lexer.cpp
    Parser.cpp
)

target_include_directories(parser_library PUBLIC ${CMAKE_SOURCE_DIR})