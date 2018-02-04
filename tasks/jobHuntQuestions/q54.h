#include <stdio.h>
#include <unistd.h>

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
	printf("CreateTimer \n");
	entry* e = (entry*)malloc(sizeof(entry));
	e->func = func;
	e->sec = seconds;
	e->next = NULL;
	e->funcNum = funcNum;
	insertEntry(e);
}

void StartTimers()
{
	printf("StartTimers - start \n");
	entry* tmp = head;
	static size_t prevDelay = 0;

	while (tmp != NULL)
	{
		size_t currDelayInSec = tmp->sec;
		printf("StartTimers - about to sleep for %lu seconds before calling function %lu \n", currDelayInSec - prevDelay, tmp->funcNum);
		sleep(currDelayInSec - prevDelay);
		tmp->func();
		prevDelay = currDelayInSec;
		tmp = tmp->next;
	}
	printf("\n \n StartTimers - end \n");
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
	}// single entry list
	else if (curr->next == NULL)
	{
		if (curr->sec < e->sec)
		{
			curr->next = e;
		}
		else
		{
			e->next = curr;
			head = e;
		}
	}
	else
	{
		entry* prev = NULL;
		while (curr != NULL && curr->sec < e->sec)
		{
			prev = curr;
			curr = curr->next;
		}
		
		// the current entry needs to be the new head of the list
		if (prev == NULL)
		{
			printf("insertEntry - adding entry with function:%lu , and seconds:%lu as the LAST entry in the list \n",e->funcNum, e->sec);
			e->next = head;
			head = e;
		}
		else
		{
			prev->next = e;
			e->next = curr;
			printf("insertEntry - adding entry with function:%lu , and seconds:%lu AFTER entry with seconds:%lu \n",e->funcNum, e->sec, prev->funcNum, prev->sec);
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
	CreateTimer(func3, 7, 3);
	CreateTimer(func2, 5, 2);
	CreateTimer(func4, 8, 4);

	printf("q54Usage - after adding all entries, display list of entries: \n");
	displayEntries();

	printf("q54Usage - about to call all entries \n");
	StartTimers();

	printf("q54Usage - before terminating, free all entries \n");
	clearEntries();
}



