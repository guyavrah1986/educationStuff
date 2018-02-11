#include <iostream>

#include "lruCache.h"

using namespace std;

LruCache::LruCache(size_t maxCapacity)
	: m_capacity(maxCapacity)
	, m_head(nullptr)
	, m_tail(nullptr)
	, m_keyToNodeMap()
{
	cout << "LruCache::LruCache - initializing cache with maximum capacity of:" << m_capacity << endl;
}

LruCache::~LruCache()
{
	cout << "LruCache::~LruCache" << endl;
}

bool LruCache::insertElement(int key, int val)
{
	if(m_keyToNodeMap.size() == m_capacity)
	{
		cout << "LruCache::::insertElement - cache has reached its max capacity, element will NOT be added" << endl;
		return false;
	}

	return true;	
}

// adds node to the end of the linked list
void LruCache::addNode(LruCacheNode* node)
{
	if (m_head == nullptr)
	{
		m_head = node;
		m_tail = node;
		node->m_next = m_tail;	
	}
	else
	{		
		m_tail->m_next = node;
		node->m_prev = m_tail;
		m_tail = m_tail->m_next;
	}		
}

int LruCache::Get(int key) const
{
	return true;
}

void LruCache::displayCache() const
{

}
