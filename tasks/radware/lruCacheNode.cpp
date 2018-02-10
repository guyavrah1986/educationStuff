#include <iostream>

#include "lruCacheNode.h"

using namespace std;

LruCacheNode::LruCacheNode(int key, int val)
	: m_key(key)
	, m_val(val)
{

}

LruCacheNode::~LruCacheNode()
{
	cout << "LruCacheNode::~LruCacheNode - deleting Node:<" << m_key << "," << m_val << ">" << endl;
}


