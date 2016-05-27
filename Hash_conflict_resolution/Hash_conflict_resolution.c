/*************************************************************************
	> File Name: Hash_conflict_resolution.cpp
	> Author: wk
	> Mail: 18402927708@163.com
	> Created Time: Thu 26 May 2016 11:07:02 PM CST
 ************************************************************************/


#include"Hash_conflict_resolution.h"

//链表节点
struct hash_node
{
	void *key;
	void *value;
	struct hash_node *prev; //双向链表
	struct hash_node *next;
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
     if(hash_lookuo_enty(hash,key,key_size) != NULL)
	  {
	    printf("hash key exist\n");
		 return;
	  }
	  hash_node_t *node = malloc(sizeof(hash_node_t));
	  node->key = malloc(key_size);
	  memcpy(node->key,key,key_size);
	  node->value=malloc(value_size);
	  memcpy(node->value,value,value_size);

	  hash_node_t **bucketaddress=hash_get_bucket(hash,key);
	  if(*bucketaddress == NULL)
	  {
	     *bucketaddress = node;
	  }
	  else
	  {
	   //将新节点插入 头插
	    node->next = *bucketaddress;
        (*bucketaddress)->prev=node;
		(*bucketaddress)=node;
	    node->prev=NULL; 
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
	 hash_node_t **bucketaddress=hash_get_bucket(hash,key);
	 if(node->prev == NULL && node->next != NULL) //头删
	 {
	      (*bucketaddress)=node->next;
	      node->next->prev =NULL;
	 }
	 else if(node->prev!= NULL && node->next == NULL)//尾删
	 {
	    node->prev->next=NULL;
	 }
	 else if(node->prev== NULL && node->next == NULL)
	 {
	     (*bucketaddress)=NULL;
	 }
	 else //中间删除
	 {
	   node->prev->next = node->next;
	   node->next->prev = node->prev;
	 }
	 free(node);
	 node=NULL;
}
//获取桶地址
hash_node_t ** hash_get_bucket(hash_t *hash,void *key)
{
	   //找到桶号
     unsigned int numofbucket = hash->hash_func(hash->buckets,key);
	 if(numofbucket >= hash->buckets)//大于桶的个数就出错了
	  {
	     printf("bad bucket lookup\n");
		 exit(0);
	  }
   //桶中找链表头节点的地址
   return &(hash->nodes[numofbucket]);
}
//根据key获取哈希表中的一个节点
hash_node_t *hash_get_node_by_key(hash_t *hash,void *key,unsigned int key_size)
{
      hash_node_t**  bucket_address=hash_get_bucket(hash,key);
	  if((*bucket_address)==NULL)//链表头指针为空
         {
		    return NULL;
		 }
         //链表中遍历查找
        hash_node_t*cur = *bucket_address;
		while(cur != NULL && memcmp(key,cur->key,key_size)!=0)
	        {
		        cur=cur->next;
		    }
			if(cur != NULL)
	        {
			  return cur;
			}
		return NULL;
}

void hash_dealloc(hash_t *hash,unsigned int buckets)
{
	if(hash != NULL)
	{
		int i=0;
	  for(;i<buckets;++i)
		{
	        if(hash->nodes[i] != NULL)
		    {
			   hash_node_t *cur = hash->nodes[i];

			   while(cur!= NULL)
				{
				   free(cur);
			      cur=cur->next;
			     }
			}
	    }
		free(hash);
		hash=NULL;
	}
}
