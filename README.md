# udp-multicast-example

This project demonstrates how to implement simple UDP multicast transmition application. 

Once you will build the project, you will have two executables:
- sender
- receiver

Sender sends messages to the multicast group.
Receiver receives messages from the multicast group.

You can run as more senders and receivers as you want.

![Alt text](/screenshots/udp-milticast.png?raw=true "Optional Title")

# What is multicast transmition?

Multicasting is the networking technique of delivering the same packet simultaneously to a group of clients. IP multicast provides dynamic many-to-many connectivity between a set of senders (at least 1) and a group of receivers. The format of IP multicast packets is identical to that of unicast packets and is distinguished only by the use of a special class of destination address (class D IPv4 address) which denotes a specific multicast group. Since TCP supports only the unicast mode, multicast applications must use the UDP transport protocol.

Multicast clients receive a stream of packets only if they have previously joined the specific multicast group address. Membership of a group is dynamic and controlled by the receivers. The routers in a multicast network learn which sub-networks have active clients for each multicast group and attempt to minimise the transmission of packets across parts of the network for which there are no active clients.

Detailed information about multicast transmition you can find <a href=https://en.wikipedia.org/wiki/Multicast>here</a>

Also <a href="https://en.wikipedia.org/wiki/Multicast_address">here</a> you can find the list of multicast addresses and what they used for.

# How to build the project?
## Environment

- Windows 10
- cmake
- Microsoft Visual Studio 2019 community edition

## Build steps

    mkdir build
    cd build
    cmake ..
    cmake --build .
