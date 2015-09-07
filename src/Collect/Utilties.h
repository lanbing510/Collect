#pragma once

wchar_t* c2w(const char* str);
BOOL SaveBitmap(const BITMAP &bm, HDC hDC, HBITMAP hBitmap, LPCTSTR szFileName);
std::string GenerateFileName();
int  GetEncoderClsid(const   WCHAR*   format, CLSID*   pClsid);
void SaveJpg(Gdiplus::Bitmap* pImage, const WCHAR* pFileName);