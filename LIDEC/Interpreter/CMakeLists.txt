add_library(Interpreter src/Interpreter.cpp)

find_package(LibXml2 REQUIRED)
target_include_directories(Interpreter PUBLIC include)
target_link_libraries(Interpreter LibXml2::LibXml2 ActionParams)
