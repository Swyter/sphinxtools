
r = open("/tmp/pychan_r.ima", "wb+")
l = open("/tmp/pychan_l.ima", "wb+")

f = open("/home/swyter/github/sphinxtools/x:/sphinx/binary/_bin_gc/music/hce00005.sfx", "rb")
#f = open("/home/swyter/github/sphinxtools/x:/sphinx/binary/_bin_gc/_eng/hc000000.sfx", "rb")
#f = open("/tmp/2b.ima", "rb")
f.seek(0x1000);

try:
    byte = f.read(1)
    while byte:
        # Do stuff with byte.

        r.write(byte)
        l.write(f.read(1))

        #o.write(bytes([  (ord(byte) & 0xf) << 4 | (ord(f.read(1)) & 0xf)  ])  )
        #(byte[0] & 0xf) << 4 | byte[1] & 0xf)
        byte = f.read(1)
        #print("%d" % len(byte) )
finally:
    f.close()
    l.close()
    r.close()

import os

os.system('sox -t ima -e ima-adpcm -c 1 -r 32000 /tmp/pychan_r.ima -b 4 /tmp/pyooout_r.wav');
os.system('sox -t ima -e ima-adpcm -c 1 -r 32000 /tmp/pychan_l.ima -b 4 /tmp/pyooout_l.wav');

os.system('ffmpeg -i /tmp/pyooout_l.wav -i /tmp/pyooout_r.wav -filter_complex "[0:a][1:a]amerge=inputs=2[aout]" -map "[aout]" pyoutput_sound.m4a')

