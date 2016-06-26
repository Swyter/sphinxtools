# sphinxtools
Unpackers and modding tools for the GameCube version of the «Sphinx and the Cursed Mummy» game.


## Background

The game files are all packed inside an uncompressed container file called `Filelist.000`. The game engine actually reads a small binary descriptor file called `Filelist.bin`,
which contains a table mapping various internal hash codes with their original internal filenames, lengths and (one or more) container numbers with their respective offset/position inside every container. Those packed files tend to appear sector-aligned, and they are often duplicated in two or more places inside of the same container file to improve disk seek times.

As far as I can, tell only the PlayStation 2 version of the game splits the game files in more than one container (`Filelist.000` and `Filelist.001`), also the _PlayStation 2_ and _XBOX_ fields are stored in reversed byte-order (little-endian), while GameCube uses big-endian.
This tool should comply with all the different variants.

I have sucessfully extracted the contents of the _GameCube_, _PlayStation 2_ and _XBOX_ versions.

## How to use

My extractor is written in simple C99 with some UNIX functions, which require Linux, Mac or BSD to compile, even if you could compile it as a Windows executable with some small changes.

Compile the C file like this with your favourite Linux compiler (GCC or Clang):

    gcc sphinx_filelistbin_extract.c -o sphinx_filelistbin_extract

Extract all the `Filelist.bin`, `Filelist.000`, ... files from your original disk.

Place them in the same folder. That's all you need. Run the extractor in your Terminal:

    ./sphinx_filelistbin_extract Filelist.bin


The unpacked files will appear in the current directory under folders called as the original Windows hard drives (either `x:`, or `d:`) used by Eurocom.
