
add_project_library(BiTypeChecker)
add_project_library(Types)

add_library(typecheck)
target_include_directories(typecheck PRIVATE ${INCLUDE_PROJECT_DIR} ${LLVM_INCLUDE_DIRS})
target_link_libraries(typecheck BiTypeChecker Types)
