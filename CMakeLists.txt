cmake_minimum_required(VERSION 2.8.3)

project(IMP)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
   message(FATAL_ERROR "Building in the source directory not supported: ${CMAKE_SOURCE_DIR} is ${CMAKE_BINARY_DIR}. If this message seems wrong, make sure to delete the CMakeFiles directory and the CMakeCache.txt file if they exist in the source dir (${CMAKE_SOURCE_DIR}).")
endif()

# Check Python version early so we can use Python >= 2.6 features in other
# build scripts
execute_process(COMMAND python "tools/build/check_python_version.py"
                RESULT_VARIABLE setup
                OUTPUT_VARIABLE toutput
                ERROR_VARIABLE error
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                OUTPUT_STRIP_TRAILING_WHITESPACE)
if(NOT ${setup} EQUAL 0)
   message(FATAL_ERROR "Failed checking Python version: ${error}")
endif()

if(IS_DIRECTORY "${PROJECT_SOURCE_DIR}/.git")
  execute_process(COMMAND python "tools/dev_tools/git/setup_git.py"
                    RESULT_VARIABLE setup
                    OUTPUT_VARIABLE toutput
                    ERROR_VARIABLE error
                    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(NOT ${setup} EQUAL 0)
     message(FATAL_ERROR " Failed to run setup_git.py: ${setup}; ${error}")
  endif()
endif()

include(${CMAKE_SOURCE_DIR}/modules/rmf/dependency/RMF/cmake_modules/IMPExecuteProcess.cmake)
include(${CMAKE_SOURCE_DIR}/modules/rmf/dependency/RMF/cmake_modules/IMPAddTests.cmake)
include(${CMAKE_SOURCE_DIR}/modules/rmf/dependency/RMF/cmake_modules/CheckCompiles.cmake)

imp_execute_process("check_common_problems" ${CMAKE_SOURCE_DIR} COMMAND ${CMAKE_SOURCE_DIR}/tools/build/check_common_problems.py)

imp_execute_process("clean_build_dir" ${CMAKE_BINARY_DIR} COMMAND ${CMAKE_SOURCE_DIR}/tools/build/clean_build_dir.py)

imp_execute_process("setup_cmake" ${CMAKE_SOURCE_DIR} COMMAND ${CMAKE_SOURCE_DIR}/tools/build/setup_cmake.py)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/modules/rmf/dependency/RMF/cmake_modules)

enable_testing()

include(${CMAKE_SOURCE_DIR}/modules/rmf/dependency/RMF/cmake_modules/IMPFindC++11.cmake)
include(${CMAKE_SOURCE_DIR}/modules/rmf/dependency/RMF/cmake_modules/IMPFindCompilerFlags.cmake)

if(POLICY CMP0017)
cmake_policy(SET CMP0017 NEW)
endif(POLICY CMP0017)

# Don't set MACOSX_RPATH by default
if(POLICY CMP0042)
cmake_policy(SET CMP0042 OLD)
endif(POLICY CMP0042)

set(timeout_factor 1)
set(IMP_SWIG_PATH CACHE STRING "List of places for swig to search")
set(SWIG_EXECUTABLE swig CACHE STRING "Swig program")
set(IMP_PYTHON python CACHE INTERNAL "The Python executable that IMP itself will use at runtime (the build system scripts will always use 'python')")
set(IMP_DISABLED_MODULES CACHE STRING "A colon-separated list of disabled modules")
set(IMP_STATIC off CACHE BOOL "Link all binaries and libraries statically; currently only supported on Linux systems with gcc.")
if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
set(timeout_factor "${timeout_factor} * 2")
set(IMP_MAX_CHECKS "INTERNAL" CACHE STRING "One of NONE, USAGE, INTERNAL")
set(IMP_MAX_LOG "VERBOSE" CACHE STRING "One of SILENT, PROGRESS, TERSE, VERBOSE")
else()
set(IMP_MAX_CHECKS "USAGE" CACHE STRING "One of NONE, USAGE, INTERNAL")
set(IMP_MAX_LOG "VERBOSE" CACHE STRING "One of SILENT, PROGRESS, TERSE, VERBOSE")
endif()
set(IMP_PER_CPP_COMPILATION "" CACHE STRING "A colon-separated list of modules to build one .cpp at a time.")

if (${IMP_MAX_CHECKS} MATCHES "INTERNAL")
set(timeout_factor "${timeout_factor} * 2")
endif()

set(IMP_TIMEOUT_FACTOR ${timeout_factor} CACHE STRING "A factor to scale the test timeouts. Use this when on a slow machine, or using a slow copy of IMP (eg doing coverage). This can be a math expression on integers, but not a floating point constant.")

include(FindCurrentDoxygen)

# clear list
set(IMP_DOC_DEPENDS "" CACHE INTERNAL "")
if(${IMP_DOXYGEN_FOUND})
imp_execute_process("setup_doxygen" ${CMAKE_BINARY_DIR} COMMAND ${CMAKE_SOURCE_DIR}/tools/build/setup_doxygen.py "--source=${CMAKE_SOURCE_DIR}")
endif()

if(IMP_STATIC)
  SET(IMP_LIB_TYPE STATIC)
  SET(Boost_USE_STATIC_LIBS ON)
  set(CMAKE_EXE_LINKER_FLAGS "-static")
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  set(CMAKE_EXE_LINK_DYNAMIC_C_FLAGS)       # remove -Wl,-Bdynamic
  set(CMAKE_EXE_LINK_DYNAMIC_CXX_FLAGS)
  set(CMAKE_SHARED_LIBRARY_C_FLAGS)         # remove -fPIC
  set(CMAKE_SHARED_LIBRARY_CXX_FLAGS)
  set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)    # remove -rdynamic
  set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)
else()
  SET(IMP_LIB_TYPE SHARED)
endif()

string(REGEX MATCHALL "[a-zA-Z]+" percpplist "${IMP_PER_CPP_COMPILATION}")
foreach(m ${percpplist})
message(STATUS ${m} " is percpp")
set(IMP_${m}_IS_PER_CPP 1)
endforeach(m)

if(NOT DEFINED PYTHON_INCLUDE_DIRS AND NOT IMP_STATIC)
  execute_process(COMMAND ${IMP_PYTHON} -c "import sys; print(sys.executable)"
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                  OUTPUT_VARIABLE python_full_path
                  OUTPUT_STRIP_TRAILING_WHITESPACE)
  execute_process(COMMAND ${IMP_PYTHON} -c "import sys; print('%d.%d.%d' % sys.version_info[:3])"
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                OUTPUT_VARIABLE python_full_version
                OUTPUT_STRIP_TRAILING_WHITESPACE)
  string(REGEX REPLACE "^([0-9]+\\.[0-9]+).*" "\\1" python_version
         ${python_full_version})
  message(STATUS "Python binary is " ${python_full_path} " (version " ${python_full_version} ")")

  FIND_PACKAGE(PythonLibs ${python_full_version} EXACT REQUIRED)
endif()
if(WIN32)
  set(IMP_SWIG_LIBRARIES ${PYTHON_LIBRARIES})
endif(WIN32)

if(NOT DEFINED PATH_SEP)
  if(WIN32)
    Set(PATH_SEP ";")
  else()
    Set(PATH_SEP ":")
  endif()
endif()
if(NOT DEFINED SETUP_EXT)
  if(WIN32)
    Set(SETUP_EXT "bat")
  else()
    Set(SETUP_EXT "sh")
  endif()
endif()

if("${SETUP_EXT}" STREQUAL "sh")
  set(IMP_TEST_SETUP "${CMAKE_BINARY_DIR}/setup_environment.sh")
else()
  # On Windows the batch file is run once to set up the test environment, not
  # per test
  set(IMP_TEST_SETUP )
endif()

include(GNUInstallDirs)
# Add extra installation locations for SWIG .i files and Python code
if(NOT DEFINED CMAKE_INSTALL_SWIGDIR)
  set(CMAKE_INSTALL_SWIGDIR "share/IMP/swig" CACHE PATH "SWIG interface files")
endif()
if(NOT DEFINED CMAKE_INSTALL_PYTHONDIR)
  set(CMAKE_INSTALL_PYTHONDIR "${CMAKE_INSTALL_LIBDIR}/python${python_version}/site-packages" CACHE PATH "Python modules")
endif()

include(InstallDeref)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

include_directories("${CMAKE_BINARY_DIR}/include")

imp_execute_process("setup" ${CMAKE_BINARY_DIR} COMMAND ${CMAKE_SOURCE_DIR}/tools/build/setup.py
                    --source=${CMAKE_SOURCE_DIR}
                    --disabled=${IMP_DISABLED_MODULES}
                    --datapath=${IMP_DATAPATH})

imp_execute_process("setup_all" ${CMAKE_BINARY_DIR}
                    COMMAND ${CMAKE_SOURCE_DIR}/tools/build/setup_all.py
                    --source=${CMAKE_SOURCE_DIR})

include(${PROJECT_SOURCE_DIR}/tools/build/cmake_files/MakeContainers.cmake)

imp_execute_process("making containers" ${CMAKE_BINARY_DIR}
                    COMMAND ${CMAKE_SOURCE_DIR}/tools/build/make_containers.py)

imp_execute_process("setup_module_alias for kernel" ${CMAKE_BINARY_DIR}
                    COMMAND ${CMAKE_SOURCE_DIR}/tools/build/setup_module_alias.py
                    --source=${CMAKE_SOURCE_DIR} --module=kernel "--alias=")




# Don't link in libpython (that prevents the extension from being used in
# later compatible versions of Python), except on Windows where all DLL
# symbols must be defined
IF(WIN32)
  set(SWIG_PYTHON_LIBRARIES ${PYTHON_LIBRARIES} )
ELSE(WIN32)
  set(SWIG_PYTHON_LIBRARIES )
ENDIF(WIN32)

# Visual Studio always adds Release or Debug to binary directories
if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
  SET(IMP_BINARY_PATH_SUFFIX ${CMAKE_BUILD_TYPE})
else()
  SET(IMP_BINARY_PATH_SUFFIX )
endif()

set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost 1.38.0 COMPONENTS system filesystem thread program_options REQUIRED)
if("${Boost_SYSTEM_LIBRARY_RELEASE}" MATCHES ".*NOTFOUND.*")
  message(FATAL_ERROR "Boost is required to build IMP.")
endif()
find_package(Boost 1.38.0 QUIET COMPONENTS random regex graph)

if("${Boost_RANDOM_LIBRARY_RELEASE}" MATCHES ".*NOTFOUND.*")
set(Boost_RANDOM_LIBRARY_RELEASE "" CACHE INTERNAL "" FORCE)
set(Boost_RANDOM_LIBRARY_DEBUG "" CACHE INTERNAL "" FORCE)
file(WRITE "${CMAKE_BINARY_DIR}/data/build_info/Boost.Random" "ok=False")
elseif(NOT "${Boost_RANDOM_LIBRARY_RELEASE}" STREQUAL "")
file(WRITE "${CMAKE_BINARY_DIR}/data/build_info/Boost.Random" "ok=True")
else()
file(WRITE "${CMAKE_BINARY_DIR}/data/build_info/Boost.Random" "ok=False")
endif()

if("${Boost_REGEX_LIBRARY_RELEASE}" MATCHES ".*NOTFOUND.*")
set(Boost_REGEX_LIBRARY_RELEASE "" CACHE INTERNAL "" FORCE)
set(Boost_REGEX_LIBRARY_DEBUG "" CACHE INTERNAL "" FORCE)
file(WRITE "${CMAKE_BINARY_DIR}/data/build_info/Boost.Regex" "ok=False")
elseif(NOT "${Boost_REGEX_LIBRARY_RELEASE}" STREQUAL "")
file(WRITE "${CMAKE_BINARY_DIR}/data/build_info/Boost.Regex" "ok=True")
else()
file(WRITE "${CMAKE_BINARY_DIR}/data/build_info/Boost.Regex" "ok=False")
endif()

if("${Boost_GRAPH_LIBRARY_RELEASE}" MATCHES ".*NOTFOUND.*")
set(Boost_GRAPH_LIBRARY_RELEASE "" CACHE INTERNAL "" FORCE)
set(Boost_GRAPH_LIBRARY_DEBUG "" CACHE INTERNAL "" FORCE)
file(WRITE "${CMAKE_BINARY_DIR}/data/build_info/Boost.Graph" "ok=False")
elseif(NOT "${Boost_GRAPH_LIBRARY_RELEASE}" STREQUAL "")
file(WRITE "${CMAKE_BINARY_DIR}/data/build_info/Boost.Graph" "ok=True")
else()
file(WRITE "${CMAKE_BINARY_DIR}/data/build_info/Boost.Graph" "ok=False")
endif()

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

set(BOOST.FILESYSTEM_LIBRARIES ${Boost_FILESYSTEM_LIBRARY_RELEASE})
set(BOOST.SYSTEM_LIBRARIES ${Boost_SYSTEM_LIBRARY_RELEASE})
set(BOOST.THREAD_LIBRARIES ${Boost_THREAD_LIBRARY_RELEASE})
set(BOOST.PROGRAMOPTIONS_LIBRARIES ${Boost_PROGRAM_OPTIONS_LIBRARY_RELEASE})
set(BOOST.REGEX_LIBRARIES ${Boost_REGEX_LIBRARY_RELEASE})
set(BOOST.GRAPH_LIBRARIES ${Boost_GRAPH_LIBRARY_RELEASE})
set(BOOST.RANDOM_LIBRARIES ${Boost_RANDOM_LIBRARY_RELEASE})

file(WRITE "${CMAKE_BINARY_DIR}/data/build_info/Boost.FileSystem" "ok=True")
file(WRITE "${CMAKE_BINARY_DIR}/data/build_info/Boost.ProgramOptions" "ok=True")
file(WRITE "${CMAKE_BINARY_DIR}/data/build_info/Boost.System" "ok=True")

if(NOT IMP_STATIC)
  # Automatically enable OpenMP if available and at least version 3
  find_package(OpenMP3)
endif()

add_custom_target("IMP-version"
                  COMMAND ${CMAKE_SOURCE_DIR}/tools/build/make_version.py --source=${CMAKE_SOURCE_DIR}
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                  COMMENT "Computing version number")


# configure modules
file(STRINGS "${CMAKE_BINARY_DIR}/data/build_info/sorted_modules" modules)

foreach(mod ${modules})
  add_subdirectory("${CMAKE_SOURCE_DIR}/modules/${mod}/")
endforeach(mod)

# build modules
file(STRINGS "${CMAKE_BINARY_DIR}/data/build_info/sorted_modules" enabled_modules)

if(NOT DEFINED IMP_NO_SWIG_DEPENDENCIES)
# the make_containers.py call is needed to let swig find all headers it needs
imp_execute_process("setup_swig_dependencies" ${CMAKE_BINARY_DIR}
                    COMMAND ${CMAKE_SOURCE_DIR}/tools/build/setup_swig_deps.py
                    "--swig=${SWIG_EXECUTABLE}")
endif()

# Static builds don't include Python extensions
if(NOT IMP_STATIC)
  # Can't set up pyext until we have SWIG dependencies
  foreach(mod ${enabled_modules})
    add_subdirectory("${CMAKE_SOURCE_DIR}/modules/${mod}/pyext")
  endforeach(mod)
endif()

foreach(mod ${enabled_modules})
  add_custom_target(IMP.${mod} DEPENDS
  IMP.${mod}-lib
  ${IMP_${mod}_BINS}
  ${IMP_${mod}_UTILS}
  ${IMP_${mod}_TESTS}
  ${IMP_${mod}_BENCHMARKS}
  ${IMP_${mod}_PYTHON}
  ${IMP_${mod}_EXAMPLES}
  ${IMP_${mod}_DOC})
endforeach(mod)

list(INSERT IMP_PYTHONPATH 0 "${CMAKE_BINARY_DIR}/lib")
list(INSERT IMP_LDPATH 0 "${CMAKE_BINARY_DIR}/lib")
list(INSERT IMP_PATH 0 "${CMAKE_BINARY_DIR}/bin")
set(PATH_ARGS )
foreach(path ${IMP_PYTHONPATH})
  list(APPEND PATH_ARGS "--python_path=${path}")
endforeach(path)
foreach(path ${IMP_LDPATH})
  list(APPEND PATH_ARGS "--ld_path=${path}")
endforeach(path)
foreach(path ${IMP_PATH})
  list(APPEND PATH_ARGS "--path=${path}")
endforeach(path)
imp_execute_process("setup_imppy" ${CMAKE_BINARY_DIR}
                    COMMAND ${CMAKE_SOURCE_DIR}/tools/build/setup_imppy.py
                    "--python=${IMP_PYTHON}"
                    "--precommand="
                    "--propagate=yes"
                    "--suffix=${IMP_BINARY_PATH_SUFFIX}"
                    "--output=setup_environment.${SETUP_EXT}"
                    ${PATH_ARGS})

if(IMP_DOXYGEN_FOUND)

 file(GLOB docs ${CMAKE_SOURCE_DIR}/doc/*/*.dox
   ${CMAKE_SOURCE_DIR}/doc/*/*.md)

  add_custom_target(IMP-doc
    COMMAND ${CMAKE_SOURCE_DIR}/tools/build/setup_doxygen_config.py "--source=${CMAKE_SOURCE_DIR}"
    # Generate manual's tag file so we can link from the refguide to it
    COMMAND ${IMP_DOXYGEN_EXECUTABLE} doxygen/manual.xml
    COMMAND ${IMP_DOXYGEN_EXECUTABLE} doxygen/ref.xml
    COMMAND ${CMAKE_SOURCE_DIR}/tools/build/make_cross_refs.py
    COMMAND ${IMP_DOXYGEN_EXECUTABLE} doxygen/ref.html
    COMMAND ${CMAKE_SOURCE_DIR}/tools/build/doxygen_show_warnings.py --warn=${CMAKE_BINARY_DIR}/doxygen/ref-warnings.txt
    COMMAND ${CMAKE_SOURCE_DIR}/tools/build/doxygen_fix_links.py ${CMAKE_BINARY_DIR}/doc/ref
    # Rebuild manual so that it can link to the refguide tags
    COMMAND ${IMP_DOXYGEN_EXECUTABLE} doxygen/manual.html
    COMMAND ${CMAKE_SOURCE_DIR}/tools/build/doxygen_show_warnings.py --warn=${CMAKE_BINARY_DIR}/doxygen/manual-warnings.txt
    COMMAND patch -p1 < ${CMAKE_SOURCE_DIR}/doc/doxygen/search.patch
    COMMAND ${CMAKE_SOURCE_DIR}/tools/build/doxygen_add_nav.py
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS ${IMP_DOC_DEPENDS} ${docs} ${IMP_DOXYGEN_FETCH} IMP-version
    COMMENT "Building documentation")

  add_custom_target(IMP-doc-install
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_BINARY_DIR}/doc/manual" "${CMAKE_INSTALL_FULL_DOCDIR}/manual"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_BINARY_DIR}/doc/ref" "${CMAKE_INSTALL_FULL_DOCDIR}/ref"
    DEPENDS "IMP-doc"
    COMMENT "Installing documentation to ${CMAKE_INSTALL_FULL_DOCDIR}")
else()
  message(STATUS "Documentation disabled as doxygen not found")
endif(IMP_DOXYGEN_FOUND)

# Install headers
install(FILES ${CMAKE_BINARY_DIR}/include/IMP.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install_deref(${CMAKE_BINARY_DIR}/include/IMP * ${CMAKE_INSTALL_INCLUDEDIR}/IMP)

# Install Python modules
install_deref(${CMAKE_BINARY_DIR}/lib/IMP * ${CMAKE_INSTALL_PYTHONDIR}/IMP)

# Install data
install_deref(${CMAKE_BINARY_DIR}/data * ${CMAKE_INSTALL_DATADIR}/IMP)

# Install SWIG .i files
install_deref(${CMAKE_BINARY_DIR}/swig *.i ${CMAKE_INSTALL_SWIGDIR})

# Install examples
install_deref(${CMAKE_BINARY_DIR}/doc/examples *
              ${CMAKE_INSTALL_DOCDIR}/examples)

# Try to ensure that ctest doesn't truncate benchmark output
file(WRITE "${CMAKE_BINARY_DIR}/CTestCustom.cmake"
"SET(CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE 4096)
")
