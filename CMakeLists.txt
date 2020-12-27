cmake_minimum_required(VERSION 3.13)
project(icebreaker)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(cpr
        GIT_REPOSITORY https://github.com/whoshuu/cpr.git
        GIT_TAG 1.5.2) # the commit hash for 1.5.0
FetchContent_MakeAvailable(cpr)
FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.7.3)
FetchContent_GetProperties(json)
if (NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()

set(
        SOURCE_FILES
        include/entities/File.hpp
        include/entities/Machine.hpp
        include/entities/Response.hpp
        include/entities/Status.hpp
        include/entities/User.hpp
        include/sections/Section.hpp
        include/entities/Package.hpp
        include/entities/Repository.hpp
        include/entities/APIEntity.hpp
        include/utils/JsonUtils.hpp
        include/entities/Code.h
        include/utils/MultipartHelpers.hpp
        src/sections/Auth.cpp
        src/sections/Files.cpp
        src/sections/Packages.cpp
        src/sections/Repositories.cpp
        nclude/utils/ResponseUtils.hpp
        include/entities/FileDataContent.h
)
include_directories(include)

add_library(icebreaker STATIC ${SOURCE_FILES})

target_link_libraries(icebreaker PRIVATE cpr::cpr)
target_link_libraries(icebreaker PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(icebreaker PUBLIC include)
target_include_directories(icebreaker PUBLIC ${cpr_SOURCE_DIR}/include)
target_include_directories(icebreaker PUBLIC ${json_SOURCE_DIR}/include)
