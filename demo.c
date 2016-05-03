/* Demonstration program using shm_open(3). */

#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

int main()
{
    int fd;
    const char *name = "demo";
    printf("Using shm_open name: %s\n", name);
    fd = shm_open(name, O_RDWR|O_CREAT, 0600);
    if (fd < 0)
        perror("Cannot open shared memory");
    printf("Got fd: %d\n", fd);
    return 0;
}
