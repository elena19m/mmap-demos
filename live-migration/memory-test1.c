#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define NUM_PAGES 100
static char msg[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit."
		"Mauris id lorem elementum, mollis diam eget, vestibulum metus."
		"Fusce ac ligula vestibulum, malesuada ipsum sed, accumsan leo.";

int
main(void)
{
	char *p;
	size_t page_size;
	size_t i;
	int rc;

	page_size = getpagesize();

	while (1) {
		p = mmap(NULL, NUM_PAGES * page_size, PROT_READ | PROT_WRITE,
			 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		if (p == MAP_FAILED) {
			fprintf(stderr, "Map failed.\r\n");
			exit(-1);
		}
		for (i = 0; i < NUM_PAGES; i++) {
			memcpy(p + i * page_size, msg, sizeof(msg));
		}

		rc = munmap(p, NUM_PAGES * page_size);
		if (rc == -1) {
			fprintf(stderr, "Unmap failed\r\n");
			exit(-2);
		}
	}

	return (0);
}
