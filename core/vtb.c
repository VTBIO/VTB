#include <string.h>
#include <stdlib.h>


static struct vtb_operations_struct default_vtb_ops = {

};

static struct vtb_struct vtb_instance = {
    .ops = &default_vtb_ops,
};

struct vtb_struct *get_vtb()
{
    return &vtb_instance;
}