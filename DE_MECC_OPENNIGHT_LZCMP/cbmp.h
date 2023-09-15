#pragma once
struct CBMPTexHeader {
    short   width;
    short   height;
    unsigned int    offset;
    unsigned int    dataSize;
};
struct CBMPDataHeader {
    unsigned short  dataOffset;// Relative to data start offset
    char    flag1;
    char    flag2;//  if ( *(_BYTE *)(cmpBufferOffset + 3) & 1 )
    int     u2;
    unsigned int    decompressSize;// numBlock = (decompressSize + 63) / 64; BlockSize = 64. Tile 8x8 index color
};
