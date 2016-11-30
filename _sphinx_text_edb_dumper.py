#!/usr/bin/python

import struct

text_edb = '/home/swyter/Escritorio/STANDALONE/DATA/actual_text_file.edb'
hashcode = '/home/swyter/github/sphinxtools/x:/sphinx/albert/hashcodes.h'

hashcodes = {}

with open(hashcode, 'r') as f:
  for line in f:
    if (line[0] == '#'):
      l = line.split()
      hashcodes[int(l[2], 16)]=l[1]

with open(text_edb, 'rb') as f:

  magic=f.read(4)
  print(magic, struct.unpack('>I', magic)[0], struct.unpack('<I',b'GEOM')[0])


  f.seek(0x0c0)

  header_thing_size=struct.unpack('<I', f.read(4))[0]
  header_thing_elem=int((header_thing_size - 4) / (5 * 4))

  for i in range(header_thing_elem):
    spreadsheet_hash_ref=struct.unpack('<I', f.read(4))[0]
    spreadsheet_el_zeros=struct.unpack('<H', f.read(2))[0]
    spreadsheet_el_index=struct.unpack('<H', f.read(2))[0]
    spreadsheet_abs_nptr=struct.unpack('<I', f.read(4))[0]
    spreadsheet_00000000=struct.unpack('<I', f.read(4))[0]
    spreadsheet_10000000=struct.unpack('<I', f.read(4))[0]

    print("%x" % spreadsheet_hash_ref, spreadsheet_00000000, spreadsheet_abs_nptr, spreadsheet_el_zeros, spreadsheet_el_index, spreadsheet_10000000)

  exit()

  f.seek(0x210)

  subsections = {}

  for i in range(0, 7):
    index=struct.unpack('<I', f.read(4))[0]
    offst=struct.unpack('<I', f.read(4))[0]

    subsections[index] = offst

    print("-> %x %x" % (index, offst))

    f.read(8)

  print(subsections)

  for i in subsections:
    print(i, '_X_X_X_X_X_X_X_X_X_')

    f.seek(subsections[i])
    f.read(4) # skip the first empty int prefixing every subsection

    string_elements=struct.unpack('<I', f.read(4))[0]

    print(string_elements)

    for i in range (0, string_elements):
      str_hash_ref=struct.unpack('<I', f.read(4))[0]

      cur_offset = f.tell()

      str_r_offset=struct.unpack('<I', f.read(4))[0]
      str_n_offset=struct.unpack('<I', f.read(4))[0]
      ffffffffffff=struct.unpack('<I', f.read(4))[0]

      fin_offset = f.tell()

      str_length=str_n_offset - str_r_offset
      str_absolute_offset=cur_offset + str_r_offset

      print("%x" % str_hash_ref, str_r_offset, str_n_offset, "%x" % ffffffffffff)
      print(str_absolute_offset)

      f.seek(str_absolute_offset)
      print(hashcodes[str_hash_ref], '---', f.read(str_length).decode('utf16'), "\n")

      f.seek(fin_offset)

