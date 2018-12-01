// ========================================================================================================
// 1) The function above inserts an item (of type int) into a list - make sure you understand how.
// 2) Givne this function implement another function that gets a node (anywhere in the linked list) and 
//    adds an item after that node
// ========================================================================================================

// 1)
void** insertFirst(void** head, int item)
{
	void** p = (void**)malloc(sizeof(void*) + sizeof(int));
	*p = head;
	*(int*)(p + 1) = item;
	
	return p;
}


// 2) 
void foo(void** node, int item)
{
	// TODO: 
}

