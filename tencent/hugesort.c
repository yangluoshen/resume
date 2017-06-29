#define _BSD_SOURCE
#include <limits.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

const size_t max_num_sz = UINT_MAX * sizeof(uint32_t);

void print(const uint32_t* buf, uint32_t len)
{
    uint32_t i;
    for (i = 0; i < len; ++i){
        printf ("%u,", buf[i]);
    }
    printf("\n");
}

uint32_t get_max(const uint32_t* src, uint32_t len)
{
    uint32_t max = 0;
    int i;
    for (i = 0; i < len ; ++i){
        if (max < src[i]) max = src[i];
    }

    return max;
}

void count_sort(const uint32_t* src, uint32_t* dest, uint32_t* tmp, uint32_t src_size, uint32_t tmp_size)
{
    uint32_t i;
    for (i = 0; i < src_size; ++i){
        //tmp[src[i]] = tmp[src[i]] + 1;
        tmp[src[i]] += 1;
    }
    
    for (i = 1; i < tmp_size; ++i){
        //tmp[i] = tmp[i] + tmp[i-1];
        tmp[i] += tmp[i-1];
    }

    //printf("tmp:");
    //print(tmp, tmp_size);

    for (i = src_size - 1; i != (uint32_t)-1; --i){
        dest[tmp[src[i]] - 1] = src[i];
        //tmp[src[i]] = tmp[src[i]] - 1;
        tmp[src[i]] -= 1;
    }
}

int do_sort(const char* src, char* dest, uint32_t size)
{
    const uint32_t* uint_src = (const uint32_t*) src;
    uint32_t* uint_dest = (uint32_t*) dest;

    uint32_t max_num = get_max(uint_src, size / sizeof(uint32_t));
    printf("max_num:%u\n", max_num);

    // max_num + 1 is essential !! 
    // because max_num is one element in src, tmpbuf must give a position to it.
    uint32_t tmpbuf_sz = max_num + 1;
    int anonymous_fd = open("/dev/zero", O_RDWR); 
    // tmp_buf would be initialized by 0x00
    char* tmp_buf = mmap(NULL, tmpbuf_sz * sizeof(uint32_t), PROT_READ|PROT_WRITE, MAP_PRIVATE, anonymous_fd, 0); 
    if (MAP_FAILED == tmp_buf){
        perror("tmp_buf mmap");
        exit(1);
    }

    count_sort(uint_src, uint_dest, (uint32_t*)tmp_buf, size / sizeof(uint32_t), tmpbuf_sz); 

    //print(uint_src, size / sizeof (uint32_t));
    //printf("\n");
    //print(uint_dest, size / sizeof(uint32_t));
    return 0;
}

void gen_random(uint32_t* src, uint32_t size, uint32_t max_num)
{
    uint32_t i;
    for (i = 0; i < size; ++i){
        uint32_t val = random() % max_num;
        src[i] = val;
    }
}

void test_count_sort()
{
#define src_size (SHRT_MAX)
#define tmp_size (SHRT_MAX)
    uint32_t src[src_size];
    uint32_t dest[src_size] = {0};
    uint32_t tmp[tmp_size] = {0};

    gen_random(src, src_size, tmp_size);

    count_sort(src, dest, tmp, src_size, tmp_size); 
     
    //print(src, src_size);
    print(dest, src_size);
}

void test_huge()
{
    int fd = open("in.dat", O_RDONLY);
    if (-1 == fd) exit(1);
    
    char* src_buf = mmap(NULL, max_num_sz, PROT_READ, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == src_buf) {
        perror("src_buf mmap");
        exit(1);
    }
    
    int out_fd = open("out.dat", O_RDWR|O_CREAT, S_IWUSR|S_IRUSR|S_IRGRP|S_IWGRP);
    if (-1 == out_fd) {
        perror("open out.dat");
        exit(1);
    }
    char* dest_buf = mmap(NULL, max_num_sz, PROT_READ|PROT_WRITE, MAP_SHARED, out_fd, 0); 
    if (MAP_FAILED == dest_buf) {
        perror("dest_buf mmap");
        exit(1);
    }

    do_sort(src_buf, dest_buf, max_num_sz);

    printf("Done!\n");
}

int main(int argc, char* argv[])
{
    test_huge();
    //test_count_sort();
    return 0;
}
