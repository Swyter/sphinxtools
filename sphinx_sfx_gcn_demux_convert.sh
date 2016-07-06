#!/bin/bash
# swy-- this script automates the demuxing and conversion of stereo
#       gamecube-format *music*, sound effects are stored in mono.

 echo 1 > /tmp/_counter

 python sphinx_sfx_gcn_demux.py MFX_Aby_Council_Int1  0x1BE00000
 python sphinx_sfx_gcn_demux.py MFX_Aby_Council_Int2  0x1BE00001
 python sphinx_sfx_gcn_demux.py MFX_Aby_Juggler       0x1BE00002
 python sphinx_sfx_gcn_demux.py MFX_Aby_Main          0x1BE00003
 python sphinx_sfx_gcn_demux.py MFX_Aby_North         0x1BE00004
 python sphinx_sfx_gcn_demux.py MFX_Action1           0x1BE00005
 python sphinx_sfx_gcn_demux.py MFX_Ambient1          0x1BE00006
 python sphinx_sfx_gcn_demux.py MFX_Ambient2          0x1BE00007
 python sphinx_sfx_gcn_demux.py MFX_Ambient3          0x1BE00008
 python sphinx_sfx_gcn_demux.py MFX_Ambient4          0x1BE00009
 python sphinx_sfx_gcn_demux.py MFX_Boss1             0x1BE0000A
 python sphinx_sfx_gcn_demux.py MFX_Boss2             0x1BE0000B
 python sphinx_sfx_gcn_demux.py MFX_Boss3             0x1BE0000C
 python sphinx_sfx_gcn_demux.py MFX_Boss4             0x1BE0000D
 python sphinx_sfx_gcn_demux.py MFX_Danger1           0x1BE0000E
 python sphinx_sfx_gcn_demux.py MFX_Danger2           0x1BE0000F
 python sphinx_sfx_gcn_demux.py MFX_Danger3           0x1BE00010
 python sphinx_sfx_gcn_demux.py MFX_Military          0x1BE00011
 python sphinx_sfx_gcn_demux.py MFX_MiniGame_Intro    0x1BE00012
 python sphinx_sfx_gcn_demux.py MFX_MiniGame_Pairs    0x1BE00013
 python sphinx_sfx_gcn_demux.py MFX_MiniGame_Shoot    0x1BE00014
 python sphinx_sfx_gcn_demux.py MFX_MiniGame_Simon    0x1BE00015
 python sphinx_sfx_gcn_demux.py MFX_MiniGame_Walls    0x1BE00016
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Bat1        0x1BE00017
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Bat2        0x1BE00018
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Bat3        0x1BE00019
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Elec1       0x1BE0001A
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Elec2       0x1BE0001B
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Elec3       0x1BE0001C
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Fire1       0x1BE0001D
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Fire2       0x1BE0001E
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Fire3       0x1BE0001F
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Paper1      0x1BE00020
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Paper2      0x1BE00021
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Paper3      0x1BE00022
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Smoke       0x1BE00023
 python sphinx_sfx_gcn_demux.py MFX_Mummy_Stone       0x1BE00024
 python sphinx_sfx_gcn_demux.py MFX_Nomads            0x1BE00035
 python sphinx_sfx_gcn_demux.py MFX_Pause             0x1BE00036
 python sphinx_sfx_gcn_demux.py MFX_Platform1         0x1BE00025
 python sphinx_sfx_gcn_demux.py MFX_Possess_Dino      0x1BE00038
 python sphinx_sfx_gcn_demux.py MFX_Possess_Pokemon   0x1BE00037
 python sphinx_sfx_gcn_demux.py MFX_Puzzle1           0x1BE00026
 python sphinx_sfx_gcn_demux.py MFX_Puzzle2           0x1BE00027
 python sphinx_sfx_gcn_demux.py MFX_Sak_Main          0x1BE00028
 python sphinx_sfx_gcn_demux.py MFX_Silence           0x1BE00029
 python sphinx_sfx_gcn_demux.py MFX_Silence_loop      0x1BE0002A
 python sphinx_sfx_gcn_demux.py MFX_Sneak1_Jail       0x1BE0002B
 python sphinx_sfx_gcn_demux.py MFX_Sneak1_Jail_Intro 0x1BE0002C
 python sphinx_sfx_gcn_demux.py MFX_Sneak2_Puzzle     0x1BE0002D
 python sphinx_sfx_gcn_demux.py MFX_Sorrow            0x1BE0002E
 python sphinx_sfx_gcn_demux.py MFX_Swim              0x1BE0002F
 python sphinx_sfx_gcn_demux.py MFX_Swim_Danger       0x1BE00030
 python sphinx_sfx_gcn_demux.py MFX_Temple1           0x1BE00031
 python sphinx_sfx_gcn_demux.py MFX_Temple2           0x1BE00032
 python sphinx_sfx_gcn_demux.py MFX_Title             0x1BE00033
 python sphinx_sfx_gcn_demux.py MFX_Title_EndSting    0x1BE00034
