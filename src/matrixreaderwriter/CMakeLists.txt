set(TARGET_NAME matrixreaderwriter)

add_library(${TARGET_NAME}
    STATIC
    MatrixReaderWriter.cc
)

target_link_libraries(${TARGET_NAME}
    project_warnings
)
