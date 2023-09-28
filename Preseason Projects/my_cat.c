#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char ** argv){
    int fd, ch;
    for(int i =1; i < argc; i+=1){
        fd = open(argv[i], O_RDONLY);
        while(read(fd, &ch, 1) == 1){
            write(STDOUT_FILENO, &ch, 1);

        }
    } close(fd);
}