#ifndef UDP_PUB
#define UDP_PUB

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

class UDPPub
{
public:
    UDPPub() = delete; // prevent usage of default constructor

    UDPPub(size_t max_buffer_size, int port, in_addr_t address, bool broadcast = false)
    {
        /**
         * Defined the socket file descriptor to reference the socket in sends.
         */
        socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (socket_fd < 0)
        {
            throw std::runtime_error(formatErrorMessage("Error opening Socket"));
        }
        this->max_buffer_size = max_buffer_size;



        if (broadcast)
        {
            throw std::logic_error(formatErrorMessage("broadcast is not successfully tested yet"));
            int broadcastEnable = 1;
            if (setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable)) < 0)
            {
                throw std::runtime_error(formatErrorMessage("Error setting socket option for broadcast"));
            }
        }

        /**
         * Define the address that we want to send too. 
         * This is saved as a private variable.
         * 
         * If we are broadcasting, the ip address should be set to the computer's broadcast address. 
         * 
         */
        memset(&dest_addr, 0, sizeof(dest_addr));
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(port);
        dest_addr.sin_addr.s_addr = address;
    }

    void write(std::string message)
    {
        // Send the message to the server
        ssize_t sent_bytes = sendto(socket_fd, message.c_str(), message.size(), 0,
                                    (sockaddr *)&dest_addr, sizeof(dest_addr));
        if (sent_bytes < 0)
        {
            throw std::runtime_error(formatErrorMessage("Error sending message"));
        }
    }


    ~UDPPub()
    {
        close(socket_fd);
    }

private:
    size_t max_buffer_size;
    sockaddr_in dest_addr;
    int socket_fd;

    std::string formatErrorMessage(const std::string &message) const
    {
        return "UDPPub: " + message;
    }
};

#endif // UDP_PUB