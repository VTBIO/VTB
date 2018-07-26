#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vtb.h"
#include "log.h"

int main(int argc, char **argv)
{
    struct vtb_struct *vtb= get_vtb();
    vtb->ops->init(vtb);

    // wait util receive shutdown cmd or ctl+c or signal ;
    vtb->ops->close(vtb);

    return 0;
}
