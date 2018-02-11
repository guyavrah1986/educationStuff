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
