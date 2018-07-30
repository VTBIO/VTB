#ifndef __NET_CONNECTION_H__
#define __NET_CONNECTION_H__

#include <apr_network_io.h>
#include <apr_thread_proc.h>
#include <apr_uuid.h>
#include <apr_thread_cond.h>
#include <apr_thread_mutex.h>

#include "list.h"

typedef struct p2p_connection {
    apr_socket_t *sock;
    apr_thread_t *reader;

    char ip_address[16];
    int port;

    head_list list;

} p2p_connection_t;



#endif /* __NET_CONNECTION_H__ */