#ifndef _VTB_VTB_H
#define _VTB_VTB_H

/* interface operation */
struct vtb_operations_struct {

};

struct vtb_struct {
    struct vtb_operations_struct *ops;
};

struct vtb_struct *get_vtb();

#endif /* _VTB_VTB_H */