#include <iostream>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

std::string getBroadcastAddress()
{
    struct ifaddrs *ifaddr, *ifa;
    char host[NI_MAXHOST];
    std::string broadcastAddress;

    if (getifaddrs(&ifaddr) == -1)
    {
        perror("getifaddrs");
        return "";
    }

    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == nullptr)
            continue;

        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
            struct sockaddr_in *broadaddr = (struct sockaddr_in *)ifa->ifa_broadaddr;

            // Skip loopback interfaces
            if (addr->sin_addr.s_addr == htonl(INADDR_LOOPBACK))
                continue;

            if (broadaddr != nullptr)
            {
                inet_ntop(AF_INET, &broadaddr->sin_addr, host, NI_MAXHOST);
                broadcastAddress = host;
                break;
            }
        }
    }

    freeifaddrs(ifaddr);
    return broadcastAddress;
}

int main()
{
    std::string broadcastAddress = getBroadcastAddress();
    if (!broadcastAddress.empty())
    {
        std::cout << "Broadcast Address: " << broadcastAddress << std::endl;
    }
    else
    {
        std::cerr << "Failed to get broadcast address" << std::endl;
    }
    return 0;
}