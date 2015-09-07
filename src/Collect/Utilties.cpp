#include "stdafx.h"
#include "Utilties.h"
#include <fstream>
using namespace std;

wchar_t* c2w(const char* str)
{
	if (str == NULL)
	{
		return L"";
	}

	int length = strlen(str) + 1;
	wchar_t *t = (wchar_t*)malloc(sizeof(wchar_t)*length);
	memset(t, 0, length*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str), t, length);
	return t;
}


BOOL SaveBitmap(const BITMAP &bm, HDC hDC, HBITMAP hBitmap, LPCTSTR szFileName)
{

	int nBitPerPixel = bm.bmBitsPixel;//获得颜色模式
	int nW = bm.bmWidth;
	int nH = bm.bmHeight;
	int nPalItemC = bm.bmPlanes;	//调色板项的个数
	int nBmpInfSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*nPalItemC;//位图信息的大小
	int nDataSize = (nBitPerPixel*nW + 31) / 32 * 4 * nH;//位图数据的大小
	//初始化位图信息
	BITMAPFILEHEADER bfh = { 0 };//位图文件头
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER)+nBmpInfSize;//sizeof(BITMAPINFOHEADER);//到位图数据的偏移量
	bfh.bfSize = bfh.bfOffBits + nDataSize;//文件总的大小
	bfh.bfType = (WORD)0x4d42;//位图标志
	char * p = new char[nBmpInfSize + nDataSize];//申请内存位图数据空间(包括信息头)
	memset(p, 0, nBmpInfSize);//将信息头的数据初始化为0
	LPBITMAPINFOHEADER pBih = (LPBITMAPINFOHEADER)p;//位图信息头
	pBih->biCompression = BI_RGB;
	pBih->biBitCount = nBitPerPixel;//每个图元像素使用的位数
	pBih->biHeight = nH;//高度
	pBih->biWidth = nW;//宽度
	pBih->biPlanes = 1;
	pBih->biSize = sizeof(BITMAPINFOHEADER);
	pBih->biSizeImage = nDataSize;//图像数据大小
	char *pData = p + nBmpInfSize;
	//DDB转换为DIB
	::GetDIBits(hDC, hBitmap, 0, nH, pData, (LPBITMAPINFO)pBih, DIB_RGB_COLORS);//获取位图数据
	ofstream ofs(szFileName, ios::binary);
	if (ofs.fail())
		return FALSE;
	ofs.write((const char*)&bfh, sizeof(BITMAPFILEHEADER));//写入位图文件头
	ofs.write((const char*)pBih, nBmpInfSize);//写入位图信息数据
	ofs.write((const char*)pData, nDataSize);//写入位图数据
	return TRUE;
}


std::string GenerateFileName()
{
	std::string szRet = "";
	char timeBuffer[30];
	time_t nowtime = time(NULL);
	tm timeTemp;
	localtime_s(&timeTemp, &nowtime);
	sprintf_s(timeBuffer, "%04d-%02d-%02d_%02d-%02d-%02d", timeTemp.tm_year + 1900, timeTemp.tm_mon + 1,
		timeTemp.tm_mday, timeTemp.tm_hour, timeTemp.tm_min, timeTemp.tm_sec);
	szRet = timeBuffer;
	return szRet;
}


int  GetEncoderClsid(const   WCHAR*   format, CLSID*   pClsid)
{
	using namespace Gdiplus;

	UINT num = 0;                     // number of image encoders   
	UINT size = 0;                   // size of the image encoder array in bytes   

	ImageCodecInfo*   pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;
		 
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return   -1;     // Failure   

	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return   j;     // Success   
		}
	}
	free(pImageCodecInfo);
	return   -1;     // Failure   
}


void SaveJpg(Gdiplus::Bitmap* pImage, const WCHAR* pFileName)
{
	using namespace Gdiplus;
	EncoderParameters encoderParameters;
	CLSID jpgClsid;
	GetEncoderClsid(L"image/jpeg", &jpgClsid);
	encoderParameters.Count = 1;
	encoderParameters.Parameter[0].Guid = EncoderQuality;
	encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
	encoderParameters.Parameter[0].NumberOfValues = 1;

	// Save the image as a JPEG with quality level 100.
	ULONG             quality;
	quality = 100;
	encoderParameters.Parameter[0].Value = &quality;
	
	Status status = pImage->Save(pFileName, &jpgClsid, &encoderParameters);
	if (status != Ok)
	{
		wprintf(L"%d  Attempt to save %s failed.\n", status, pFileName);
	}
}