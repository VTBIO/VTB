#include "node_table.h"
#include "mutex.h"

static struct node_entry *create_node_entry(node_id *local_id, node_id *id, struct node_ip_endpoint endpoint)
{

    return NULL;
}

/*******************************************************************/

static void process_events(struct node_table *nt)
{
    if (node_event_handler != NULL) {
        node_event_handler->process_events();
    }
}

static node_entry *add_node(struct node_table *nt, node *node, node_relation relation)
{
    struct node_entry *entry;

    if (relation == Known) {
        entry = create_node_entry();
        entry->pending = false;

        mutex_lock(&nt->x_node);
        list_add(&nt->nodes, &entry->list);
        mutex_unlock(&nt->x_node);

        note_active_node(nt, node->id, node->endpoint);
        return entry;
    }

    if (node->endpoint == NULL)
        return NULL;

    if (node->id == NULL) {
        ping(nt, node->endpoint);
        return NULL;
    }

    entry = create_node_entry();
    mutex_lock(&nt->x_node);
    list_add(&nt->nodes, &entry->list);
    mutex_unlock(&nt->x_node);
    ping(nt, node->endpoint);
    return entry;
}

static struct list_head *nodes(struct node_table *nt)
{
    // TODO : warning not lock here.
    return &nt->nodes;
}

static struct node_entry *node_entry(struct node_table *nt, node_id id)
{
    //
}

static void do_discover(struct node_table *nt, node_id *target, uint32_t round, node_entry *tried)
{

}

static struct list_head *nearst_node_entries(struct node_table *nt, node_id *target)
{

}

static void ping(struct node_table *nt, node_ip_endpoint *to)
{

}

static void ping(struct node_table *nt, node_entry *entry)
{
    if (nt && entry) {
        ping(nt, entry->endpoint);
    }
}

static void evict(struct node_table *nt, node_entry *least_seen, noed_entry *new_node)
{

}

static void note_active_node(struct node_table *nt, public_struct *pubk, bi::udp::endpoint *endpoint)
{

}

static void drop_node(struct node_table *nt, node_entry *node)
{

}

static void on_received(struct node_table *nt, struct udp_socket *sock, bi::udp::endpoint *from, char *packet)
{

}

static void do_check_evictions(struct node_table *nt)
{

}

static void do_discovery(struct node_table *nt)
{

}







/* init */
void node_table_init(struct node_table *nt)
{
    mutex_init(&nt->x_node);
    mutex_init(&nt->x_state);
    mutex_init(&nt->x_eviction);
    mutex_init(&nt->x_find_node_timeout);

    INIT_LIST_HEAD(&nt->nodes);
    INIT_LIST_HEAD(&nt->states);
    INIT_LIST_HEAD(&nt->evictions);
    INIT_LIST_HEAD(&nt->find_node_timeouts);
}

void node_table_exist(struct node_table *nt)
{
    mutex_destroy(&nt->x_node);
    mutex_destroy(&nt->x_state);
    mutex_destroy(&nt->x_eviction);
    mutex_destroy(&nt->x_find_node_timeout);
}

static struct node_table_operations default_nt_ops = {

};

static struct node_table table = {
    .ops = &default_nt_ops,
};

struct node_table *get_node_table() {
    return &table;
}

