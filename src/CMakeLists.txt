set(TARGET_NAME pcc)

include_directories(
    SYSTEM ${CONAN_INCLUDE_DIRS}
)

add_subdirectory(matrixreaderwriter)

add_executable(${TARGET_NAME}
    main.cc
)

target_link_libraries(${TARGET_NAME}
    ${CONAN_LIBS}
    matrixreaderwriter
    project_warnings
)
