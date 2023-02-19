// evv_svc_base.c

#include <stdio.h>
#include <stdlib.h>
#include "evv_svc_base.h"

evv_svc_base* new_svc_base(const char* pRd)
{
	evv_svc_base* new_evv_svc_base_obj = (evv_svc_base*)malloc(sizeof(evv_svc_base));
	printf("new_svc_base - allocated evv_svc_base at address:%p\n", new_evv_svc_base_obj);
	new_evv_svc_base_obj->pDerivedObj = new_evv_svc_base_obj;

    	// Initializing interface for access to functions
	vtable->Init = NULL;     			//evv_svc_base_init;
	vtable->ContinueWork = NULL; 			//evv_svc_base_continue_work; 	
	return new_evv_svc_base_obj;
}

void delete_svc_base(evv_svc_base* a_this)
{
	printf("delete_svc_base - free-ing evv_svc_base at address:%p\n", a_this);
	//free(a_this);
}

// Note that in this case, evv_svc_base did NOT implement the two "polymorphic" methods (cuase it does not "use" them).
// void evv_svc_base_init(evv_svc_base* pEvvSvcBase);
// void evv_svc_base_continue_work(evv_svc_base* pEvvSvcBase);



