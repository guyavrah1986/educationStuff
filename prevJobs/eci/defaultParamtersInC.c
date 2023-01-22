#include <stdio.h>

typedef struct {
	void* evv_svc_base;
	void* evb_ro_route_base;
	unsigned char add_delete;
	void* evv_vpws_if_cb;
} f_args;

void evv_svc_update_route_notify(void* evv_svc_base, void* evb_ro_route_base, unsigned char add_delete, void* evv_vpws_if_cb)
{

}

int main(int argc, char** argv)
{
	printf("main - start\n");
	printf("main - end\n");
	return 0;
}

