add_library(CLILoader src/CLILoader.cpp)
add_library(ActionParams src/ActionParams.cpp)
target_include_directories(CLILoader PUBLIC include)
target_include_directories(ActionParams PUBLIC include)
