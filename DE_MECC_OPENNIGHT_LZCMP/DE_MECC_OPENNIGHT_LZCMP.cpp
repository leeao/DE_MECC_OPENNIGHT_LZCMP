// DE_MECC_OPENNIGHT_LZCMP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include "string"
#include "cbmp.h"
#include "DE_LZCMP.h"
#include "Image.h"
#include "Path.h"

using namespace std;
int main(int argc, char* argv[])
{
    string exePath = GetExePath();
    ifstream palFile(exePath + "\\color.palette", ios::in);
    char* pal = new char[1024];
    int havePal = 0;
    if (palFile.fail())
    {
        //std::cout << "Can't found color.palette file!\n" << endl;
    }
    
    if (palFile.is_open())
    {
        havePal = 1;
        palFile.read(pal, 1024);
        palFile.close();
        for (int i = 0; i < 256; i++)
        {
            pal[i * 4 + 3] = (unsigned char)255;
        }
    }
    int count = argc;
    string help = "MECC OpenNight 1995 .cbmp image Decompress Tools\n by Allen\n";
    if (count == 1)
    {
        cout << help << endl;
    }
    
    for (int i = 1; i < count; i++)
    {
        //string fname = "D:\\下载\\Mecc CBMP Examples\\10.CBMP";
        string fname = argv[i];
        string outName;
        string ext = "";
        cout << "Decompressing... " << fname << endl;
        ifstream fin(fname, ios::in | ios::binary);


        if (fin.fail())
        {
            cout << "fail oepn:" << fname << endl;
            continue;
        }
        if (fname.rfind('.') != -1)
        {
            ext = fname.substr(fname.rfind('.')).c_str();   //获取后缀名 ".cbmp"
            transform(ext.begin(), ext.end(), ext.begin(), tolower);
            outName = fname.substr(0, fname.rfind('.'));    //获取文件路径+文件名不带扩展名 path/filename
            //outName = outName + ".dbmp";

            if (ext == ".cbmp")
            {
                char temp[2];
                short numTex;
                fin.read((char*)&temp, 2);
                numTex = *(short*)&temp;
                int texHeaderDataSize = sizeof(CBMPTexHeader) * numTex;
                char* texHeaderData = new char[texHeaderDataSize];
                fin.read(texHeaderData, texHeaderDataSize);
                for (int j = 0; j < numTex; j++)
                {
                    CBMPTexHeader texHeader = *(CBMPTexHeader*)(texHeaderData + sizeof(CBMPTexHeader) * j);
                    short storageWidth = getStorageWidth(texHeader.width);
                    short storageHeight = getStorageWidth(texHeader.height);
                    fin.seekg(texHeader.offset, ios::beg);
                    char* data = new char[texHeader.dataSize];
                    fin.read(data, texHeader.dataSize);
                    

                    CBMPDataHeader dataHeader = *(CBMPDataHeader*)data;
                    int storageSize = storageWidth * storageHeight;
                    char* decmpBuffer = new char[storageSize] {0};

                    initTempBuffer1024_FUN_00409de0();
                    FUN_00409e4a((short*)data, (uint)decmpBuffer);


                    char* untileBuffer = new char[storageSize] {0};
                    untile(decmpBuffer, untileBuffer, storageWidth, storageHeight, 8, storageHeight, 8);
                    int cropSize = texHeader.width * texHeader.height;
                    char* cropBuffer = new char[cropSize] {0};
                    crop(texHeader.width, texHeader.height, storageWidth, storageHeight, 8, untileBuffer, cropBuffer);
                    char logName[512];
                    /*                    
                    if (numTex == 1)
                    {
                        sprintf_s(logName, "%s.dbmp", outName.c_str());
                    }
                    else
                    {
                        sprintf_s(logName, "%s_%d.dbmp", outName.c_str(), j);
                    }


                    ofstream fout(logName, ios::out | ios::binary);                    
                    fout.write(cropBuffer, cropSize);
                    fout.close();

                    if (numTex == 1)
                    {
                        sprintf_s(logName, "%s_tiled.dbmp", outName.c_str());
                    }
                    else
                    {
                        sprintf_s(logName, "%s_%d_tiled.dbmp", outName.c_str(), j);
                    }
                    ofstream fout2(logName, ios::out | ios::binary);
                    fout2.write(decmpBuffer, dataHeader.decompressSize);
                    fout2.close();

                    */

                    if (havePal)
                    {
                        char* rgba32Buffer = new char[texHeader.width * texHeader.height * 4];
                        decodeRawPal(cropBuffer, pal, rgba32Buffer, texHeader.width, texHeader.height, 8, "R8G8B8A8");
                        if (numTex == 1)
                        {
                            sprintf_s(logName, "%s.tga", outName.c_str());
                        }
                        else
                        {
                            sprintf_s(logName, "%s_%d.tga", outName.c_str(), j);
                        }
                        saveTGA(logName, texHeader.width, texHeader.height, rgba32Buffer);

                    }
                }
                fin.close();


            }
        }


    }
 

}

