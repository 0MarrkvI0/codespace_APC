include(FetchContent)




# ASIO (header-only)
FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-36-0
)

FetchContent_MakeAvailable(asio)

# Create interface target for ASIO
add_library(asio INTERFACE)
target_include_directories(asio INTERFACE 
    ${asio_SOURCE_DIR}/asio/include
)
target_compile_definitions(asio INTERFACE ASIO_STANDALONE)
add_library(asio::asio ALIAS asio)




# nlohmann::json (header-only)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)
set(JSON_SystemInclude ON CACHE INTERNAL "")
FetchContent_MakeAvailable(nlohmann_json)
