#include "protocol.hpp"

#include <asio.hpp>
#include <iostream>
#include <string>

using asio::ip::tcp;

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: client <host> <port>\n";
            return 1;
        }

        asio::io_context io_context;

        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(argv[1], argv[2]);

        tcp::socket socket(io_context);
        // https://think-async.com/Asio/asio-1.36.0/doc/asio/reference/connect/overload8.html
        asio::connect(socket, endpoints);

        std::cout << "Connected to server. Type messages (Ctrl+C to quit):\n";

        while (true) {
            std::string message;
            std::cout << "> ";
            std::getline(std::cin, message);

            if (message.empty()) continue;

            // append new line as delimiter
            message += '\n';

            // Send message
            asio::write(socket, asio::buffer(message));

            // Receive echo
            char reply[1024];
            size_t reply_length = socket.read_some(asio::buffer(reply));
            std::cout << "Echo: " << std::string(reply, reply_length) << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}