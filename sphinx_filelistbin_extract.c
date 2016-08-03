/* Structs of the filelist.bin file were reverse engineered with 010 editor from
   the contents stored in filelist.txt, also included in the GCN disk.

   Should work with various retail versions and platforms of Eurocom's EngineX with little work */

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>

#include <string.h>
#include <endian.h>

#include <stdbool.h>
#include <stddef.h>

/* © 2016 Created by Swyter -- MIT licensed. Have fun! */

struct header
{
    uint32_t magic;
    uint32_t total_size;
    uint32_t list_item_count;

    /* 0x0001 and 0x0000 respectively, no idea, seems like a flag or counter */
    uint16_t unk_a;
    uint16_t unk_b;

    /* address relative to this field */
    uint32_t next_section;
};

struct list_item
{
    uint32_t len;
    uint32_t hash;
    uint32_t ver;
    uint32_t unk_flags;
    uint32_t offset_count;
    struct
    {
        uint32_t loc_addr;
        uint32_t loc_file;
    } offsets[1];
};

bool is_le = false;
#define ntohl(val) (!is_le ? be32toh(val) : le32toh(val))

void extract_to(char *descriptor, char *filename, uint32_t loc_addr, uint32_t loc_file, uint32_t len);

void main(int argc, char *argv[])
{

#ifdef _WIN32
    /* Windows doesn't like Unicode by default */
    #include <windows.h>
    SetConsoleOutputCP(CP_UTF8);
#endif

    puts(
        "\n"
        "  SPHINX AND THE CURSED MUMMY «FILELIST» RETAIL EXTRACTOR       \n"
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

    int fd = open(argv[1], O_RDONLY); struct stat s = {0};

    /* does the file exist? can we open it? is it a regular file? */
    if (fd >= 0 && fstat(fd, &s) >= 0) goto extract;

    printf(
        "  [x] Couldn't open «%s»: %s\n\n", argv[1], strerror(errno)
    );

    return;

extract:
    puts(
        "  [-] Mapping descriptor into memory...\n"
    );

    size_t size = s.st_size;

    void *map = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);

    if (map == MAP_FAILED)
    {
        printf("  [x] Couldn't mmap «%s»: %s\n\n", argv[1], strerror(errno)); return;
    }

    puts(
        "  [-] Extracting files...\n"
    );

    struct header *head = (struct header *)map;

    /* GameCube files are stored in big endian/network order, due to the PowerPC processor,
       PlayStation 2 files are little endian, mipsel arch, like most Intel computers */

    if (*(uint8_t *)&head->magic & (0x4 | 0x5))
    {
        puts("  [i] Switching to little-endian mode (PlayStation 2 game data?)..."); is_le = true;
    }

    if (ntohl(head->magic) == 0x4)
    {
        puts("  [i] Detected as version 4, the earlier format used in pre-retail demos!\n"
             "      This program only unpacks retail containers, use the demo extractor for this file.\n");
        return;
    }
    else if (ntohl(head->magic) == 0x5)
    {
        puts("  [i] Detected as version 5, the format used in retail containers!\n");
    }

    printf("  [debug] %p %p %x %x %zx--\n\n", map, head, ntohl(head->magic), ntohl(head->total_size), size);

    if (ntohl(head->total_size) != size)
    {
        puts("  [x] Invalid total size field. Probably a corrupted, unsupported\n"
             "      or incorrect «Filelist.bin» descriptor! Go figure! :(\n");
        return;
    }

    uint32_t *string_pointer = (uint32_t *)((size_t) &head->next_section + ntohl(head->next_section));

    for (
        struct list_item *item = map + sizeof(struct header);

        /* stop once we go past the next section (which is the string pointer block), not foolproof but works */
        (size_t) item < ((size_t) &head->next_section + ntohl(head->next_section));

        /* variable-sized makes everything harder, this basically computes `static part` + `dynamic part * entries` */
        item = (struct list_item *)((size_t) item + (offsetof(struct list_item, offsets)) +
                                                    (sizeof(item->offsets) * ntohl(item->offset_count))), string_pointer++
    )
    {

        char *filepath = (char *)((size_t) string_pointer + ntohl(*string_pointer));

        printf(
            "%-50s : Len %10u : Ver %4u : Hash %#010x : Loc %11x:%03u\n",
            filepath,
            ntohl(item->len),
            ntohl(item->ver),
            ntohl(item->hash),
            ntohl(item->offsets[0].loc_addr),
            ntohl(item->offsets[0].loc_file)
        );

        extract_to(argv[1], filepath, ntohl(item->offsets[0].loc_addr), ntohl(item->offsets[0].loc_file), ntohl(item->len));

        //return;
    }

    munmap(map, size);
    close(fd);
}

void extract_to(char *descriptor, char *filename, uint32_t loc_addr, uint32_t loc_file, uint32_t len)
{
    char containerpath[255] = {0};
    char extractedpath[255] = {0};
    char extractedfldr[255] = ".";

    strncpy(containerpath, descriptor, (sizeof(containerpath) - 1));
    strncpy(extractedpath, filename,   (sizeof(extractedpath) - 1));

#ifdef _WIN32
    /* Windows doesn't like : in folder names, change that */
    extractedpath[1] = ';';
#endif

    char *dot = strrchr(containerpath, '.') + 1;

    /* does it fit? or will overflow? */
    if ((dot - containerpath) + sizeof("000") > (sizeof(containerpath) - 1))
        return;

    snprintf(dot, sizeof("000"), "%03u", loc_file);


    char *slash = strrchr(extractedpath, '\\');
    char *token = strtok(extractedpath, "\\");

    do
    {
       snprintf(&extractedfldr[0] + strlen(extractedfldr), (sizeof(extractedfldr) - 1), "/%s", token);

       if (token < slash)
#ifdef _WIN32
         mkdir(extractedfldr);
#else
         mkdir(extractedfldr, 0744);
#endif

       //printf("  [debug] «%s» (%s)", token, extractedfldr);
    } while((token = strtok(NULL, "\\")));

    int fd_container = open(containerpath, O_RDONLY);
    int fd_extracted = open(extractedfldr, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (fd_container < 0 || fd_extracted < 0)
    {
        printf("  [x] Couldn't open «%s» or «%s»: %s\n\n", containerpath, extractedfldr, strerror(errno)); goto close;
    }

    struct stat s;
    fstat(fd_container, &s);

    size_t container_size = s.st_size;
    size_t extracted_size = len;

    /* the file we have just created is still empty, zero-fill with the needed length so
       that we have something to work with while mmap'ing, we don't want bus errors */
    ftruncate(fd_extracted, extracted_size);

    void *container_map = mmap(0, container_size, PROT_READ,  MAP_PRIVATE, fd_container, 0);
    char *extracted_map = mmap(0, extracted_size, PROT_WRITE, MAP_SHARED,  fd_extracted, 0);

    if (container_map == MAP_FAILED || extracted_map == MAP_FAILED)
    {
        printf("  [x] Couldn't mmap «%s» or «%s»: %s\n\n", containerpath, extractedfldr, strerror(errno)); goto cleanup;
    }

    //printf("\n  [debug] %x %x %x %u\n", extracted_map, container_map, loc_addr, len);

    memcpy(extracted_map, container_map + loc_addr, len);

cleanup:
    munmap(container_map, container_size);
    munmap(extracted_map, extracted_size);

close:
    if (fd_container >= 0) close(fd_container);
    if (fd_extracted >= 0) close(fd_extracted);
}
