find_package(LibXml2 REQUIRED)

add_library(XMLLoader src/XMLLoader.cpp)
find_package(LibXml2 REQUIRED)
target_link_libraries(XMLLoader CLILoader LibXml2::LibXml2)
target_include_directories(XMLLoader PUBLIC include)