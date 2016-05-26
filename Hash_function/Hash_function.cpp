/*************************************************************************
	> File Name: hash_function.cpp
	> Author: wk
	> Mail: 18402927708@163.com
	> Created Time: Thu 26 May 2016 10:10:46 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

/*
散列表实在建立的时候将数据项的关键码和
数据项在表中的位置进行映射从而实现在查找的
过程中可不必进行关键码的比较就可以直接访问
数据项的一种数据结构

数据项所存储的表要用数组来实现
给定关键码经过散列函数计算得到的是关键码对应的数据项在数组中的存储下标

hash table  缺点：表空间不易扩展(数组比较)  优点：查找比较快不用进行关键码的比较
hash  map   缺点：链表内部存储要进行关键字的比较进行查找   优点：表空间容易扩展

散列函数选取的原则
简单:  散列函数的计算比较快捷  散列表的计算比关键码的比较快的多
均匀:  关键码的集合大小 远远大于表空间的大小所以将关键码映射到表空间中是一个压缩的过程
         容易出现将不同的关键码映射到同一个地址空间，这就是所谓的哈希冲突
哈希冲突解决方法：
链地址法
开地址法
建立公共溢出区

*/
#define BUCKETS 101
unsigned int SDBMHash(char *str)
{
    unsigned int hash = 0;
 
    while (*str)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// RS Hash Function
unsigned int RSHash(char *str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
 
    while (*str)
    {
        hash = hash * a + (*str++);
        a *= b;
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// JS Hash Function
unsigned int JSHash(char *str)
{
    unsigned int hash = 1315423911;
 
    while (*str)
    {
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// P. J. Weinberger Hash Function
unsigned int PJWHash(char *str)
{
    unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters    = (unsigned int)((BitsInUnignedInt  * 3) / 4);
    unsigned int OneEighth        = (unsigned int)(BitsInUnignedInt / 8);
    unsigned int HighBits         = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
    unsigned int hash             = 0;
    unsigned int test             = 0;
 
    while (*str)
    {
        hash = (hash << OneEighth) + (*str++);
        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// ELF Hash Function
unsigned int ELFHash(char *str)
{
    unsigned int hash = 0;
    unsigned int x    = 0;
 
    while (*str)
    {
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// BKDR Hash Function
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
 
    while (*str)
    {
        hash = hash * seed + (*str++);
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// DJB Hash Function
unsigned int DJBHash(char *str)
{
    unsigned int hash = 5381;
 
    while (*str)
    {
        hash += (hash << 5) + (*str++);
    }
 
    return (hash & 0x7FFFFFFF);
}
 
// AP Hash Function
unsigned int APHash(char *str)
{
    unsigned int hash = 0;
    int i;
 
    for (i=0; *str; i++)
    {
        if ((i & 1) == 0)
        {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }
 
    return (hash & 0x7FFFFFFF);
}

 //编程珠玑中的一个hash函数

//用跟元素个数最接近的质数作为散列表的大小
#define NHASH 29989
#define MULT 31

unsigned in hash(char *p)
{
    unsigned int h = 0;
    for (; *p != '\0'; p++)
        h = MULT *h + *p;
    return h % NHASH;
}
unsigned int SDBMHash(const char *str)
{
    unsigned int hash = 0;
	while(*str != '\0')
	{
	 hash = (*str++) + (hash<<6) *(hash<<16)-hash;
	}
	return (hash & 0x7FFFFFF)%BUCKETS;
}

int main()
{
  const char * keywords[]=
	{
    "auto","double","int","struct", "break","else", "long", "switch","case",
	"enum", "register", "typedef", "char", "extern","return","union","const", 
	"float","short", "unsigned", "continue", "for", "signed", "void",
    "default", "goto", "sizeof", "volatile", "do", "if", "while","static"
  };

   //哈希表每个地址的映射次数 eg: 0地址的映射次数用count[0]表示...
  int count[BUCKETS];
    int i=0;
  for(i=0;i<BUCKETS;++i) //初始化
	{
     count[i] = 0;
    }

    int sizeofarray = sizeof(keywords)/sizeof(keywords[0]);
     for(i=0;i<sizeofarray;++i)
	 {
	   unsigned int pos= SDBMHash(keywords[i]);
	   count[pos]++;
	 }
  
     for(i=0;i<sizeofarray;++i)
	 {
	   unsigned int tmppos= SDBMHash(keywords[i]);
	  cout<<keywords[i]<<"->"<<tmppos<<"  "<<count[tmppos]<<" times\n";
	 }
    return 0;
}

