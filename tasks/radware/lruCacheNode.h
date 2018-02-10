#pragma once

class LruCacheNode
{
	public:
	LruCacheNode(int key, int val);
	~LruCacheNode();
	

	LruCacheNode* m_prev;
	LruCacheNode* m_next;
	int m_key;
	int m_val;	
};
