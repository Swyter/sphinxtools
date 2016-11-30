#!/usr/bin/python

import struct

text_edb = '/home/swyter/Escritorio/STANDALONE/DATA/actual_text_file.edb'

with open(text_edb, 'rb') as f:

  magic=f.read(4)
  print(magic, struct.unpack('>I', magic)[0], struct.unpack('<I',b'GEOM')[0])

  f.seek(0x210)

  subsections = {}

  for i in range(1, 7):
    index=struct.unpack('<I', f.read(4))[0]
    offst=struct.unpack('<I', f.read(4))[0]

    subsections[index] = offst

    print("-> %x %x" % (index, offst))

    f.read(8)

  print(subsections)

  for i in subsections:
    print(i)

    f.seek(subsections[i])
    f.read(4) # skip the first empty int prefixing every subsection

    string_elements=struct.unpack('<I', f.read(4))[0]

    print(string_elements)

    for i in range (1, string_elements):
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
      print(f.read(str_length).decode('utf16'))

      f.seek(fin_offset)
