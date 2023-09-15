#include <memory>
#include "Image.h"
#include <string.h>
#include <fstream>
#include <iostream>
void untile(char* pixel, char* outBuffer, int width, int height, int tile_w, int tile_h, int bpp)
{
    //bpp is bits per pixel
    //tile_w is tile width
    //tile_h is tile height
    int numTileW = width / tile_w;
    int numTileH = height / tile_h;
    int lineSize = tile_w * bpp / 8;
    int tileSize = tile_w * tile_h * bpp / 8;

    for (int y = 0; y < numTileH; y++)
    {
        for (int x = 0; x < numTileW; x++)
        {
            unsigned int dataPtr = y * numTileW * tileSize + tileSize * x;
            for (int ty = 0; ty < tile_h; ty++)
            {
                int curHeight = y * tile_h + ty;
                int curWidth = x * tile_w;
                int dstIndex = (curHeight * width + curWidth) * bpp / 8;
                int srcIndex = dataPtr + ty * lineSize;
                //memcpy(outBuffer + dstIndex, pixel + srcIndex, lineSize);
                memcpy_s(outBuffer + dstIndex, lineSize, pixel + srcIndex, lineSize);
            }
        }
    }
}
void crop(int width, int height, int storageWidth, int storageHeight, int bitsPerPixel, char* srcBuffer, char* dstBuffer)
{
    int srcLineSize = storageWidth * bitsPerPixel / 8;
    int dstLineSize = width * bitsPerPixel / 8;
    for (int y = 0; y < height; y++)
    {
        unsigned int srcPtr = y * srcLineSize;
        unsigned int dstPtr = y * dstLineSize;
        memcpy_s(dstBuffer + dstPtr, dstLineSize, (srcBuffer + srcPtr), dstLineSize);
    }
}
void saveTGA(char* tgaName, int width, int height, char* rgba32Buffer)
{
    TGAFILEHEADER tgaHdr{};
    memset((char*)&tgaHdr, 0, sizeof(TGAFILEHEADER));
    tgaHdr.ImageType = 2;
    tgaHdr.ISpecification.Width = width;
    tgaHdr.ISpecification.Height = height;
    tgaHdr.ISpecification.PixelDepth = 32;

    std::ofstream outTga(tgaName, std::ios::binary | std::ios::out);
    if (outTga.fail())
    {
        std::cout << "fail create: " << tgaName << std::endl;
    }
    //std::cout << tgaName << std::endl;
    std::cout << "Extracted... " << tgaName << std::endl;
    outTga.write((char*)&tgaHdr, sizeof(TGAFILEHEADER));
    outTga.write(rgba32Buffer, width * height * 4);
    outTga.close();
}
void decodeRawPal(char* pixel, char* palette, char* rgba32Buffer, int width, int height, int bpp, std::string palFormat)
{
    int lineSize = width * 4;
    if (bpp == 8)
    {
        for (int h = 0; h < height; h++)
        {
            unsigned int baseOffset = lineSize * (height - h - 1);
            for (int w = 0; w < width; w++)
            {
                unsigned char index = pixel[width * h + w];

                char* dstPtr = rgba32Buffer + baseOffset + w * 4;
                //char* dstPtr = rgba32Buffer + (width*h+w) * 4;
                ARGB8888 color{};

                color = decodePal(palFormat, palette, index);
                

                char* srcPtr = (char*)(&color);
                memcpy_s(dstPtr, 4, srcPtr, 4);

            }
        }
    }
}
ARGB8888 decodePal(std::string palFormat, char* palette, unsigned int index)
{
    ARGB8888 color{};
    if (palFormat == "R8G8B8A8")
    {
        color.R = *(char*)(palette + index * 4 + 2);
        color.G = *(char*)(palette + index * 4 + 1);
        color.B = *(char*)(palette + index * 4);
        color.A = *(char*)(palette + index * 4 + 3);
    }
    return color;
}

void decodeRaw(char* pixel, char* rgba32Buffer, int width, int height, int bpp, std::string pixelFormat)
{
    int lineSize = width * 4;
    for (int h = 0; h < height; h++)
    {
        unsigned int baseOffset = lineSize * (height - h - 1);
        for (int w = 0; w < width; w++)
        {
            unsigned int index = width * h + w;

            char* dstPtr = rgba32Buffer + baseOffset + w * 4;

            ARGB8888 color = decodePal(pixelFormat, pixel, index);

            char* srcPtr = (char*)(&color);
            memcpy_s(dstPtr, 4, srcPtr, 4);
        }
    }
}