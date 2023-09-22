
#include <iostream>
#include <CUnit/Basic.h>


#ifdef OCTETOS_PKMT_V0_TDD
	#include "v0.hh"
#endif

int main(int argc, char *argv[])
{
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

#ifdef OCTETOS_PKMT_V0_TDD
	//std::cout << "Step 2\n";
	CU_pSuite pSuite_v0 = CU_add_suite("Package Manager Tool", v0_init, v0_clean);
	if (NULL == pSuite_v0)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite_v0, "Developing..", v0_developing)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
#ifdef OCTETOS_PKMT_V0_TDD_PERFORMANCE

#endif

#endif

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
