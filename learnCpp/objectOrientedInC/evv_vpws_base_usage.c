#include <stdio.h>
#include <stdlib.h>

/*
#include "evv_vpws_base.h"
#include "evv_evi_base.h"
*/

// Good link:
// https://stackoverflow.com/a/352364/1971003

// ===========================================================================================================
// ===========================================================================================================
// Base class
// ----------

// forward decleration for compilation
struct evv_svc_base;

struct evv_svc_base_vtable
{
    void (*init)(struct evv_svc_base*);
    void (*continue_work)(struct evv_svc_base*);
    struct evv_svc_base* (*dtor)(struct evv_svc_base* a_this); // virtual destructor
};

// The base class
struct evv_svc_base
{
	// This vtable pointer will eventually point to a "concrete" v-table of
	// the derived objects.
	struct evv_svc_base_vtable vtable;

	// Common members for all derieved objects
	unsigned long evi_index;	
	char* rd[9];	
};

// The base class "virtual functions injectors"
void evv_svc_base_init(struct evv_svc_base* a_this)
{
	printf("evv_svc_base::evv_svc_base_init\n");
	a_this->vtable.init(a_this);
}

void evv_svc_base_continue_work(struct evv_svc_base* a_this)
{
	printf("evv_svc_base::evv_svc_base_continue_work\n");
	a_this->vtable.continue_work(a_this);
}

struct evv_svc_base* evv_svc_base_dtor(struct evv_svc_base* a_this)
{
    printf("evv_svc_base::dtor\n");
    return a_this;
}

struct evv_svc_base* evv_svc_base_alloc()
{
    return (struct evv_svc_base*)malloc(sizeof(struct evv_svc_base));
}

struct evv_svc_base* evv_svc_base_new(struct evv_svc_base* a_evv_svc_base)
{
    	a_evv_svc_base->vtable.init = evv_svc_base_init;
    	a_evv_svc_base->vtable.continue_work = evv_svc_base_continue_work;
	a_evv_svc_base->vtable.dtor = evv_svc_base_dtor;
    	return a_evv_svc_base;
}

void evv_svc_base_free(struct evv_svc_base* a_this)
{
    a_this->vtable.dtor(a_this);
    free(a_this);
}

// ===========================================================================================================
// ===========================================================================================================
// Derived class 1
// ---------------

struct evv_evi_base
{
	// Base class "portion" (must be first)
	struct evv_svc_base svc_base;

	// Single vtable for ALL evv_evi_base instances
	struct evv_svc_base_vtable* vtable;

	// Derived class specific members
	unsigned int irbInterfaceObject;
};

// Implementation for virtual functions of Derived1
void evv_evi_base_init(struct evv_evi_base* a_this)
{
	printf("evv_evi_base::init\n");
}

void evv_evi_base_continue_work(struct evv_evi_base* a_this)
{
	printf("evv_evi_base::continue_work\n");
}

// Global vtable for evv_evi_base - will be "used" by all instacnes of evv_evi_base
static struct evv_svc_base_vtable evv_evi_base_vtable =
{
	&evv_evi_base_init, 
	&evv_evi_base_continue_work,
	&evv_evi_base_free
};

struct evv_evi_base* evv_evi_base_dtor(struct evv_evi_base* a_this)
{
	printf("evv_evi_base::dtor\n");
	evv_svc_base_dtor((struct evv_svc_base*)a_this);
	return a_this;
}

struct evv_evi_base* evv_evi_base_alloc()
{
    return (struct evv_evi_base*)malloc(sizeof(struct evv_evi_base));
}

struct evv_evi_base* evv_evi_base_new(struct evv_evi_base* a_evv_evi_base)
{
	// Explict call to parent constructor
    	evv_svc_base_new((struct evv_svc_base*)a_evv_evi_base);

	// Ponint to the global vtable
	a_evv_evi_base->vtable = &evv_evi_base_vtable;

    	//a_evv_evi_base->vtable->init = evv_evi_base_init;
    	//a_evv_evi_base->vtable->continue_work = evv_evi_base_continue_work;
	//a_evv_evi_base->vtable->dtor = evv_evi_base_dtor;
    	return a_evv_evi_base;
}

void evv_evi_base_free(struct evv_evi_base* a_this)
{
    a_this->vtable->evv_evi_base_dtor(a_this);
    free(a_this);
}
*/

// ===========================================================================================================
// ===========================================================================================================
// main:
// ----

int main(int argc, char** argv)
{
	printf("main - start\n");

	/*
	evv_svc_base* vpws = (evv_svc_base*)new_vpws_base("1.1.1.1:5");
	printf("main - create evv_vpws_base on the heap\n");
	vpws->Init(vpws);
	evv_svc_base* evi = (evv_svc_base*)new_evi_base("2.2.2.2:5");
	printf("main - create evv_evi_base on the heap\n");
	evi->Init(evi);
	evi->delete_evi_base(evi);
	*/
	printf("main - end\n");
	return 0;
}
