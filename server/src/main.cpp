#include "protocol.hpp"

#include <asio.hpp>
#include <iostream>
#include <filesystem>

// Simple blocking MiniDrive server skeleton

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cout << "Usage: ./server --port <PORT> --root <ROOT_DIR>\n";
        return 1;
    }

    int port = 0;
    std::string root;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--port") port = std::stoi(argv[++i]);
        else if (arg == "--root") root = argv[++i];
    }

    if (!std::filesystem::exists(root)) {
        std::cerr << "[error] root directory does not exist\n";
        return 1;
    }

    try {
        asio::io_context io;

        asio::ip::tcp::acceptor acceptor(
            io,
            asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)
        );

        std::cout << "[server] Running on port " << port << "\n";
        std::cout << "[server] Root directory: " << root << "\n";

        while (true) {
            asio::ip::tcp::socket socket(io);
            std::cout << "[server] Waiting for client...\n";

            acceptor.accept(socket);
            std::cout << "[server] Client connected: "
                      << socket.remote_endpoint() << "\n";

            // Receive message
            asio::streambuf buffer;
            asio::read_until(socket, buffer, '\n');

            std::string msg((std::istreambuf_iterator<char>(&buffer)), {});
            std::cout << "[server] Received: " << msg << "\n";

            // Respond
            std::string response = "OK\n";
            asio::write(socket, asio::buffer(response));

            std::cout << "[server] Sent response\n";
        }

    } catch (std::exception& e) {
        std::cerr << "[server] Exception: " << e.what() << "\n";
    }

    return 0;
}
