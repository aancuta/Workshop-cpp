add_executable(main
    main.cpp
)

target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(main ast_library parser_library)
