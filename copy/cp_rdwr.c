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

#define BUFSIZE 4096

static void usage(char *name)
{
	fprintf(stdout, "Usage: "
			"%s src_file dst_file\n", name);
}

static ssize_t xread(int fd, void *buffer, size_t len)
{
	ssize_t ret;
	ssize_t n;

	n = 0;
	while (n < (ssize_t) len) {
		ret = read(fd, (char *) buffer + n, len - n);
		if (ret < 0)
			return -1;
		if (ret == 0)
			break;
		n += ret;
	}

	return n;
}

/*
 * "upgraded" write routine
 */

static ssize_t xwrite(int fd, const void *buffer, size_t len)
{
	ssize_t ret;
	ssize_t n;

	n = 0;
	while (n < (ssize_t) len) {
		ret = write(fd, (const char *) buffer + n, len - n);
		if (ret < 0)
			return -1;
		if (ret == 0)
			break;
		n += ret;
	}

	return n;
}

static void copy_file(int fd_src, int fd_dst)
{
	int rc;
	ssize_t len;
	char buf[BUFSIZE];

	while(1) {
		len = read(fd_src, buf, BUFSIZE);
		DIE(len < 0, "read");

		if (len == 0)
			break;

		rc = xwrite(fd_dst, buf, len);
		DIE(rc < 0, "write");
	}

}

int main(int argc, char **argv)
{
	int fd_src, fd_dst;
	int rc;

	if (argc != 3) {
		usage(argv[0]);
		exit(1);
	}

	fd_src = open(argv[1], O_RDONLY);
	DIE(fd_src < 0, "open src");

	fd_dst = open(argv[2], O_CREAT | O_TRUNC | O_RDWR, 0644);
	DIE(fd_dst < 0, "open dst");

	copy_file(fd_src, fd_dst);

	rc = close(fd_src);
	DIE(rc < 0, "close src");

	rc = close(fd_dst);
	DIE(rc < 0, "close dst");

	return 0;
}
