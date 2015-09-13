// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� BUFFERDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// BUFFERDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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