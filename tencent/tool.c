#define _BSD_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

const uint32_t default_num = UINT_MAX;
const uint32_t max_val = SHRT_MAX;

void gen_zero_file(char* fname, uint32_t size)
{
    int fd = open(fname, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
    if (-1 == fd) {
        perror("open");
        exit(0);
    }
    
    if (lseek(fd, (size - 1) * sizeof (uint32_t), SEEK_SET) == -1){
        perror("lseek");
        return;
    }
    
    uint32_t num = 0;
    write(fd, &num, sizeof (uint32_t));

    close(fd);
    printf("Done!\n");
}

void gen_random_file(char* fname, uint32_t size)
{
    int fd = open(fname, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
    if (-1 == fd) {
        perror("open");
        exit(0);
    }

    uint32_t i;
    for (i = 0; i < size; ++i){
        uint32_t num = random() % max_val;
        if (sizeof(uint32_t) != write(fd, &num, sizeof(uint32_t))){
            perror("write");
            exit(0);
        } 
    }

    close(fd);
    printf("Done!\n");
}

void print_file(const char* fname, uint32_t num)
{

    int fd = open(fname, O_RDONLY);
    if (-1 == fd){
        perror("print file open");
        return;
    }

    uint32_t n;
    uint32_t val = 0;
    while (num-- && (n = read(fd, &val, sizeof(uint32_t))) == sizeof(uint32_t)){
        printf("%u,", val);
    } 

    close(fd);
    printf("\nDone!\n");
}

void usage(char* name)
{
    printf("Usage: %s [-p|-g] file\n", name);
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        usage(argv[0]);
        exit(0);
    }


    if (0 == strcmp("-p", argv[1])){
        uint32_t num = (argc==4) ? atoi(argv[2]) : (uint32_t)-1;
        char* fname = (argc==4) ? argv[3] : argv[2];
        print_file(fname, num);
    }else if (0 == strcmp("-g", argv[1])){
        gen_random_file(argv[2], default_num);
    }else if (0 == strcmp("-z", argv[1])){
        gen_zero_file(argv[2], default_num);
    }else{
        usage(argv[0]);
        exit(0);
    }
    
    return 0;
}

