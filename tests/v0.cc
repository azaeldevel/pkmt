
#include "v0.hh"

#include <string>
#include <iostream>
#include <variant>
#include <random>
#include <chrono>

#include <pkmt/0/Package.hh>

#if defined(__linux__)

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida"
#endif


namespace pkmt = oct::pkmt::v0;

int v0_init(void)
{
	return 0;
}

int v0_clean(void)
{
	return 0;
}

void v0_developing()
{

    pkmt::Package pack1(3);
        pack1->major = 1;
        pack1->minor = 0;
        pack1->patch = 0;
        pack1->brief = "Packete princial";
        pack1->name = "Main";
        pack1[0]->major = 0;
        pack1[0]->minor = 1;
        pack1[0]->patch = 0;
        pack1[0]->brief = "Packete 1";
        pack1[0]->name = "Req 1";
        pack1[1]->major = 0;
        pack1[1]->minor = 1;
        pack1[1]->patch = 0;
        pack1[1]->brief = "Packete 2";
        pack1[1]->name = "Req 2";
            pack1[1].resize(2);
            pack1[1][0]->major = 3;
            pack1[1][0]->minor = 9;
            pack1[1][0]->patch = 0;
            pack1[1][0]->brief = "Packete 4";
            pack1[1][0]->name = "Req 4";
            pack1[1][1]->major = 3;
            pack1[1][1]->minor = 9;
            pack1[1][1]->patch = 0;
            pack1[1][1]->brief = "Packete 5";
            pack1[1][1]->name = "Req 5";
        pack1[2]->major = 5;
        pack1[2]->minor = 1;
        pack1[2]->patch = 23;
        pack1[2]->brief = "Packete 3";
        pack1[2]->name = "Req 3";

    //std::cout << std::endl;
    //pkmt::print(std::cout,pack1);

    //constexpr pkmt::package _pack2 = {1,3,56,"Package test","Requsito actual"};
    //constexpr pkmt::Package pack2(_pack2);
}

