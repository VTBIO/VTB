#ifndef _STORAGE_DATABASE_H
#define _STORAGE_DATABASE_H

struct db_config {
    const char *db_file;
    int backup;
    const char *backup_db_file;
};

struct db_operations_struct {
    void (*init)(struct db_config *config);
    int (*open)(void);
    void (*put)(const char[] key, const char[] value);
    char *(*get)(char[] key);
    void (*close)(void);
};

struct db_struct {
    struct db_config *config;
    struct db_operations_struct *ops;
};

struct db_struct *get_db();

#endif /* _STORAGE_DATABASE_H */