
#ifndef OCTETOS_PKMT_TESTS_V0_HH
#define OCTETOS_PKMT_TESTS_V0_HH

#include <CUnit/Basic.h>

#if defined(__linux__)

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida"
#endif

int v0_init(void);
int v0_clean(void);
void v0_developing();


#endif
