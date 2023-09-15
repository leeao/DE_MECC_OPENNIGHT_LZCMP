#include "DE_LZCMP.h"
#include <memory>

unsigned int tempBuffer1024[256]{0};

void __cdecl FUN_00409e4a(short* curTexCmpDataPtr,uint decmpBuffrPtr)//, undefined** param_2)

{

    struct_409e4a header;

    header.local_10 = curTexCmpDataPtr;
    header.local_c = (unsigned char*)((int)*curTexCmpDataPtr + (int)curTexCmpDataPtr);
    header.local_8 = (short)((int)(*(int*)(curTexCmpDataPtr + 4) + 0x3f +
        (*(int*)(curTexCmpDataPtr + 4) + 0x3f >> 0x1f & 0x3fU)) >> 6);
    header.local_118 = 0;
    if ((*(unsigned char*)((int)curTexCmpDataPtr + 3) & 1) != 0) {
        header.local_114 = *header.local_c + 1; //count
        header.local_c = header.local_c + 1;  // cmpBufferPtr
        header.local_168 = header.local_112;  // current temp 258 buffer ptr
        header.local_11c = header.local_114;  // current count
        do {
            *header.local_168 = *header.local_c;
            header.local_c = header.local_c + 1;
            header.local_168 = header.local_168 + 1;
            header.local_11c = header.local_11c - 1;
        } while (header.local_11c != 0);
        header.local_112[256] = 2;
    }
    header.local_11c = header.local_8;
    do {
        header.local_118 = FUN_00409f9d(&header.local_114, (int)header.local_c, header.local_118, header.local_160, &header.local_120);
        do{
            memcpy_s((char*)decmpBuffrPtr, 64, (char*)header.local_160, 64);
            header.local_11c = header.local_11c + -1;
            header.local_120 = header.local_120 - 1;
            decmpBuffrPtr += 64;
            if (((int)header.local_120 < 0) || (header.local_11c == 0)) break;
        } while (header.local_11c);
        if (header.local_11c == 0) {
            return;
        }
    } while (true);


}

uint __cdecl get32bit_bits_FUN_0040b7f0(int param_1, int param_2, char param_3)

{

    unsigned char* pbVar1;

    pbVar1 = (unsigned char*)((param_2 >> 3) + param_1);
    return ((((uint)*pbVar1 * 0x100 + (uint)pbVar1[1]) * 0x100 + (uint)pbVar1[2]) * 0x100 +
        (uint)pbVar1[3] << ((unsigned char)param_2 & 7)) >> (0x20U - param_3 & 0x1f);

}

int __cdecl
FUN_00409f9d(unsigned short* param_1, int cmpDataOffset, int param_3, int* temp64DecmpBufferPt, unsigned int* param_5)

{
    int iVar1;
    char cVar2;
    uint uVar3;
    uint uVar4;
    int local_14;
    int local_10;
    int local_c;
    char local_8;

    *param_5 = 0;
    uVar3 = get32bit_bits_FUN_0040b7f0(cmpDataOffset, param_3, '\x02');
    cVar2 = (char)uVar3;
    iVar1 = param_3 + 2;
    if (cVar2 == '\0') {
        param_3 = FUN_0040a720(param_1, cmpDataOffset, iVar1, (unsigned char*)temp64DecmpBufferPt);
    }
    else if (cVar2 == '\x01') {
        param_3 = FUN_0040a1cd(param_1, cmpDataOffset, iVar1, (unsigned char*)temp64DecmpBufferPt);
    }
    else if (cVar2 == '\x02') {
        uVar3 = get32bit_bits_FUN_0040b7f0(cmpDataOffset, iVar1, '\x18');
        param_3 = param_3 + 0x1a;
        FUN_00409f9d(param_1, cmpDataOffset, uVar3, temp64DecmpBufferPt, param_5);
        *param_5 = 0;
    }
    else {
        uVar3 = get32bit_bits_FUN_0040b7f0(cmpDataOffset, iVar1, '\b');
        uVar4 = get32bit_bits_FUN_0040b7f0(cmpDataOffset, param_3 + 10, '\x01');
        iVar1 = param_3 + 0xb;
        if (uVar4 != 0) {
            uVar4 = get32bit_bits_FUN_0040b7f0(cmpDataOffset, param_3 + 0xb, '\x10');
            *param_5 = uVar4;
            iVar1 = param_3 + 0x1b;
        }
        param_3 = iVar1;
        FUN_0040a0e9(temp64DecmpBufferPt, (char)uVar3);
    }
    return param_3;

}


int __cdecl FUN_0040a720(ushort* param_1, int param_2, int param_3, unsigned char* param_4)

{

    struct_40a720 header; 
    header.local_108 = header.local_104;
    header.iVar1 = FUN_0040aa1f(param_1, param_2, param_3, &header.local_108, header.local_10c);
    header.uVar2 = get16bit_bits_FUN_0040b8f0(param_2, header.iVar1, 6);
    header.iVar1 = FUN_0040ae49(param_2, header.iVar1 + 6, (char)((header.uVar2 & 0x38) >> 3) + 1, ((unsigned char)header.uVar2 & 7) + 1
        , header.local_10c[0] - 1, 0x40, param_4);
    header.local_114 = 0x40;
    do {
        *param_4 = *(unsigned char*)((uint)*param_4 + (int)header.local_108);
        param_4 = param_4 + 1;
        header.local_114 = header.local_114 + -1;
    } while (header.local_114 != 0);
    return header.iVar1;
}


int __cdecl FUN_0040aa1f(ushort* param_1, int param_2, int param_3, ushort** param_4, ushort* param_5)

{
    uint uVar1;

    if (*(char*)(param_1 + 0x81) == '\0') {
        *param_5 = *param_1;
        *param_4 = param_1 + 1;
    }
    else {
        uVar1 = get32bit_bits_FUN_0040b7f0(param_2, param_3, *(char*)(param_1 + 0x81));
        param_3 = param_3 + (uint) * (unsigned char*)(param_1 + 0x81);
        if ((char)uVar1 == '\0') {
            *param_5 = *param_1;
            *param_4 = param_1 + 1;
        }
        else if ((char)uVar1 == '\x01') {
            param_3 = FUN_0040a814((short*)param_1, param_2, param_3, (unsigned char*)*param_4,
                (short*)param_5);
        }
        else {
            param_3 = FUN_0040a8e6((short*)param_1, param_2, param_3, (unsigned char*)*param_4, param_5);
        }
    }
    return param_3;
}


int __cdecl FUN_0040a814(short* param_1, int param_2, int param_3, unsigned char* param_4, short* param_5)

{
    unsigned char bVar1;
    uint uVar2;
    uint uVar3;
    int iVar4;
    int local_14;
    int local_10;
    int local_c;
    int local_8;

    uVar2 = get32bit_bits_FUN_0040b7f0(param_2, param_3, '\x06');
    *param_5 = (short)uVar2;
    uVar2 = get32bit_bits_FUN_0040b7f0(param_2, param_3 + 6, '\x03');
    uVar3 = get32bit_bits_FUN_0040b7f0(param_2, param_3 + 9, '\x03');
    iVar4 = FUN_0040ab11(param_2, param_3 + 0xc, (char)uVar2 + 1, (char)uVar3 + 1, *param_1 + -1,
        *param_5, (unsigned char*)param_4);
    local_8 = (int)(param_1 + 1);
    local_10 = *param_5 + 1;
    do {
        bVar1 = *param_4;
        *param_4 = *(unsigned char*)(local_8 + (uint)bVar1);
        param_4 = param_4 + 1;
        local_8 = (int)((unsigned char*)(local_8 + (uint)bVar1) + 1);
        local_10 = local_10 + -1;
    } while (local_10 != 0);
    return iVar4;
}

int __cdecl
FUN_0040ab11(int param_1, int param_2, unsigned char param_3, unsigned char param_4, short param_5, short param_6,
    unsigned char* param_7)

{

    char cVar1;
    char cVar2;
    unsigned char bVar3;
    short sVar4;
    short sVar5;
    uint uVar6;
    uint uVar7;
    int iVar8;
    short local_20;
    char local_10;
    short local_c;
  
    sVar4 = (short)(1 << (param_3 & 0x1f));
    sVar5 = sVar4 >> 1;
    if (param_5 < sVar4) {
        param_2 = FUN_0040b890(param_1,param_2,param_3,param_6,param_7);
    }
    else {
        cVar1 = param_4 + param_3;
        bVar3 = cVar1 - 2;
        local_c = (short)(((int)param_5 - (int)sVar5) - (int)(short)((int)sVar5 << (param_4 & 0x1f)) >>
                            (bVar3 & 0x1f)) + 2;
        if (0x20 < local_c) {
            local_c = 0x20;
        }
        sVar4 = local_c + -1;
        local_20 = param_6;
        cVar2 = (char)sVar5;
        if (param_3 < 2) {
            do {
                uVar6 = get32bit_bits_FUN_0040b7f0(param_1,param_2,' ');
                uVar6 = FUN_0040b980(uVar6,(unsigned char)local_c);
                if ((unsigned char)uVar6 == 0) {
                    *param_7 = '\0';
                    param_2 = param_2 + 1;
                }
                else {
                    if ((short)(ushort)(unsigned char)uVar6 < local_c) {
                        local_10 = (char)((uVar6 & 0xff) - 1 << (param_4 - 1 & 0x1f)) + cVar2;
                        if (1 < param_4) {
                            uVar7 = get32bit_bits_FUN_0040b7f0(param_1,(uVar6 & 0xff) + param_2 + 1,param_4 - 1);
                            local_10 = (char)uVar7 + local_10;
                        }
                            iVar8 = (uint)param_4 + (uVar6 & 0xff);
                    }
                    else {
                        uVar6 = get32bit_bits_FUN_0040b7f0(param_1,local_c + param_2,cVar1 + -1);
                        local_10 = (char)uVar6 + (char)((int)sVar4 << (bVar3 & 0x1f)) + cVar2;
                        iVar8 = (uint)param_4 + (int)local_c;
                    }
                    param_2 = param_2 + iVar8;
                    *param_7 = local_10;
                }
                param_7 = param_7 + 1;
                local_20 = local_20 + -1;
            } while (local_20 != 0);
        }
        else {
            do {
                uVar6 = get32bit_bits_FUN_0040b7f0(param_1,param_2,' ');
                uVar6 = FUN_0040b980(uVar6,(unsigned char)local_c);
                if ((unsigned char)uVar6 == 0) {
                    uVar6 = get32bit_bits_FUN_0040b7f0(param_1,param_2 + 1,param_3 - 1);
                    *param_7 = (char)uVar6;
                    uVar6 = (uint)param_3;
                }
                else {
                    if ((short)(ushort)(unsigned char)uVar6 < local_c) {
                        local_10 = (char)((uVar6 & 0xff) - 1 << (bVar3 & 0x1f)) + cVar2;
                        if (2 < (uint)param_4 + (uint)param_3) {
                            uVar7 = get32bit_bits_FUN_0040b7f0(param_1,(uVar6 & 0xff) + param_2 + 1,bVar3);
                            local_10 = (char)uVar7 + local_10;
                        }
                        uVar6 = ((uint)param_4 + (uint)param_3 + (uVar6 & 0xff)) - 1;
                    }
                    else {
                        uVar6 = get32bit_bits_FUN_0040b7f0(param_1,local_c + param_2,cVar1 + -1);
                        local_10 = (char)uVar6 + (char)((int)sVar4 << (bVar3 & 0x1f)) + cVar2;
                        uVar6 = (uint)param_4 + (uint)param_3 + (int)sVar4;
                    }
                    *param_7 = local_10;
                }
                param_2 = param_2 + uVar6;
                param_7 = param_7 + 1;
                local_20 = local_20 + -1;
            } while (local_20 != 0);
        }
    }
    return param_2;
}

int __cdecl FUN_0040b890(int param_1, int param_2, unsigned char param_3, short param_4, unsigned char* param_5)

{
    int iVar1;

    do {
        iVar1 = get16bit_bits_FUN_0040b8f0(param_1, param_2, param_3);
        *param_5 = (char)iVar1;
        param_5 = param_5 + 1;
        param_2 = param_2 + (uint)param_3;
        param_4 = param_4 + -1;
    } while (param_4 != 0);
    return param_2;
}

int __cdecl get16bit_bits_FUN_0040b8f0(int param_1, int param_2, unsigned char param_3)

{
    /*
    int local_8;
    int local_c;

    local_8 = (param_2 >> 3) + param_1;
    local_c = (unsigned short)*(unsigned char*)local_8++;
    local_c = (unsigned short)(((local_c << 8) & 0xffff) + *(unsigned char*)local_8++);


    local_c = (unsigned short)(local_c << ((unsigned char)param_2 & 0x7));
    local_c = (unsigned short)(local_c >> (unsigned char)(0x10 - (unsigned char)param_3));
    return (unsigned char)local_c;*/

    unsigned char* pbVar1;
    unsigned char local_c;

    pbVar1 = (unsigned char*)((param_2 >> 3) + param_1);
    local_c = (unsigned char)
        ((ushort)((ushort)pbVar1[1] + (ushort)*pbVar1 * 0x100 << ((unsigned char)param_2 & 7)) >>
            ((unsigned char)(0x10 - (uint)param_3) & 0x1f));
    //return CONCAT31((int3)(0x10 - (uint)param_3 >> 8), local_c);
    
    return (((int)(0x10 - (uint)param_3 >> 8) << 8) | local_c);

}

int __cdecl FUN_0040b980(int param_1, unsigned char param_2)

{
    int local_8;

    local_8 = 0;
    for (; (local_8 < (int)(uint)param_2 && (-1 < param_1)); param_1 = param_1 << 1) {
        local_8 = local_8 + 1;
    }
    return local_8;
}




int __cdecl FUN_0040a8e6(short* param_1, int param_2, int param_3, unsigned char* param_4, ushort* param_5)

{
    uint uVar1;
    uint uVar2;
    int iVar3;
    int local_24;
    char local_20;
    int local_1c;
    int local_18;
    char local_14;
    int local_10;
    int local_c;
    char local_8;

    uVar1 = get32bit_bits_FUN_0040b7f0(param_2, param_3, '\x06');
    local_20 = (char)uVar1;
    uVar1 = get32bit_bits_FUN_0040b7f0(param_2, param_3 + 6, '\x03');
    uVar2 = get32bit_bits_FUN_0040b7f0(param_2, param_3 + 9, '\x03');
    iVar3 = FUN_0040ab11(param_2, param_3 + 0xc, (char)uVar1 + 1, (char)uVar2 + 1, *param_1 + -1,
        (ushort)(unsigned char)local_20, (unsigned char*)param_4);
    local_8 = *param_4;
    *param_4 = *(unsigned char*)((int)param_1 + (unsigned char)local_8 + 2);
    local_14 = '\x01';
    local_1c = (int)(param_4 + 1);
    local_24 = (int)(param_4 + 1);
    while ((char)(local_20 + -1) != '\0') {
        if (*(char*)local_24 == '\0') {
            local_24 = local_24 + 1;
            local_20 = local_20 + -2;
            local_8 = *(char*)local_24;
        }
        else {
            local_8 = *(char*)local_24 + local_8;
            local_20 = local_20 + -1;
        }
        *(char*)local_1c = *(char*)((int)param_1 + (unsigned char)local_8 + 2);
        local_24 = local_24 + 1;
        local_1c = local_1c + 1;
        local_14 = local_14 + '\x01';
    }
    *param_5 = (ushort)(unsigned char)local_14;
    return iVar3;
}



int __cdecl
FUN_0040ae49(int param_1, int param_2, unsigned char param_3, unsigned char param_4, short param_5, short param_6,
    unsigned char* param_7)

{
    short sVar1;
    ushort uVar2;
    ushort uVar3;
    uint uVar4;
    short local_24;
    short local_20;
    char local_1c;
    short local_18;
    short local_14;
    short local_10;
    short local_c;
    char local_8;

    sVar1 = (short)(1 << (param_3 & 0x1f));
    uVar2 = sVar1 - 1;
    uVar3 = (short)(1 << (param_4 & 0x1f)) - 1;
    if (param_5 < sVar1) {
        param_2 = FUN_0040b890(param_1, param_2, param_3, param_6, param_7);
    }
    else {
        local_14 = param_6;
        do {
            uVar4 = get32bit_bits_FUN_0040b7f0(param_1, param_2, param_3);
            local_8 = (char)uVar4;
            param_2 = param_2 + (uint)param_3;
            if ((unsigned char)local_8 == uVar2) {
                local_18 = param_5 - uVar2;
                do {
                    uVar4 = get32bit_bits_FUN_0040b7f0(param_1, param_2, param_4);
                    param_2 = param_2 + (uint)param_4;
                    local_8 = (unsigned char)uVar4 + local_8;
                    local_18 = local_18 - uVar3;
                    if ((unsigned char)uVar4 != uVar3) break;
                } while (0 < local_18);
            }
            *param_7 = local_8;
            param_7 = param_7 + 1;
            local_14 = local_14 + -1;
        } while (local_14 != 0);
    }
    return param_2;
}


int __cdecl FUN_0040a1cd(ushort* param_1, int param_2, int param_3, unsigned char* param_4)

{
    char cVar1;     // local_114 temp
    char cVar2;     // local_114 temp
    char cVar3;     // local_13c
    unsigned char bVar4;    // local_110
    unsigned char bVar5;    // local_114
    unsigned char bVar6;    // local_114
    unsigned char bVar7;    // local_148 
    short sVar8;    // local_13c
    short sVar9;    // local_128
    int iVar10;     // param_3
    uint uVar11;    // local_114
    uint uVar12;    // eax temp

    struct_40a1cd header;
    header.local_108 = header.local_104;
    iVar10 = FUN_0040aa1f(param_1, param_2, param_3, &header.local_108, header.local_10c);
    uVar11 = get16bit_bits_FUN_0040b8f0(param_2, iVar10, 6);
    cVar1 = (char)((uVar11 & 0x38) >> 3);
    bVar4 = cVar1 + 1;
    bVar5 = (unsigned char)uVar11 & 7;
    bVar6 = bVar5 + 1;
    param_3 = iVar10 + 6;
    header.local_138 = param_4;
    sVar9 = (short)(1 << bVar4);
    sVar8 = sVar9 >> 1;
    if ((short)(header.local_10c[0] - 1) < sVar9) {
        param_3 = FUN_0040b890(param_2, param_3, bVar4, 0x40, param_4);
        header.local_140 = 0x40;
        do {
            *header.local_138 = *(unsigned char*)((uint)*header.local_138 + (int)header.local_108);
            header.local_138 = header.local_138 + 1;
            header.local_140 = header.local_140 + -1;
        } while (header.local_140 != 0);
    }
    else {
        cVar2 = bVar6 + bVar4;
        bVar7 = cVar2 - 2;
        header.local_120 = (short)(((int)(short)(header.local_10c[0] - 1) - (int)sVar8) -
            (int)(short)((int)sVar8 << bVar6) >> (bVar7 & 0x1f)) + 2;
        if (0x20 < header.local_120) {
            header.local_120 = 0x20;
        }
        sVar9 = header.local_120 + -1;
        header.local_134 = 0x40;
        cVar3 = (char)sVar8;
        if (bVar4 < 2) {
            do {
                uVar11 = get32bit_bits_FUN_0040b7f0(param_2, param_3, ' ');
                uVar11 = FUN_0040b980(uVar11, (unsigned char)header.local_120);
                if ((unsigned char)uVar11 == 0) {
                    *header.local_138 = *(unsigned char*)header.local_108;
                    param_3 = param_3 + 1;
                }
                else {
                    if ((short)(ushort)(unsigned char)uVar11 < header.local_120) {
                        header.local_124 = (char)((uVar11 & 0xff) - 1 << bVar5) + cVar3;
                        if (1 < bVar6) {
                            uVar12 = get32bit_bits_FUN_0040b7f0(param_2, (uVar11 & 0xff) + param_3 + 1, bVar5);
                            header.local_124 = (char)uVar12 + header.local_124;
                        }
                        iVar10 = (uint)bVar6 + (uVar11 & 0xff);
                    }
                    else {
                        uVar11 = get32bit_bits_FUN_0040b7f0(param_2, header.local_120 + param_3, cVar2 + -1);
                        header.local_124 = (char)uVar11 + (char)((int)sVar9 << (bVar7 & 0x1f)) + cVar3;
                        iVar10 = (uint)bVar6 + (int)header.local_120;
                    }
                    param_3 = param_3 + iVar10;
                    *header.local_138 = *(unsigned char*)((uint)header.local_124 + (int)header.local_108);
                }
                header.local_138 = header.local_138 + 1;
                header.local_134 = header.local_134 + -1;
            } while (header.local_134 != 0);
        }
        else {
            do {
                uVar11 = get32bit_bits_FUN_0040b7f0(param_2, param_3, ' ');
                uVar11 = FUN_0040b980(uVar11, (unsigned char)header.local_120);
                if ((unsigned char)uVar11 == 0) {
                    uVar11 = get32bit_bits_FUN_0040b7f0(param_2, param_3 + 1, cVar1);
                    *header.local_138 = *(unsigned char*)((uVar11 & 0xff) + (int)header.local_108);
                    uVar11 = (uint)bVar4;
                }
                else {
                    if ((short)(ushort)(unsigned char)uVar11 < header.local_120) {
                        header.local_124 = (char)((uVar11 & 0xff) - 1 << (bVar7 & 0x1f)) + cVar3;
                        if (2 < (unsigned char)(bVar6 + bVar4)) {
                            uVar12 = get32bit_bits_FUN_0040b7f0(param_2, (uVar11 & 0xff) + param_3 + 1, bVar7);
                            header.local_124 = (char)uVar12 + header.local_124;
                        }
                        uVar11 = ((uint)bVar6 + (uint)bVar4 + (uVar11 & 0xff)) - 1;
                    }
                    else {
                        uVar11 = get32bit_bits_FUN_0040b7f0(param_2, header.local_120 + param_3, cVar2 + -1);
                        header.local_124 = (char)uVar11 + (char)((int)sVar9 << (bVar7 & 0x1f)) + cVar3;
                        uVar11 = (uint)bVar6 + (uint)bVar4 + (int)sVar9;
                    }
                    *header.local_138 = *(unsigned char*)((uint)header.local_124 + (int)header.local_108);
                }
                param_3 = param_3 + uVar11;
                header.local_138 = header.local_138 + 1;
                header.local_134 = header.local_134 + -1;
            } while (header.local_134 != 0);
        }
    }
    return param_3;
}


void __cdecl FUN_0040a0e9(int* param_1, unsigned char param_2)

{
    int iVar1;
    int local_c;
    int local_8;

    //iVar1 = *(int*)(&tempBuffer1024 + (uint)param_2 * 4);
    iVar1 = tempBuffer1024[param_2];
    *param_1 = iVar1;
    param_1[1] = iVar1;
    param_1[2] = iVar1;
    param_1[3] = iVar1;
    param_1[4] = iVar1;
    param_1[5] = iVar1;
    param_1[6] = iVar1;
    param_1[7] = iVar1;
    param_1[8] = iVar1;
    param_1[9] = iVar1;
    param_1[10] = iVar1;
    param_1[0xb] = iVar1;
    param_1[0xc] = iVar1;
    param_1[0xd] = iVar1;
    param_1[0xe] = iVar1;
    param_1[0xf] = iVar1;
    return;
}

void initTempBuffer1024_FUN_00409de0(void)

{
    int i;
    unsigned int local_8;

    for (i = 0; i < 0x100; i = i + 1) {
        local_8 = (i << 24) | ((i << 16)| ((i << 8) | i));
        //*(unsigned int*)(&tempBuffer1024 + i * 4) = local_8;
        tempBuffer1024[i] = local_8;
    }
    return;
}



short getStorageWidth(int width)
{
    return (short)width + 7U & 0xfff8;
}