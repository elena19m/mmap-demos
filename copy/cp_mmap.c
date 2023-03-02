/*
 * Implementing 'cp' with mmap
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

static void usage(char *name)
{
	fprintf(stdout, "Usage: "
			"%s src_file dst_file\n", name);
}

static size_t get_file_size(int fd)
{
	int rc;
	struct stat st;

	rc = fstat(fd, &st);
	DIE(rc < 0, "fstat");

	return st.st_size;
}

static void copy_file(int fd_src, int fd_dst, size_t size)
{
	int rc;
	char *src, *dst;

	src = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd_src, 0);
	DIE(src == MAP_FAILED, "mmap src");

	dst = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_dst, 0);
	DIE(dst == MAP_FAILED, "mmap dst");

	memcpy(dst, src, size);

	rc = munmap(src, size);
	DIE(rc < 0, "unmap src");

	rc = munmap(dst, size);
	DIE(rc < 0, "unmap dst");
}

int main(int argc, char **argv)
{
	int fd_src, fd_dst;
	int rc;
	size_t size;

	if (argc != 3) {
		usage(argv[0]);
		exit(1);
	}

	fd_src = open(argv[1], O_RDONLY);
	DIE(fd_src < 0, "open src");

	fd_dst = open(argv[2], O_CREAT | O_TRUNC | O_RDWR, 0644);
	DIE(fd_dst < 0, "open dst");

	size = get_file_size(fd_src);

	rc = ftruncate(fd_dst, size);
	DIE(rc < 0, "ftruncate");

	copy_file(fd_src, fd_dst, size);

	rc = close(fd_src);
	DIE(rc < 0, "close src");

	rc = close(fd_dst);
	DIE(rc < 0, "close dst");

	return 0;
}
