#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

static char msg[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit."
                "Mauris id lorem elementum, mollis diam eget, vestibulum metus."
                "Fusce ac ligula vestibulum, malesuada ipsum sed, accumsan leo.";

static char msg2[] = "FreeBSD - bhyve";

int
main(void)
{
        char *p;
        size_t page_size;
        size_t i;
        size_t mem_size;
        size_t num_pages;
        int rc;

        page_size = getpagesize();
        mem_size = 2UL * 1024UL * 1024UL * 1024UL;
        num_pages = mem_size / page_size;

        p = mmap(NULL, mem_size, PROT_READ | PROT_WRITE,
                         MAP_SHARED | MAP_ANONYMOUS, -1, 0);

        if (p == MAP_FAILED) {
                fprintf(stderr, "Map failed.\r\n");
                exit(-1);
        }

        do {
                for (i = 0; i < num_pages; i++) {
                        if (i % 2 == 0)
                                memcpy(p + i * page_size, msg, sizeof(msg));
                        else
                                memcpy(p + i * page_size, msg2, sizeof(msg2));
                }

        } while (1);

        rc = munmap(p, mem_size);
        if (rc == -1) {
                fprintf(stderr, "Unmap failed\r\n");
                exit(-2);
        }
        return (0);
}
