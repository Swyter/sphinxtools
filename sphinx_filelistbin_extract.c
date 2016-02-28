/* Structs of the filelist.bin file were reverse engineered with 010 editor from
   the contents stored in filelist.txt, also included in the GCN disk.

   Should work with various versions and platforms of Eurocom's EngineX with little work */

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>

#include <string.h>
#include <arpa/inet.h>

struct header
{
    uint32_t magic;
    uint32_t total_size; // <format=hex>;
    uint32_t list_item_count;
    uint32_t unk_b; // <format=hex>;
    uint32_t next_section; // <format=hex>; // + 10h (address relative to this field)
};

struct list_item
{
    uint32_t len;
    uint32_t hash; // <format=hex>;
    uint32_t ver;
    uint32_t unk_flags; //<format=hex>;
    uint32_t always_one;
    uint32_t loc_addr; //<format=hex>;
    uint32_t loc_file;
};

void main(int argc, char *argv[])
{
    puts(
        "\n"
        "  SPHINX AND THE CURSED MUMMY «FILELIST» EXTRACTOR              \n"
        "  --------------------------------------------------------------\n"
        "  (C) 2016-02-28 Created by Swyter <swyterzone+sphinx@gmail.com>\n"
        "\n"
        "  Licensed under MIT-like terms, this is a FOSS program.        \n"
    );

    if (argc == 2) goto open;

    printf(
        "  This program extracts game files from filebin.0XX containers \n"
        "  by reading the same filelist.bin descriptor used by the game.\n"
        "\n"
        "  > USAGE: %s <filelist.bin>\n\n", argv[0]
    );

    return;

open:
    puts(
        "  [-] Opening descriptor...\n"
    );

    if (access(argv[1], R_OK) != -1) goto extract;

    printf(
        "  [x] Couldn't open «%s»\n\n", argv[1]
    );

    return;

extract:
    puts("  [-] Extracting files...\n");

    int fd = open(argv[1], O_RDONLY);

    if (fd < 0)
    {
        puts("open failed");
        return;
    }

    struct stat s;
    fstat(fd, &s);

    size_t size = s.st_size;

    void *map = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);

    if (map == MAP_FAILED)
    {
        printf("map failed: %s\n", strerror(errno));
        return;
    }

    struct header *head = (struct header *)map;


    printf("%p %p %x %x %x--\n\n", map, head, ntohl(head->magic), ntohl(head->total_size), size);

    if (ntohl(head->total_size) != size)
        return;

    for (struct list_item *item = map + sizeof(struct header); (size_t) item < (size_t) head + (sizeof(struct list_item) * ntohl(head->list_item_count)) ; item++)
    {

        uint32_t *string_pointer = (uint32_t *)(((size_t) &head->next_section) + ntohl(head->next_section));


        printf(
            "%-50s : Len %10u : Ver %4u : Hash %#010x : Loc %11x:%03u\n",
            (size_t)string_pointer + ntohl(*string_pointer),  //((size_t) &head->next_section - (size_t)head) + ntohl(head->next_section),
            ntohl(item->len),
            ntohl(item->ver),
            ntohl(item->hash),
            ntohl(item->loc_addr),
            ntohl(item->loc_file));
    }

    munmap(map, s.st_size);
    close(fd);
}
