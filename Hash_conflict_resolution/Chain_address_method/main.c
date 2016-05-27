/*************************************************************************
	> File Name: main.c
	> Author: wk
	> Mail: 18402927708@163.com
	> Created Time: Fri 27 May 2016 02:09:19 PM CST
 ************************************************************************/

#include"chain_address_method.h"
 
//总共有n个节点桶的个数m个所以查找时间是n/m  O(1)
//链地址发的a=n/m 可以大于1 就会有很多在同一个桶中
//二次探测法要预留空间  a 不可以大于0.5

typedef struct  stu{
      char num[5];
	  char name[32];
	  int age;
}stu_t;

unsigned int hash_function(unsigned int buckets,void *key) //用num作为关键码(字符串)
{
   char *str= (char*)key;
   unsigned int index = 0;
   while(*str != '\0')
	{
      index = *str + 4*index;
	  str++;
    }
	return index % buckets;
}

unsigned int hash_function_1(unsigned int buckets,void *key)//用age作为关键码(整数)
{
   int dec= *(int*)key;

	return dec % buckets;
}



int main()
{
     stu_t stu_arr[]={
		 {"1","A",20},
		 {"2","B",21},
		 {"3","C",22}
	 };
  hash_t *hash=hash_alloc(256,hash_function);
  int size = sizeof(stu_arr)/sizeof(stu_arr[0]);
  /*用字符串作为关键码
  int i=0;
   for(;i<size;++i)
	{
        hash_add_entry(hash,stu_arr[i].num,strlen(stu_arr[i].num),&stu_arr[i],sizeof(stu_arr[i]));  
    }
	stu_t *s = (stu_t*)hash_lookuo_enty(hash,"1",1);
      if(s != NULL)
	 {
	  printf("%s   %s  %d\n",s->num,s->name,s->age);
	 }
	 else
	{
	 printf("not found\n");
	 }
     hash_free_entry(hash,"1",1);
	 s = (stu_t*)hash_lookuo_enty(hash,"1",1);
      if(s != NULL)
	 {
	  printf("%s   %s  %d\n",s->num,s->name,s->age);
	 }
	 else
	{
	 printf("not found\n");
	 }
*/
//用年龄作为关键码 (用整数作为关键码)
int i=0;
   for(;i<size;++i)
	{
        hash_add_entry(hash,&stu_arr[i].age,sizeof(stu_arr[i].age),&stu_arr[i],sizeof(stu_arr[i]));  
    }
	int key=20;
	stu_t *s = (stu_t*)hash_lookuo_enty(hash,&key,4);
      if(s != NULL)
	 {
	  printf("%s   %s  %d\n",s->num,s->name,s->age);
	 }
	 else
	{
	 printf("not found\n");
	 }
     hash_free_entry(hash,&key,4);
	 s = (stu_t*)hash_lookuo_enty(hash,&key,4);
      if(s != NULL)
	 {
	  printf("%s   %s  %d\n",s->num,s->name,s->age);
	 }
	 else
	{
	 printf("not found\n");
	 }

	 hash_dealloc(hash,256);
    return 0;
}

