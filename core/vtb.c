#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vtb.h"

static int vtb_init(struct vtb_struct *vtb)
{
    struct db_struct *db;
    struct net_struct *net;

    // init db
    db = get_db();
    db->ops->init(NULL);
    db->ops->open();
    vtb->db = db;

    // init net

    { // test db
        char *value = NULL;
        //db->ops->put("vtb-0000-0000-0000-0001", "this is the first record for test!");
        //db->ops->put("vtb-0000-0000-0000-0002", "this is the second record for test!");

        value = db->ops->get("vtb-0000-0000-0000-0001");
        printf("get result : {key:vtb-0000-0000-0000-0001, value:%s}\n", value);
        value = db->ops->get("vtb-0000-0000-0000-0002");
        printf("get result : {key:vtb-0000-0000-0000-0002, value:%s}\n", value);

        value = db->ops->get("vtb-0000-0000-0000-0003");
        printf("get result : {key:vtb-0000-0000-0000-0003, value:%s}\n", value);
    }




    return 0;
}

static int vtb_start_rpc_service(struct vtb_struct *vtb)
{
    return 0;
}


static void vtb_close(struct vtb_struct *vtb)
{
    struct db_struct *db = vtb->db;
    db->ops->close();
}

static struct vtb_operations_struct default_vtb_ops = {
    .init = vtb_init,
    .start_rpc_service = vtb_start_rpc_service,
    .close = vtb_close,
};

static struct vtb_struct vtb_instance = {
    .ops = &default_vtb_ops,
};

struct vtb_struct *get_vtb()
{
    return &vtb_instance;
}