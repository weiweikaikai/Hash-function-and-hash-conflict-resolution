/*************************************************************************
	> File Name: two_detection_methods.cpp
	> Author: wk
	> Mail: 18402927708@163.com
	> Created Time: Thu 26 May 2016 11:07:02 PM CST
 ************************************************************************/


#include"two_detection_methods.h"

//链表节点
struct hash_node
{
    int state;//节点状态 1表示使用  0表示删除
	void *key;
	void *value;
};

//哈希表
struct hash
{
	unsigned int buckets; //桶的个数
	unsigned int size;//装有数据的个数
    hashfunc_t hash_func; //哈希函数
	hash_node_t **nodes;  //链表中节点的地址
};


//创建哈希表
hash_t * hash_alloc(unsigned int buckets,hashfunc_t hash_func)
{
    hash_t *hash = (hash_t*)malloc(sizeof(hash_t));
	hash->buckets = buckets;
	hash->hash_func = hash_func;

	int size = buckets * sizeof(hash_node_t*);
	hash->nodes= (hash_node_t**)malloc(size);
	memset(hash->nodes,0,size);
	return hash;
}
//在哈希表中查找
void* hash_lookuo_enty(hash_t *hash,void *key,unsigned int key_size)
{
     hash_node_t *node=hash_get_node_by_key(hash,key,key_size);
	 if(node == NULL)
	 {
	   return NULL;
	 }
	 return node->value;
}
static is_primer(unsigned int value)
{
	    int i=3;
       for(;i<value/2;++i)
	    {
	         if(i%value == 0)
			{
			 return 0;
			 }
	   }
	   return 1;
}

static int next_primer(unsigned int value) //求下一个质数
{
     if(value %2 == 0)
	   {
	     value++;
	   }
	   for(;is_primer(value)!=1;value+=2)
		   return value;
}
//往哈希表中添加一项
void hash_add_entry(hash_t *hash,void *key,unsigned int key_size,void *value,unsigned int value_size)
{
     if(hash_lookuo_enty(hash,key,key_size) != NULL) //key是否存在
	  {
	    printf("hash key exist\n");
		 return;
	  }
	  hash_node_t *node = malloc(sizeof(hash_node_t));
	  node->key = malloc(key_size);
	  memcpy(node->key,key,key_size);
	  node->value=malloc(value_size);
	  memcpy(node->value,value,value_size);

	  unsigned int bucket_num=hash_get_bucket(hash,key);
       unsigned int cur =bucket_num;
	   int i=0;
	  while(hash->nodes[cur]->state == 1 && cur != hash->buckets)
	  {
	      if(cur %2 != 0) //奇数
		    {
			  cur += 2*(i-1);
			     while(cur > hash->buckets)
		        {
			      cur -= hash->buckets;
			    }
			}
			else //偶数
		    { 
			  cur -= 2*(i-1);
			    while(cur < 0)
		       {
			       cur += hash->buckets;
			   }
			}
			while(cur > hash->buckets)
		    {
			  cur -= hash->buckets;
			}
			++i;
	  }

      /*
	  可以证明当表的长度buckets为质数的时候且表的装填因子不超过0.5的时候
	  新的表项 x一定能够插入而且任何一个位置不会被探测两次
	  因此只要表中至少有一半空的，就不会有表满的问题
	  如果装填因子大于0.5就将原来表的长度扩充一倍 进行表的分裂
	  */
	  if(cur == hash->buckets)
	  {
	   printf("table is full\n");
	   return ;
	  }
	  else
	  {
	    hash->nodes[cur]=node;
		hash->nodes[cur]->state = 1;
	   if(++hash->size < hash->buckets /2)
		   return ;
	   else
		  {
	      unsigned int old_buckets = hash->buckets;
           hash->buckets = next_primer(2 * old_buckets); //最好是一个质数
	        //将原来表中的内容重新插入新分配的表中
			//之后将原来表空间释放
	     }
	
	  }

}
//从哈希表中删除一项
void hash_free_entry(hash_t *hash,void *key,unsigned int key_size)
{
      hash_node_t *node=hash_get_node_by_key(hash,key,key_size);
	 if(node == NULL)
	 {
	   return ;
	 }
	 free(node);
	 node =NULL;
}
//获取桶地址
unsigned int  hash_get_bucket(hash_t *hash,void *key)
{
	   //找到桶号
     unsigned int numofbucket = hash->hash_func(hash->buckets,key);
	 if(numofbucket >= hash->buckets)//大于桶的个数就出错了
	  {
	     printf("bad bucket lookup\n");
		 exit(0);
	  }
   //桶中找链表头节点的地址
   return numofbucket;
}
//根据key获取哈希表中的一个节点
hash_node_t *hash_get_node_by_key(hash_t *hash,void *key,unsigned int key_size)
{
      unsigned int  bucket_num=hash_get_bucket(hash,key);
      unsigned int cur = bucket_num;
	  int i =0;
	  while(cur != hash->buckets && memcmp(key,hash->nodes[cur]->key,key_size) != 0)
	  {
	        if(cur %2 != 0) //奇数
		    {
			  cur += 2*(i-1);
			   while(cur > hash->buckets)
		        {
			      cur -= hash->buckets;
			    }
			}
			else //偶数
		    { 
			  cur -= 2*(i-1);
			  while(cur < 0)
		       {
			       cur += hash->buckets;
			   }
			}
		
			++i;
	  }
	  if(cur == hash->buckets)
	  {
	   printf("not found\n");
	   	return NULL;
	  }
	  else
	   {
	    return hash->nodes[cur];
	   }

}

void hash_dealloc(hash_t *hash,unsigned int buckets)
{
	if(hash != NULL)
	{
		free(hash->nodes);
		hash=NULL;
	}
}
