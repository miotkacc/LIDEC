find_package(LibXml2 REQUIRED)

add_library(XMLLoader src/XMLLoader.cpp)
target_include_directories(XMLLoader PUBLIC include)