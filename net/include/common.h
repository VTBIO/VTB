#ifndef __NET_COMMON_H__
#define __NET_COMMON_H__

using node_id = h512;


enum PacketType {
    HelloPacket = 0;
    DisconnectPacket,
    PingPacket,
    PongPacket,
    GetPeersPacket,
    PeersPacket,
    UserPacket = 0x10,
};

enum DisconnectReason {
    DisconnectRequested = 0,
    TCPError,
    BadProtocol,
    UselessPeer,
    TooManyPeers,
    DuplicatePeer,
    IncompatibleProtocol,
    NullIdentity,
    ClientQuit,
    UnexpectedIdentity,
    LocalIdentity,
    PingTimeout,
    UserReason = 0x10,
    NoDisconnect = 0xffff
};

struct PeerSessionInfo {
    node_id id;
    char client_version[8];
    char host[16];
    unsigned short port;

    uint32_t protocol_version;
};

enum PeerType {
    Optional,
    Required,
};

struct node_ip_endpoint {
    bi::address address;
    uint16_t udp_port;
    uint16_t tcp_port;
};

struct node_spec {

    char address[16];
    uint16_t tcp_port;
    uint16_t udp_port;
    node_id id;
};

struct node {
    node_id id;
    struct node_ip_endpoint endpoint;
    PeerType type;
};
#endif