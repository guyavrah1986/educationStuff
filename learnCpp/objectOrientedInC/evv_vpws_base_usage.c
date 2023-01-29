#include <stdio.h>

/*
#include "evv_vpws_base.h"
#include "evv_evi_base.h"
*/

// Good link:
// https://stackoverflow.com/a/352364/1971003

// forward decleration for compilation
struct evv_svc_base;

struct evv_svc_base_vtable
{
    void (*init)(struct evv_svc_base*);
    void (*continue_work)(struct evv_svc_base*);
};

// The base class
struct evv_svc_base
{
	// This vtable pointer will eventually point to a "concrete" v-table of
	// the derived objects.
	struct evv_svc_base_vtable* vtable;

	// Common members for all derieved objects
	unsigned long evi_index;	
	char* rd[9];	
};

// The base class "virtual functions injectors"
void init(struct evv_svc_base* a_this)
{
	a_this->vtable->init(a_this);
}

void continue_work(struct evv_svc_base* a_this)
{
	a_this->vtable->continue_work(a_this);
}

// Derived class 1
struct evv_evi_base
{
	// Base class "portion"
	struct evv_svc_base svc_base;

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

//.Global vtable for evv_evi_base - will be "used" by all instacnes of evv_evi_base
struct evv_svc_base_vtable evv_evi_base_vtable =
{
    &evv_evi_base_init, /* you might get a warning here about incompatible pointer types */
    &evv_evi_base_continue_work   /* you can ignore it, or perform a cast to get rid of it */
};

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
