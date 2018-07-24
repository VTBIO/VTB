#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "rocksdb/c.h"
#include "database.h"

#define DEFAULT_DIR_FILE "./data/vtb_data"
#define DEFAULT_BACKUP_DIR_FILE "./backup/vtb_data"

static rocksdb_t *db = null;

static struct db_config default_config = {
    .db_file = DEFAULT_DIR_FILE,
    .backup = 0,
    .backup_db_file = DEFAULT_BACKUP_DIR_FILE,
};

static void rocks_db_init(struct db_config *config)
{
    if (config == NULL) {

    }
}

static int rocks_db_open(void)
{
    char *err = null;

    rocksdb_options_t *options = rocksdb_options_create();
    // Optimize RocksDB. This is the easiest way to
    // get RocksDB to perform well
    long cpus = sysconf(_SC_NPROCESSORS_ONLN);  // get # of online cores
    rocksdb_options_increase_parallelism(options, (int)(cpus));
    rocksdb_options_optimize_level_style_compaction(options, 0);
    // create the DB if it's not already present
    rocksdb_options_set_create_if_missing(options, 1);

    // open DB
    db = rocksdb_open(options, default_config.db_file, &err);
    assert(!err);
}

void rocks_db_put(const char[] key, const char* value)
{
    rocksdb_writeoptions_t *writeoptions = rocksdb_writeoptions_create();
    rocksdb_put(db, writeoptions, key, strlen(key), value, strlen(value) + 1, &err);
    assert(!err);
}

/* Warning: free value */
static char *rocks_db_get(char[] key)
{
    rocksdb_readoptions_t *readoptions = rocksdb_readoptions_create();
    size_t len;
    char *value = rocksdb_get(db, readoptions, key, strlen(key), &len, &err);
    assert(!err);
    return value;
}

static void rocks_db_close(void)
{
    rocksdb_close(db);
}

/* static for config */

static struct db_operations_struct default_db_ops = {
    .init   = rocks_db_init,
    .open   = rocks_db_open,
    .put    = rocks_db_put,
    .get    = rocks_db_get,
    .close  = rocks_db_close,
};

static struct db_struct[] db_instance = {
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