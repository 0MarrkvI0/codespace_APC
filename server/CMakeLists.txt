add_executable(server
    src/main.cpp
)

target_link_libraries(server
    PRIVATE
        asio::asio
        nlohmann_json::nlohmann_json
        minidrive_common
)
