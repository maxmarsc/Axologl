cmake_minimum_required(VERSION 3.28)

project(Axologl 
    VERSION 1.0.0 
    DESCRIPTION "A simple logging library for Nintendo Switch homebrew"
    LANGUAGES CXX
)

if(NOT SWITCH)
    message(FATAL_ERROR "This project is intended to be built for the Nintendo Switch. Please use the appropriate toolchain file.")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
find_package(Libnx REQUIRED)

# Since it is header-only, we use an INTERFACE library.
add_library(axologl INTERFACE)
add_library(axologl::axologl ALIAS axologl)
target_compile_features(axologl INTERFACE cxx_std_17) # required for filesystem

target_include_directories(axologl INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(axologl INTERFACE switch::libnx)

# Use PROJECT_IS_TOP_LEVEL to default tests to OFF if used via FetchContent/add_subdirectory.
option(AXOLOGL_BUILD_TESTS "Build Axologl tests" ${PROJECT_IS_TOP_LEVEL})

if(AXOLOGL_BUILD_TESTS)
    add_executable(axologl_test test/main.cpp)
    target_link_libraries(axologl_test PRIVATE axologl::axologl)
    target_link_options(axologl_test PRIVATE 
        -specs=${LIBNX}/switch.specs
    )
endif()

# Installation Support
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Install the library target
install(TARGETS axologl 
    EXPORT AxologlTargets
)

# Install header files
install(DIRECTORY include/ 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Generate and install the Export file (makes find_package work)
install(EXPORT AxologlTargets
    FILE AxologlTargets.cmake
    NAMESPACE axologl::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Axologl
)

# Generate and install Version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/AxologlConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Create a basic Config file
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/AxologlConfig.cmake"
    "include(\${CMAKE_CURRENT_LIST_DIR}/AxologlTargets.cmake)\n"
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/AxologlConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/AxologlConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Axologl
)