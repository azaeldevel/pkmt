
#include <CUnit/Basic.h>
#include <octetos/core/Version.hh>
#include <iostream>
#include <libconfig.h++>


#include "../src/data.hh"
#include "config.h"



void testRepositoryClass()
{
	pkmt::Repository repo;
	try
	{
		std::string dir = PATHDIR;
		dir += "/src/tmpsys";
		repo = dir;
	}
	catch(libconfig::FileIOException ex)
	{
		std::cerr << ex.what() << "\n";
		CU_ASSERT(false);
		return;
	}
	//std::cout << "Name repos : " << repo.getName() << "\n";
}

void testBaseClass()
{
	pkmt::Phase base("source");

	std::string str = base;
}



void testPhaseClass()
{
	pkmt::Phase phase("testing");

	std::string str = phase;
}


void testArchClass()
{
	pkmt::Architecture arch("x86-64");

	std::string str = arch;
}


int init(void)
{
	return 0;
}
int clean(void)
{
	return 0;
}




int main(int argc, char *argv[])
{  

	octetos::core::Semver verpk;
	verpk.set(VERSION);
	int majorNumber = 0;
	if(majorNumber != verpk.getMajor())
	{
		std::cerr << "Cree un nuevo archivo para la version '" << majorNumber << "' estas en la version'" << VERSION << "'\n";
		return EXIT_FAILURE;
	}
	
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite("Testing pkmt", init, clean);
	if (NULL == pSuite) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Testing Architecture class.", testArchClass)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Testing Phase class.", testPhaseClass)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Testing Base class.", testBaseClass)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	
	if ((NULL == CU_add_test(pSuite, "Testing repository class.", testRepositoryClass)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();	
}
