//evv_svc_base.h
#pragma once

// forward decleration for the base type evv_svc_base ("Base object")
typedef struct _evv_svc_base evv_svc_base; 

// forward declration for the v-table functions
typedef void    (*fptrInit)(evv_svc_base* a_this);
typedef void    (*fptrContinueWork)(evv_svc_base* a_this);

struct evv_svc_vtable
{
	//declaration of pointers to functions that will be "virtual" (polymorphic)
	fptrInit         Init;
	fptrContinueWork ContinueWork;
}

typedef struct _evv_svc_base 
{
	// Pointers to all polymorphic functions ("virtual")
	evv_svc_vtable vtable;

	// Pointer to the derived object. Will be initialized during construction
	void* pDerivedObj;

	// Common members for all derived object(s)
	unsigned long evi_index;	
	char* rd[9];	
}evv_svc_base;


evv_svc_base* new_svc_base(const char* pRd);            //constructor
void delete_svc_base(evv_svc_base* pSvcBase);    	//destructor
void evv_svc_base_init(evv_svc_base* pEvvSvcBase);
void evv_svc_base_continue_work(evv_svc_base* pEvvSvcBase);

