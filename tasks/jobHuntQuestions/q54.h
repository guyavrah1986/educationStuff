#include <stdio.h>

typedef struct 
{
	void (*func)(void);
	size_t sec;
	struct entry* next;
	size_t funcNum;	// for debug
}entry;

entry* head = NULL;

void func1()
{
	printf("func1 \n");
}

void func2()
{
	printf("func2 \n");
}

void func3()
{
	printf("func3 \n");
}

void func4()
{
	printf("func4 \n");
}

// =================================================================================================================================================================
// Interface functions implementation:
// -----------------------------------

void CreateTimer(void (*func)(void), size_t seconds, size_t funcNum)
{
	entry* e = (entry*)malloc(sizeof(entry));
	e->func = func;
	e->sec = seconds;
	e->next = NULL;
	e->funcNum = funcNum;
	insertEntry(e);
}

void StartTimers()
{

}

// =================================================================================================================================================================
// Utilities functions :
// --------------------

void insertEntry(entry* e)
{
	printf("insertEntry - got entry with function address:%p , and seconds:%lu \n",e->func, e->sec);
	entry* curr = head;
	
	// empty list 
	if (curr == NULL)
	{
		printf("insertEntry - entering the first entry (head == NULL) \n");
		head = e;
		return;
	}
	else
	{
		entry* prev = curr;
		while (curr->next != NULL && curr->sec > e->sec)
		{
			curr = curr->next;
			prev = prev->next;
		}
		
		// we got to the end of the list --> simply add the current new	
		// entry as the LAST entry
		if (curr->next == NULL)
		{
			curr->next = e;
		}
		else
		{
			prev->next = e;
			e->next = curr;
		}
	} 
}

void displayEntries()
{
	entry* tmp = head;
	while (tmp != NULL)
	{
		printf("<%lu,%lu>-->", tmp->funcNum,tmp->sec);
		tmp = tmp->next;
	}
	printf("NULL \n");
}

void clearEntries()
{
	entry* tmp = head;
	while (tmp != NULL)
	{
		printf("freeing entry <%lu,%lu> \n", tmp->funcNum,tmp->sec);
		entry* entryToDelete = tmp;
		tmp = tmp->next;
		free(entryToDelete);
	}
}

// =================================================================================================================================================================
// Usage function:
// --------------
void q54Usage()
{
	// insert first entry
	CreateTimer(func1, 3, 1);
	CreateTimer(func2, 7, 2);

	printf("q54Usage - after adding all entries, display list of entries: \n");
	displayEntries();

	printf("q54Usage - before terminating, free all entries \n");
	clearEntries();
}



