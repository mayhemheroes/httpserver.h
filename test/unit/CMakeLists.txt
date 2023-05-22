add_executable(
  fuzz-parser
  fuzz_parser.c
)


include(CheckFunctionExists)
check_function_exists(epoll_wait EPOLL)
check_function_exists(kqueue KQUEUE)

if(KQUEUE)
  target_compile_definitions(fuzz-parser PRIVATE "KQUEUE")
endif()

if(EPOLL)
  target_compile_definitions(fuzz-parser PRIVATE "EPOLL")
endif()

target_link_libraries(fuzz-parser PUBLIC httpsrv)

## Uncomment these lines after converting fuzzme.c into a libFuzzer target
if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(FATAL_ERROR "Clang is required for libFuzzer!")
endif()
target_compile_options(fuzz-parser PUBLIC -fsanitize=fuzzer)
target_link_options(fuzz-parser PUBLIC -fsanitize=fuzzer)
