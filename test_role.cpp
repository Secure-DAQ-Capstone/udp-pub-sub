#include "udp-pub.cpp"
#include "udp-sub.cpp"
#include <iostream>
#include <thread>

void runSubscriber(size_t buffer_size, int port, in_addr_t address)
{
    try
    {
        UDPSub subscriber(buffer_size, port, address);
        while (true)
        {
            std::string message = subscriber.read();
            std::cout << "Received: " << message << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Subscriber Exception: " << e.what() << std::endl;
    }
}

void runPublisher(size_t buffer_size, int port, in_addr_t address, bool enable_broadcast)
{
    try
    {
        UDPPub publisher(buffer_size, port, address, enable_broadcast);
        std::string message;
        while (true)
        {
            std::cout << "Enter message to send: ";
            std::getline(std::cin, message);
            std::cout << message << std::endl;
            publisher.write(message);
            std::cout << "Message sent: " << message << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Publisher Exception: " << e.what() << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <pub|sub>" << std::endl;
        return 1;
    }

    size_t buffer_size = 1024;
    int port = 8080;

    /** 
     * This is the port that te publisher would send messages too.
     * It doesn't bind to a socket, it just sends a message when needed.
     * 
     * Therefore, this would need to be replaced with the address of the computer you want to send too.
     */
    in_addr_t sendto_address = inet_addr("192.168.2.111");

    /**
     * The subscriber is binding a socket to it's local IP and Port.
     * Therefore you can expect this to be a loop back.
     */
    in_addr_t sub_local_address = inet_addr("127.0.0.1");

    std::string role = argv[1];
    if (role == "sub")
    {
        runSubscriber(buffer_size, port, sub_local_address);
    }
    else if (role == "pub")
    {
        runPublisher(buffer_size, port, sendto_address, false);
    }
    else
    {
        std::cerr << "Invalid role: " << role << std::endl;
        std::cerr << "Usage: " << argv[0] << " <pub|sub>" << std::endl;
        return 1;
    }

    return 0;
}