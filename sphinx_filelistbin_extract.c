/* Structs of the filelist.bin file were reverse engineered with 010 editor from
   the contents stored in filelist.txt, also included in the GCN disk.
   
   Should work with various versions and platforms of Eurocom's EngineX with little work */

#include <stdint.h>
#include <stdio.h>

struct header
{
	uint8_t magic;
	uint8_t total_size; // <format=hex>;
	uint8_t list_item_count;
	uint8_t unk_b; // <format=hex>;
	uint8_t next_section; // <format=hex>; // + 10h (address relative to this field)
};

struct list_item
{
    uint8_t len;
    uint8_t hash; // <format=hex>;
    uint8_t ver;
    uint8_t unk_flags; //<format=hex>;
    uint8_t always_one;
    uint8_t loc_addr; //<format=hex>;
    uint8_t loc_file;
};

void main(int argc, char *argv[])
{
	puts("\n"
	     "  SPHINX AND THE CURSED MUMMY «FILELIST» EXTRACTOR              \n"
		 "  --------------------------------------------------------------\n"
	     "  (C) 2016-02-28 Created by Swyter <swyterzone+sphinx@gmail.com>\n"
	     "\n"
	     "  Licensed under MIT-like terms, this is a FOSS program.        \n");

	if (argc != 2)
	{
		printf("  This program extracts game files from filebin.0XX containers \n"
		       "  by reading the same filelist.bin descriptor used by the game.\n"
	           "\n"
		       "  > USAGE: %s <filelist.bin>\n\n", argv[0]);
		return;
	}

}
