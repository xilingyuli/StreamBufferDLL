// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 BUFFERDLL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// BUFFERDLL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef BUFFERDLL_EXPORTS
#define BUFFERDLL_API extern "C" __declspec(dllexport)
#else
#define BUFFERDLL_API __declspec(dllimport)
#endif
#include "stdafx.h"

#define N 50000
#define INF 0

BUFFERDLL_API int initBuffer();
BUFFERDLL_API int receiveData(unsigned int id, unsigned int offset, unsigned int bytes, char *pData);
BUFFERDLL_API int containueBytes(unsigned int id, unsigned int &iDataOffset, char* &pData);
BUFFERDLL_API int removeData(unsigned int id, int iBytes);
BUFFERDLL_API int closeBuffer();

char *streamBuffer = new char[N];
list< pair<int, int> > List;

int StreamOffSet;