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

void LruCache::removeNode(LruCacheNode* node)
{
	if (m_head == node)
	{
		m_head = m_head->m_next;
		if (m_head != nullptr)
		{
			m_head->m_prev = nullptr;
		}
	}
	else if (m_tail == node)
	{
		m_tail = m_tail->m_prev;
		m_tail->m_next = nullptr;
	}
	else
	{	
		node->m_prev->m_next = node->m_next;
		node->m_next->m_prev = node->m_prev;
	}
}

void LruCache::moveNode(LruCacheNode* node)
{
	if (m_tail == node)
	{
        	return;
        }
	else if (m_head == node)
	{
        	node->m_next->m_prev = nullptr;
                m_head = node->m_next;
                m_tail->m_next = node;
                node->m_prev = m_tail;
                m_tail = m_tail->m_next;
        }
	else
	{
                node->m_prev->m_next = node->m_next;
                node->m_next->m_prev = node->m_prev;
                m_tail->m_next = node;
                node->m_prev = m_tail;
                m_tail = m_tail->m_next;
        }      
}

int LruCache::Get(int key)
{
	if (m_keyToNodeMap.find(key) == m_keyToNodeMap.end())
	{
            return -1;
        }
	else
	{
            LruCacheNode* tmp = m_keyToNodeMap[key];
            moveNode(tmp);
            return m_keyToNodeMap[key]->m_val;
        }
}

void LruCache::Set(int key, int value)
{
	if (m_keyToNodeMap.find(key) != m_keyToNodeMap.end())
	{
            moveNode(m_keyToNodeMap[key]);
            m_keyToNodeMap[key]->m_val = value;
        }
	else
	{
            	if (m_keyToNodeMap.size() == m_capacity)
		{
                	m_keyToNodeMap.erase(m_head->m_key);
                	removeNode(m_head);
            	}

            	LruCacheNode* node = new LruCacheNode(key,value);
            	m_keyToNodeMap[key] = node;
            	addNode(node);
        }
}

void LruCache::displayCache() const
{

}
