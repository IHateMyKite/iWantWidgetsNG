# It's recommended to set a minimum CMake version.
# If you use CMake features from higher versions, update this to match.
cmake_minimum_required(VERSION 3.21)

# Set your project name. This will be the name of your SKSE .dll file.
project(IWantWidgetsNative VERSION 1.2.4 LANGUAGES CXX)

# Otherwise, you can set OUTPUT_FOLDER to any place you'd like :)
# set(OUTPUT_FOLDER "C:/path/to/any/folder")

# Get the .cpp files from your src/ directory
# to be passed into add_commonlibsse_plugin
#
# This helper automatically finds all of your .cpp files for you
#
# Please note: the official recommendation is to list our every .cpp
# file individually after SOURCES
set(source_files ${source_files}
    src/IWWPapyrus.cpp
    src/IWWFunctions.cpp
    src/IWWConfig.cpp
)

# Setup your SKSE plugin as an SKSE plugin!
find_package(CommonLibSSE CONFIG REQUIRED)
add_commonlibsse_plugin(${PROJECT_NAME} SOURCES ${source_files} plugin.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23) # <--- use C++23 standard
target_precompile_headers(${PROJECT_NAME} PRIVATE PCH.h) # <--- PCH.h is required!
target_include_directories(${PROJECT_NAME} PRIVATE include)
