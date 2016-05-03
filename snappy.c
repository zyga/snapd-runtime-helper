#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

static void init_snappy_shm() __attribute__((constructor));

static char snappy_shm_dir[NAME_MAX];

static void init_snappy_shm()
{
    char *SNAP_NAME;
    char *SNAP_REVISION;
    char name[NAME_MAX];
    int err;

    SNAP_NAME = getenv("SNAP_NAME");
    SNAP_REVISION = getenv("SNAP_REVISION");

    // XXX: this is SHMDIR in glibc
    strcpy(snappy_shm_dir, "/dev/shm/");

    if (strlen(SNAP_NAME) > 0 || strlen(SNAP_REVISION) > 0) {
        // NOTE: proper code would use mkdirat, this is not done here.
        err = snprintf(name, sizeof name, "/dev/shm/snap/%s/", SNAP_NAME);
        if (err < 0 || err == NAME_MAX - 1) {
            perror("cannot construct path /dev/shm/snap/$SNAP_NAME/");
            return;
        }
        err = mkdir(name, 0700);
        if (err != 0 && errno != EEXIST) {
            perror("cannot make /dev/shm/snap/$SNAP_NAME/");
            return;
        }
        err = snprintf(name, sizeof name, "/dev/shm/snap/%s/%s/", SNAP_NAME, SNAP_REVISION);
        if (err < 0 || err == NAME_MAX - 1) {
            perror("cannot construct path /dev/shm/snap/$SNAP_NAME/$SNAP_REVISION/");
            return;
        }
        err = mkdir(name, 0700);
        if (err != 0 && errno != EEXIST) {
            perror("cannot make /dev/shm/snap/$SNAP_NAME/$SNAP_REVISION/");
            return;
        }
        strcpy(snappy_shm_dir, name);
    }
}

const char *__shm_directory(size_t *len)
{
    *len = strlen(snappy_shm_dir);
    return snappy_shm_dir;
}
