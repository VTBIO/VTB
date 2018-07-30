#ifndef __NET_UDP_H__
#define __NET_UDP_H__

#include "list.h"
#include "mutex.h"
#include "socket_inc.h"

struct udp_datagram {
    struct head_list list;
    uint32_t size;
    char data[0];
};

struct udp_socket_events {
    void (*on_disconnected)();
    void (*on_received)();
};

enum UDP_ERROR_CODE {

};

typedef struct udp_socket_operations {
    void (*init)(struct udp_socket *udp);
    void (*connect)(struct udp_socket *udp);
    int (*send)(struct udp_socket *udp, udp_datagram_t *data);
    int (*is_open)(struct udp_socket *udp);
    void (*disconnect)(struct udp_socket *udp);

    void (*do_read)(struct udp_socket *udp);
    void (*do_write)(struct udp_socket *udp);
    void (*disconnect_with_error)(struct udp_socket *udp, UDP_ERROR_CODE err);
};

struct udp_socket {
    uint32_t started;
    uint32_t closed;

    struct udp_event host;
    mutex_t send_mutex;
    struct head_list send_list;
    int sockfd;

    struct udp_socket_opearations *ops;
};

#endif /* __NET_UDP_H__ */