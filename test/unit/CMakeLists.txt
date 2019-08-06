set(TARGET_NAME unit_test)
add_custom_target(${TARGET_NAME}
        COMMAND echo \"There is no unit_test\"
        )

set(Cobertura_NAME cobertura_coverage)
set(Coverage_NAME coverage)
add_custom_target(${Cobertura_NAME}
        COMMAND touch  ${CMAKE_BINARY_DIR}/cobertura_coverage.xml
        )

add_custom_target(${Coverage_NAME}
        COMMAND mkdir -p ${CMAKE_BINARY_DIR}/coverage/
        COMMAND touch  ${CMAKE_BINARY_DIR}/coverage/index.html
        )