cmake_minimum_required(VERSION 3.22)
project(LIDEC)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(XMLLoader)
add_subdirectory(CLILoader)
add_subdirectory(Interpreter)
add_subdirectory(Dispatcher)
add_subdirectory(Executors)

add_executable(main main.cpp)

target_link_libraries(main CLILoader XMLLoader Interpreter Dispatcher Executors ActionParams)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(testCLILoader testCLILoader.cpp)
target_link_libraries(testCLILoader CLILoader GTest::gtest_main GTest::gmock_main ActionParams)

add_executable(testXMLLoader testXMLLoader.cpp)
target_link_libraries(testXMLLoader XMLLoader CLILoader ActionParams GTest::gtest_main GTest::gmock_main)

add_executable(testInterpreter testInterpreter.cpp)
target_link_libraries(testInterpreter Interpreter GTest::gtest_main GTest::gmock_main)

add_executable(testDispatcher testDispatcher.cpp)
target_link_libraries(testDispatcher GTest::gtest_main GTest::gmock_main Dispatcher)

add_executable(testExecutors testExecutors.cpp)
target_link_libraries(testExecutors GTest::gtest_main GTest::gmock_main Executors)

add_executable(test testCLILoader.cpp testXMLLoader.cpp testInterpreter.cpp testDispatcher.cpp testExecutors.cpp)
target_link_libraries(test GTest::gtest_main GTest::gmock_main CLILoader ActionParams XMLLoader Interpreter Dispatcher Executors)

add_executable(demoXMLLoader demoXMLLoader.cpp)
target_link_libraries(demoXMLLoader CLILoader ActionParams XMLLoader Interpreter Dispatcher Executors)

add_executable(demoMultithread demoMultithread.cpp)
target_link_libraries(demoMultithread CLILoader ActionParams XMLLoader Interpreter Dispatcher Executors)