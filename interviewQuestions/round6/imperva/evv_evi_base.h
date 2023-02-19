//evv_evi_base.h
#pragma once

typedef struct _evv_evi_base evv_evi_base; 

//declaration of pointers to functions
typedef void    (*fptrInit)(evv_evi_base*);
typedef void    (*fptrContinueWork)(evv_evi_base*);

typedef struct _evv_evi_base 
{
    void* pBaseObj;

    //interface for function
    fptrInit         Init;
    fptrContinueWork ContinueWork;
}evv_evi_base;


evv_evi_base* new_evi_base(const char* pRd);           //constructor
void delete_evi_base(evv_evi_base* pEviBase);    //destructor
void evv_evi_base_init(evv_evi_base* pEvvEviBase);
void evv_evi_base_continue_work(evv_evi_base* pEvvEviBase);
