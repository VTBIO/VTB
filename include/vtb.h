#ifndef _VTB_VTB_H
#define _VTB_VTB_H

#include "database.h"
#include "rpc.h"
#include "net.h"
#include "config.h"

struct vtb_struct;

/* interface operation */
struct vtb_operations_struct {
    int (*init)(struct vtb_struct *vtb);
    int (*start_rpc_service)(struct vtb_struct *vtb);

    void (*close)(struct vtb_struct *vtb);
};

struct vtb_struct {
    struct db_struct *db;
    struct net_struct *net;
    struct rpc_struct *rpc;

    struct vtb_operations_struct *ops;
};

struct vtb_struct *get_vtb();
#endif /* _VTB_VTB_H */