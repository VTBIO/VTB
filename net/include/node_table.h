#ifndef __NET_NODE_TABLE_H__
#define __NET_NODE_TABLE_H__

#include "mutex.h"
#include "common.h"

struct node_entry {
    uint32_t distance;
    int pending;
    struct list_head list;
};

enum node_table_event_type {
    NODE_ENTRY_ADDED,
    NODE_ENTRY_DROPPED,
};

struct node_table_event_handler {


    mutex_t mutex;

};

// using for node_table
enum node_relation {
    Unknown = 0,
    Known,
};

enum discovery_type {
    Random = 0,
};

struct node_bucket {
    uint32_t distance;
    struct head_list list; /* list of node_entry */
};

struct node_table;
struct node_table_operations {
    int (*distance)(struct node_table *nt, node_id *a, node_id *b);
    void (*set_event_handler)(struct node_table *nt, node_table_event_handler *handler);
    void (*process_events)(struct node_table *nt);
    node_entry *(*add_node)(struct node_table *nt, node *node, node_relation relation);
    struct list_head *(*nodes)(struct node_table *nt);
    uint32_t (*count)(struct node_table *nt);
    int (*have_node)(struct node_table *nt, node_id *id);


    // used to ping endpoint
    void (*ping)(struct node_table *nt, node_ip_endpoint *to);

    // Used ping known node. Used by node table when refreshing buckets and as part of eviction process (see evict).
    void (*ping)(struct node_table *nt, node_entry *entry);

    // Returns center node entry which describes this node and used with dist() to calculate xor metric for node table nodes.
    node_entry *(*center)(struct node_table *nt);

    // Used by asynchronous operations to return NodeEntry which is active and managed by node table.
    node_entry *(*node_entry)(struct node_table *nt, node_id id);

    /// Used to discovery nodes on network which are close to the given target.
    /// Sends s_alpha concurrent requests to nodes nearest to target, for nodes nearest to target, up to s_maxSteps rounds.
    void (*do_discover)(struct node_table *nt, node_id *target, uint32_t round, node_entry *tried);

    // Returns nodes from node table which are closest to target.
    struct list_head *(*nearst_node_entries)(struct node_table *nt, node_id *target);

    // Asynchronously drops _leastSeen node if it doesn't reply and adds _new node, otherwise _new node is thrown away.
    void (*evict)(struct node_table *nt, node_entry *least_seen, noed_entry *new_node);

    // Called whenever activity is received from a node in order to maintain node table.
    void (*note_active_node)(struct node_table *nt, public_struct *pubk, bi::udp::endpoint *endpoint);

    // Used to drop node when timeout occurs or when evict() result is to keep previous node.
    void (*drop_node)(struct node_table *nt, node_entry *node);

    /// Returns references to bucket which corresponds to distance of node id.
    /// @warning Only use the return reference locked x_state mutex.
    // TODO p2p: Remove this method after removing offset-by-one functionality.
    node_bucket *(bucket_UNSAFE)(struct node_table *nt, node_entry* _n);

    /// general network event

    // Called by m_socket when packet is received.
    void (*on_received)(struct node_table *nt, struct udp_socket *sock, bi::udp::endpoint *from, char *packet);

    // Called by m_socket when socket is disconnected.
    void (*on_disconnected)(struct node_table *nt, struct udp_socket *sock);


    // task
    // Called by evict() to ensure eviction check is scheduled to run and terminates when no evictions remain. Asynchronous.
    void (*do_check_evictions)(struct node_table *nt);

    // Looks up a random node at @c_bucketRefresh interval.
    void (*do_discovery)(struct node_table *nt);






};


struct node_table {
    struct node node;

    mutex_t x_node;
    struct list_head nodes;

    mutex_t x_state;
    struct list_head states;

    mutex_t x_eviction;
    struct list_head evictions;

    mutex_t x_find_node_timeout;
    struct list_head find_node_timeouts;

    struct node_socket socket;

    struct node_table_event_handler *node_event_handler;
    struct udp_socket_events *events;

    struct node_table_operations *ops;
};


/*******************************************************************/
struct discovery_datagram {  // commom: rlpx_datagram_face
    // These two are set for inbound packets only.
    node_id source_id;  // sender public key (from signature)
    h256 echo;          // hash of encoded packet, for reply tracking

    // All discovery packets carry a timestamp, which must be greater than the current local time. This prevents replay attacks.
    uint32_t ts;
};

/**
 * Ping packet: Sent to check if node is alive.
 * PingNode is cached and regenerated after ts + t, where t is timeout.
 * Ping is used to implement evict. When a new node is seen for a given bucket which is full, the least-responsive node is pinged.
 * If the pinged node doesn't respond, then it is removed and the new node is inserted.
 *
 */
struct ping_node {
    struct discovery_datagram comm;
    uint8_t type;       // default is 1
    uint32_t version;   // default is 0
    struct node_ip_endpoint source;
    struct node_ip_endpoint destination;
};

// pong packet : using for response to ping
struct pong {
    struct discovery_datagram comm;
    uint8_t type;       // default is 2
    struct node_ip_endpoint destination;
};

/**
 * FindNode Packet: Request k-nodes, closest to the target.
 * FindNode is cached and regenerated after ts + t, where t is timeout.
 * FindNode implicitly results in finding neighbours of a given node.
 *
 * target: NodeID of node. The responding node will send back nodes closest to the target.
 *
 */
struct find_node {
    struct discovery_datagram comm;
    uint8_t type;   // default is 3
    h512 target;
};

struct neighbour {
    struct node_ip_endpoint endpoint;
    node_id id;
};

struct neighbours {
    struct discovery_datagram comm;
    uint8_t type;   // default is 4
    uint32_t neighbours_num;
    struct neighbour neighbour[0];
};

////////////////////////////////////
struct node_table *get_node_table();

#endif /* __NET_NODE_TABLE_H__ */