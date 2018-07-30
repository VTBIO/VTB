#include <stdio.h>
#include <stdlib.h>


static void udp_socket_init(struct udp_socket *udp)
{
    int fd;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        printf("%s create socket failed!\n", __func__);
        return;
    }


}

static void udp_socket_connect(struct udp_socket *udp)
{

}

static int udp_socket_send(struct udp_socket *udp, udp_datagram_t *data)
{

}

static int udp_socket_is_open(struct udp_socket *udp)
{

}

void udp_socket_disconnect(struct udp_socket *udp)
{

}

static void udp_socket_do_read(struct udp_socket *udp)
{

}

static void udp_socket_do_write(struct udp_socket *udp)
{

}

static void udp_socket_disconnect_with_error(struct udp_socket *udp, UDP_ERROR_CODE err)
{

}

static struct udp_socket_operations default_udp_socket_ops = {
    .init = udp_socket_init,
    .connect = udp_socket_connect,
    .send = udp_socket_send,
    .is_open = udp_socket_is_open,
    .disconnect = udp_socket_disconnect,
    .do_read = udp_socket_do_read,
    .do_write = udp_socket_do_write,
    .disconnect_with_error = udp_socket_disconnect_with_error,
};


#include "udp.h"