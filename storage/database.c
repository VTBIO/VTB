#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "leveldb/c.h"
#include "database.h"

#define DEFAULT_DIR_FILE            "database"
#define DEFAULT_BACKUP_DIR_FILE     "backup_database"

static leveldb_t *db = NULL;
static leveldb_options_t *options = NULL;
static leveldb_writeoptions_t *woptions = NULL;
static leveldb_readoptions_t *roptions = NULL;

static struct db_config default_config = {
    .db_file = DEFAULT_DIR_FILE,
    .backup = 0,
    .backup_db_file = DEFAULT_BACKUP_DIR_FILE,
};

static void level_db_init(struct db_config *config)
{
    if (config == NULL) {

    }
}

static int level_db_open(void)
{
    char *err = NULL;

    options = leveldb_options_create();
    leveldb_options_set_create_if_missing(options, 1);
    db = leveldb_open(options, default_config.db_file, &err);
    if (err != NULL) {
        fprintf(stderr, "Open fail. %s\n", err);
        leveldb_free(err);
        return -1;
    }

    return 0;
}

void level_db_put(const char *key, const char* value)
{
    char *err = NULL;

    woptions = leveldb_writeoptions_create();
    leveldb_put(db, woptions, key, strlen(key), value, strlen(value), &err);
    if (err != NULL) {
        fprintf(stderr, "Write fail. %s\n", err);
        leveldb_free(err);
    }
}

/* Warning: free value */
static char *level_db_get(char *key)
{
    char *err = NULL;
    char *value = NULL;
    size_t read_len = -1;

    roptions = leveldb_readoptions_create();
    value = leveldb_get(db, roptions, key, strlen(key), &read_len, &err);
    if (err != NULL) {
        fprintf(stderr, "Read fail. %s\n", err);
        leveldb_free(err);
        return NULL;
    }

    return value;
}

static void level_db_del(char *key)
{
    char *err = NULL;

    leveldb_delete(db, woptions, key, strlen(key), &err);
    if (err != NULL) {
        leveldb_free(err);
        fprintf(stderr, "Delete fail. %s\n", err);
    }
}

static void level_db_close(void)
{
    leveldb_close(db);
}

/* static for config */

static struct db_operations_struct default_db_ops = {
    .init   = level_db_init,
    .open   = level_db_open,
    .put    = level_db_put,
    .get    = level_db_get,
    .delete = level_db_del,
    .close  = level_db_close,
};

static struct db_struct db_instance[] = {
    {
        .config = &default_config,
        .ops    = &default_db_ops,
    },
    {
    },
};

struct db_struct *get_db()
{
    return &db_instance[0];
}