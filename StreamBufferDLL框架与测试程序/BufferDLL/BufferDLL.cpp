// BufferDLL.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include "BufferDLL.h"


// 作用：初始化排序缓存
// 返回：初始化状态码（0 - 成功， 其他 - 错误代码（可以自己定义））
int initBuffer()
{
	List.clear();
	StreamOffSet = 0;
    return 0;
}

// 作用：排序缓存接受数据
// 参数： id - 节目id，在单节目情况下可以不考虑该参数
//        offset - 偏移量，发送给排序缓存的数据包的首字节在源文件中相对于源文件首字节的偏移量
//        bytes - 数据包长度，表示发送给排序缓存的数据包的长度，单位：字节
//        pData - 数据指针，指向数据包的首字节的数据指针
// 返回：成功接受到的字节数
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

// 作用：查询已经排好序的数据信息
// 参数： id - 节目id，在单节目情况下可以不考虑该参数
//        &iDataOffset - 引用参数，用于返回数据
//        &pData - 引用参数，用于返回数据
// 返回：已经排好序的数据长度
//        &iDataOffset - 排好序的数据的首字节在源文件中的偏移量
//        &pData - 排好序的首字节的指针
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

// 作用：排序缓存移除数据
// 参数： id - 节目id，在单节目情况下可以不考虑该参数
//        iBytes - 移除数据的长度，表示可以从缓存中移除已经排好序的数据的长度，单位：字节
// 返回：成功移除的字节数
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

// 作用：关闭排序缓存，释放空间
// 返回：关闭状态码（0 - 成功， 其他 - 错误代码（可以自己定义））
int closeBuffer()
{
    delete streamBuffer;
	return 0;
}


