#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>



int main(int argc, char *argv[]) {
    int fd;
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        write(1, "Bad\n", 5);
        return 1;
    }

    char ch;

    while (read(fd, &ch, 1) > 0) {
        write(1, &ch, 1);
    }
    close(fd);

    return 0;
}