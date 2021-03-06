
#include <CUnit/Basic.h>
#include <octetos/core/Version.hh>
#include <iostream>
#include <libconfig.h++>



#include "../src/data.hh"
#include "config.h"




void testManagerClass()
{
	pkmt::Manager manager("autotools");

	std::string str = manager;
}




void testRepositoryClass()
{
	pkmt::Repository repo;
	std::string dir;
	try
	{
		dir = PATHDIR;
		dir += "/src/tmpsys";
		repo = dir;
	}
	catch(const libconfig::FileIOException &fioex)
	{
		std::cerr << "\n" << fioex.what() << "\n";
		CU_ASSERT(false);
		return;
	}
	std::cout << "\n";
	std::cout << "Name repos : " << repo.getName() << "\n";
	CU_ASSERT(true);
	
	pkmt::Package* pktmpsys = repo.find("tmpsys");
	if(pktmpsys == NULL)
	{
		std::cerr << "No se encontro el paquete tmpsys\n";
		CU_ASSERT(false);
		return;
	}
	else
	{
		std::cout << "Paquete : " << pktmpsys->getName() << " in " << pktmpsys->getFilename() << "\n";
		//pktmpsys->readDataFull();
		try
		{
			pktmpsys->readDependencies();
		}
		catch(pkmt::NotFoundDependencyException e)
		{
			std::cerr << "Fallo la lectura de dependencias\n";
			std::cerr << e.what() << "\n";
			CU_ASSERT(false);
		}
		catch(std::exception& e)
		{
			std::cerr << "Fallo la lectura de dependencias\n";
			std::cerr << e.what() << "\n";
			CU_ASSERT(false);
			return;
		}
		
		for(auto it = pktmpsys->getDependencies().begin() ;  it != pktmpsys->getDependencies().end();it++)
		{
			std::cout << pktmpsys->getName() << " -> " << it->second->getName() << "\n";
		}
		
		CU_ASSERT(true);
	}
	
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
	
	
	if ((NULL == CU_add_test(pSuite, "Testing Manager class.", testManagerClass)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Testing Repository class.", testRepositoryClass)))
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
