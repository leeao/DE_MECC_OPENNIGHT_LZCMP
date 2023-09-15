#pragma once
typedef unsigned int uint;
typedef unsigned short ushort;
struct struct_409e4a  
{
    unsigned char* local_168;   //0
    int pad1;                   //0x4
    int local_160[16] = {0};    //0x8
    uint local_120;             //0x48
    ushort local_11c;           //0x4C
    ushort pad2;                //0x4E
    int local_118;              //0x50
    ushort local_114;           //0x54
    unsigned char local_112[258] = {}; //0x56
    short* local_10;                    //0x158
    short   pad3;               //0x15A
    unsigned char* local_c;     //0x16C
    short local_8;              //0x160
    short pad4;                 //0x162
};
struct struct_40a720
{
    int iVar1;
    uint uVar2;
    short local_114;
    ushort local_10c[2] = { 0 };
    ushort* local_108;
    ushort local_104[128] = { 0 };
};

struct struct_40a1cd
{
    int     local_148;              //0x0
    short   local_144[2];           //0x4
    short   local_140;              //0x8
    short   pad1;       
    short   local_13c;              //0xC
    short   pad2;
    unsigned char* local_138;       //0x10
    short   local_134;              //0x14
    short   pad3;
    unsigned char local_130;        //0x18
    char    pad4[3];
    short   local_12C;              //0x1C
    short   pad5;
    short   local_128;              //0x20
    short   pad6;
    unsigned char local_124;        //0x24
    char    pad7[3];
    short   local_120;              //0x28
    short   pad8;
    int     local_11c;              //0x2C
    short   local_118;              //0x30
    short   pad9;
    char    local_114;              //0x34
    char    pad10[3];
    int     local_110;              //0x38
    ushort  local_10c[2] = {};      //0x3C-0x40
    ushort* local_108;              //0x40-0x44
    ushort  local_104[128] = {};    //0x44-0x144
};

void __cdecl FUN_00409e4a(short* curTexCmpDataPtr, uint decmpBuffrPtr);
uint __cdecl get32bit_bits_FUN_0040b7f0(int param_1, int param_2, char param_3);
int __cdecl FUN_00409f9d(unsigned short* param_1, int cmpDataOffset, int param_3, int* temp64DecmpBufferPt, unsigned int* param_5);
int __cdecl FUN_0040a720(ushort* param_1, int param_2, int param_3, unsigned char* param_4);
int __cdecl FUN_0040aa1f(ushort* param_1, int param_2, int param_3, ushort** param_4, ushort* param_5);
int __cdecl FUN_0040a814(short* param_1, int param_2, int param_3, unsigned char* param_4, short* param_5);
int __cdecl
FUN_0040ab11(int param_1, int param_2, unsigned char param_3, unsigned char param_4, short param_5, short param_6,
    unsigned char* param_7);
int __cdecl FUN_0040b890(int param_1, int param_2, unsigned char param_3, short param_4, unsigned char* param_5);
int __cdecl get16bit_bits_FUN_0040b8f0(int param_1, int param_2, unsigned char param_3);
int __cdecl FUN_0040b980(int param_1, unsigned char param_2);
int __cdecl FUN_0040a8e6(short* param_1, int param_2, int param_3, unsigned char* param_4, ushort* param_5);
int __cdecl
FUN_0040ae49(int param_1, int param_2, unsigned char param_3, unsigned char param_4, short param_5, short param_6,
    unsigned char* param_7);
int __cdecl FUN_0040a1cd(ushort* param_1, int param_2, int param_3, unsigned char* param_4);
void __cdecl FUN_0040a0e9(int* param_1, unsigned char param_2);
void initTempBuffer1024_FUN_00409de0(void);
short getStorageWidth(int width);