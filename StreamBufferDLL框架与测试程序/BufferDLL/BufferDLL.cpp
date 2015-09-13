// BufferDLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include "stdafx.h"
#include "BufferDLL.h"


// ���ã���ʼ�����򻺴�
// ���أ���ʼ��״̬�루0 - �ɹ��� ���� - ������루�����Լ����壩��
int initBuffer()
{
	List.clear();
	StreamOffSet = 0;
    return 0;
}

// ���ã����򻺴��������
// ������ id - ��Ŀid���ڵ���Ŀ����¿��Բ����Ǹò���
//        offset - ƫ���������͸����򻺴�����ݰ������ֽ���Դ�ļ��������Դ�ļ����ֽڵ�ƫ����
//        bytes - ���ݰ����ȣ���ʾ���͸����򻺴�����ݰ��ĳ��ȣ���λ���ֽ�
//        pData - ����ָ�룬ָ�����ݰ������ֽڵ�����ָ��
// ���أ��ɹ����ܵ����ֽ���
int receiveData(unsigned int id, unsigned int offset, unsigned int bytes, char *pData)
{
    int startPosition = offset-StreamOffSet;
    int endPosition = startPosition+bytes;
	if (startPosition >= N || endPosition <= 0)
		return bytes;
    if(startPosition<0)
        startPosition = 0;
	if(endPosition>N)
        endPosition = N;
    memcpy(streamBuffer+startPosition,pData,endPosition-startPosition);
	List.push_back(make_pair(startPosition, endPosition));
	return bytes;
}

// ���ã���ѯ�Ѿ��ź����������Ϣ
// ������ id - ��Ŀid���ڵ���Ŀ����¿��Բ����Ǹò���
//        &iDataOffset - ���ò��������ڷ�������
//        &pData - ���ò��������ڷ�������
// ���أ��Ѿ��ź�������ݳ���
//        &iDataOffset - �ź�������ݵ����ֽ���Դ�ļ��е�ƫ����
//        &pData - �ź�������ֽڵ�ָ��
int containueBytes(unsigned int id, unsigned int &iDataOffset, char* &pData)
{
	List.sort();
	for (list< pair<int, int> >::iterator it1 = List.begin();;)
	{
		list< pair<int, int> >::iterator it2 = it1++;
		if (it1 == List.end())
			break;
		if ((*it2).second >= (*it1).first)
		{
			(*it1).first = (*it2).first;
			if ((*it2).second>(*it1).second)
				(*it1).second = (*it2).second;
			List.erase(it2);
		}
		else
			break;
	}
	iDataOffset = StreamOffSet + (*List.begin()).first;
	pData = &streamBuffer[(*List.begin()).first];
	return (*List.begin()).second - (*List.begin()).first;
}

// ���ã����򻺴��Ƴ�����
// ������ id - ��Ŀid���ڵ���Ŀ����¿��Բ����Ǹò���
//        iBytes - �Ƴ����ݵĳ��ȣ���ʾ���Դӻ������Ƴ��Ѿ��ź�������ݵĳ��ȣ���λ���ֽ�
// ���أ��ɹ��Ƴ����ֽ���
int removeData(unsigned int id, int iBytes)
{
    StreamOffSet += iBytes;
	memcpy(streamBuffer, streamBuffer + iBytes, N - iBytes);
	List.sort();
	for (list< pair<int, int> >::iterator it = List.begin();it!=List.end();)
	{
		(*it).first -= iBytes;
		(*it).second -= iBytes;
		if ((*it).second<=0)
		{
			List.erase(it++);
		}
		else if ((*it).first<0)
		{
			(*it).first = 0;
			it++;
		}
		else
		{
			it++;
		}
	}
	return iBytes;
}

// ���ã��ر����򻺴棬�ͷſռ�
// ���أ��ر�״̬�루0 - �ɹ��� ���� - ������루�����Լ����壩��
int closeBuffer()
{
    delete streamBuffer;
	return 0;
}


