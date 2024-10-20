#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct stat fileStat;

    // Ensure a file name is passed as an argument
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Get file status
    if (stat(argv[1], &fileStat) < 0) {
        perror("Error obtaining file information");
        return 1;
    }

    // Print inode details
    printf("File: %s\n", argv[1]);
    printf("Inode Number: %ld\n", (long)fileStat.st_ino);
    printf("File Mode: %o (octal)\n", fileStat.st_mode);
    printf("Number of Links: %ld\n", (long)fileStat.st_nlink);
    printf("File Size: %lld bytes\n", (long long)fileStat.st_size);
    printf("Block Size: %ld bytes\n", (long)fileStat.st_blksize);
    printf("Number of Blocks: %lld\n", (long long)fileStat.st_blocks);
    printf("Last Access Time: %ld\n", (long)fileStat.st_atime);
    printf("Last Modification Time: %ld\n", (long)fileStat.st_mtime);
    printf("Last Status Change Time: %ld\n", (long)fileStat.st_ctime);

    return 0;
}
