#pragma once
#include <string>

#pragma  pack(push,1)
typedef struct {
	unsigned short   FirstIndexEntry;
	unsigned short   ColorMapLength;
	unsigned char  ColorMapEntrySize;
}COLORMAPSPECIFICATION;


typedef struct {
	unsigned short   XOrigin;
	unsigned short   YOrigin;
	unsigned short   Width;
	unsigned short   Height;
	unsigned char  PixelDepth;
	unsigned char  ImageDescriptor;
}IMAGESPECIFICATION;


typedef struct {
	unsigned char  IDLength;
	unsigned char  ColorMapType;
	unsigned char  ImageType;
	COLORMAPSPECIFICATION CMSpecification;
	IMAGESPECIFICATION ISpecification;
}TGAFILEHEADER;

typedef struct {
	unsigned char B;
	unsigned char G;
	unsigned char R;
	unsigned char A;
}ARGB8888;

#pragma  pack(pop)

void untile(char* pixel, char* outBuffer, int width, int height, int tile_w, int tile_h, int bpp);
void crop(int width, int height, int storageWidth, int storageHeight, int bitsPerPixel, char* srcBuffer, char* dstBuffer);
void saveTGA(char* tgaName, int width, int height, char* rgba32Buffer);
void decodeRawPal(char* pixel, char* palette, char* rgba32Buffer, int width, int height, int bpp, std::string palFormat);
ARGB8888 decodePal(std::string palFormat, char* palette, unsigned int index);
void decodeRaw(char* pixel, char* rgba32Buffer, int width, int height, int bpp, std::string pixelFormat);