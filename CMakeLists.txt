cmake_minimum_required(VERSION 3.10)

project(conan-juce-test)

get_property(GENERATOR_IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if (GENERATOR_IS_MULTI_CONFIG)
    set(CMAKE_BUILD_TYPE)
elseif (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(SCRIPTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/scripts")

list(APPEND CMAKE_MODULE_PATH "${SCRIPTS_DIR}/cmake")

include(conan)

conan_check(VERSION 1.14)
conan_add_remote(NAME bincrafters URL https://api.bintray.com/conan/bincrafters/public-conan)
conan_add_remote(NAME khdkhd URL https://api.bintray.com/conan/khdkhd/public-conan)

conan_setup(
        CONANFILE "${CMAKE_SOURCE_DIR}/conanfile.txt"
        CMAKE_TARGETS
        KEEP_RPATHS
)

set(
        SOURCES
        src/main.cpp
        src/hello.cpp
        src/hello.h
)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES})

set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST
        "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        ${HOST_SPECIFIC_DEPENDENCIES}
        CONAN_PKG::JUCE
)


target_compile_options(
        ${PROJECT_NAME} PRIVATE
        -mmacosx-version-min=10.11
        -O0
        -stdlib=libc++
)

if (CMAKE_BUILD_TYPE STREQUAL Debug)

    execute_process(COMMAND uname -m OUTPUT_VARIABLE JUCE_ARCH_LABEL OUTPUT_STRIP_TRAILING_WHITESPACE)

    target_include_directories(${PROJECT_NAME} PRIVATE
            "../../JuceLibraryCode"
            "$ENV{HOME}/JUCE/modules"
    )

    target_compile_definitions(${PROJECT_NAME} PRIVATE
            "_DEBUG=1"
            "DEBUG=1"
    )
endif ()

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)