#pragma once

#include <unordered_map>

#include "lruCacheNode.h"

class LruCache
{
	public:
	LruCache(size_t maxCapacity);
	~LruCache();

	bool insertElement(int key, int val);
	bool getElement(int key) const;

	// utilities
	void addNode(LruCacheNode* node);
	void displayCache() const;

	size_t m_capacity;
	LruCacheNode* m_head;
	LruCacheNode* m_tail;
	std::unordered_map<int, LruCacheNode*> m_keyToNodeMap;
};
