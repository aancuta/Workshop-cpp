
set(unit_tests
    unit-print.in
    unit-print2.in
    unit-number.in
    unit-undefined.in
    unit-id.in
    unit-assign.in
    unit-empty-block.in
    unit-empty-block-eval.in
    unit-simple-block.in
    unit-simple-block-eval.in
    unit-unary-plus-expression.in
    unit-unary-minus-expression.in
    unit-binary-plus.in
    unit-binary-priorities.in
)
set(integration_tests
    integration-binary.in
    integration-assign.in
    integration-undefined.in
    integration-unary.in
    integration-unary2.in
    integration-double-op.in
    integration-if.in
    integration-else.in
    integration-assign-if.in
    integration-assign-blocks-parantheses.in
    integration-if-block.in
)
set(functional_tests
    functional-abs.in
    functional-loop.in
    functional-gcd.in
    functional-fib.in
)
set(test_files
    ${unit_tests}
    ${integration_tests}
    ${functional_tests}
)

foreach(test_file ${test_files})
    string(REGEX REPLACE ".in$" "" test_name ${test_file})
    add_test(${test_name} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/main ${CMAKE_CURRENT_SOURCE_DIR}/${test_file})
    file(READ ${test_file}.ref reference)
    set_tests_properties(${test_name} PROPERTIES PASS_REGULAR_EXPRESSION ${reference})
endforeach()
