include_directories(%(includepath)s)
link_directories(%(libpath)s)
add_definitions("-DIMP_EXECUTABLE")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${%(NAME)s_CXX_FLAGS}")

File(GLOB runtimepytests "${CMAKE_BINARY_DIR}/test/%(name)s/test_*.py" "${CMAKE_BINARY_DIR}/test/%(name)s/medium_test_*.py" "${CMAKE_BINARY_DIR}/test/%(name)s/expensive_test_*.py")

include(Files.cmake)

set(IMP_TEST_ARGUMENTS)
set(IMP_TEST_SETUP ${IMP_TEST_SETUP};${%(NAME)s_TEST_SETUP})
set(IMP_LINK_LIBRARIES IMP.%(name)s-lib
    %(modules)s
    %(dependencies)s)

imp_add_tests("IMP.%(name)s" ${PROJECT_BINARY_DIR}/test/%(name)s IMP_%(name)s_TESTS test ${runtimepytests} ${pyfiles} ${cppfiles})
