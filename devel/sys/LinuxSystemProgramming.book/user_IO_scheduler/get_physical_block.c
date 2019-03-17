#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<unistd.h>

#include<linux/fs.h>

#include<stdio.h>
#include<stdlib.h>

int get_block(int fd, int logical_block) {
	/*
	 * get the block from the logical_block,
	 * which must be related to the fd
	 */
	int ret = ioctl(fd, FIBMAP, &logical_block);
	if(ret < 0) {
		perror("ioctl()");
		return EXIT_FAILURE;
	}
	return logical_block;
}

int get_nr_blocks(int fd) {
	/* get the number of the bloks in the fd */
	struct stat buf;
	int ret = fstat(fd, &buf);
	if(ret < 0) {
		perror("fstat()");
		return -1;
	}
	return buf.st_blocks;
}

void print_blocks(int fd) {
	/*
	 * print the such information:
	 * (logical_block, physical_block
	 */
	int nr_blocks = get_nr_blocks(fd);
	if(nr_blocks == -1) {
		fprintf(stderr, "get_nr_blocks() failed!\n");
		return;
	}
	if(nr_blocks == 0) {
		printf("no allocated blocks\n");
		return;
	} else if(nr_blocks == 1)
		printf("1 blocks\n\n");
	else
		printf("%d blocks\n\n", nr_blocks);

	int i;
	for(i = 0; i < nr_blocks; i++) {
		int phys_blocks = get_block(fd, i);
		if(phys_blocks < 0) {
			fprintf(stderr, "get_block() failed!\n");
			return;
		}
		if(!phys_blocks)
			continue;
		printf("(%u, %u)", i, phys_blocks);
	}
	putchar('\n');
}

int main(int argc, char **argv) {
	int fd;
	if(argc < 2) {
		fprintf(stderr, "usage %s <file>...\n", argv[0]);
		return EXIT_FAILURE;
	}
	int i;
	for(i = 1; i < argc; i++) {
		fd = open(argv[i], O_RDONLY);
		if(fd < 0) {
			perror("open()");
			return EXIT_FAILURE;
		}
		print_blocks(fd);
		close(fd);
	}
	return EXIT_SUCCESS;
}
