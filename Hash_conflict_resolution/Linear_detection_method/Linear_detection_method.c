/*************************************************************************
	> File Name: Linear_detection_method.cpp
	> Author: wk
	> Mail: 18402927708@163.com
	> Created Time: Thu 26 May 2016 11:07:02 PM CST
 ************************************************************************/


#include"Linear_detection_method.h"

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
	  while(hash->nodes[cur]->state == 1 && cur != hash->buckets)
	  {
	     cur =cur+1%hash->buckets;
	  }
	  if(cur == hash->buckets)
	  {
	   printf("table is full\n");
	   return ;
	  }
	  else
	  {
	    hash->nodes[cur]=node;
		hash->nodes[cur]->state = 1;
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
	  while(cur != hash->buckets && memcmp(key,hash->nodes[cur]->key,key_size) != 0)
	  {
	        cur = (cur+1)%hash->buckets;
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
