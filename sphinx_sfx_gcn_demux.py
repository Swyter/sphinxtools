import sys

# NOTE: only music has interleaved stereo tracks, normal soundbank effects are just ADCPM mono.

# swy-- run it with sphinx_sfx_gcn_demux_convert.sh, requires an extracted sphinx
#       installation, sox, bash, echo, ffmpeg and an unix-style environment unless tweaked.

#       output as AAC (m4a) inside the folder ./GCN-soundtrack unless extension and path changed.

name = sys.argv[1]
hash = sys.argv[2]
code = "%06x" % (int(hash, 16) & 0xFFFFFF)

r = open("/tmp/pychan_r.ima", "wb+")
l = open("/tmp/pychan_l.ima", "wb+")

f = open("./x:/sphinx/binary/_bin_gc/music/hc" + code + ".sfx", "rb")
#f = open("/home/swyter/github/sphinxtools/x:/sphinx/binary/_bin_gc/music/hce00005.sfx", "rb")
#f = open("/home/swyter/github/sphinxtools/x:/sphinx/binary/_bin_gc/_eng/hc000000.sfx", "rb")
#f = open("/tmp/2b.ima", "rb")

# swy-- start of soundbank, not hardcoded but constant
f.seek(0x1000);

try:
    byte = f.read(1)
    while byte:
        # swy-- split interleaved IMA ADCPM bytes like in a zipper, right-channel bytes
        #       (odd) to one file, left-channel (even) bytes to another one.

        #       if every sample is 4 bytes there are two samples per byte/ at a time.

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

# swy-- convert to two different raw PCM files and mux the channels together with a decent lossy codec. ffmpeg is pretty neat!

count = int(open("/tmp/_counter", "r").read()) or 1

import os

os.system('sox -t ima -e ima-adpcm -c 1 -r 32000 /tmp/pychan_r.ima -b 4 /tmp/pyooout_r.wav');
os.system('sox -t ima -e ima-adpcm -c 1 -r 32000 /tmp/pychan_l.ima -b 4 /tmp/pyooout_l.wav');

os.system('ffmpeg -i /tmp/pyooout_l.wav -i /tmp/pyooout_r.wav -filter_complex "[0:a][1:a]amerge=inputs=2[aout]" -map "[aout]" "GCN-soundtrack/(%02i) %s [%s].m4a"' % (count, name, hash))

os.system('echo %i > /tmp/_counter' % (count + 1))
