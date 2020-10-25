
#ifndef BDT_SHELL
#define BDT_SHELL

#include <octetos/coreutils/shell.hh>
#include <list>


namespace pkmt
{

class Shell : public coreutils::Shell
{
private:
	static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);
	
public:
	struct pair_md5
	{
		std::string md5;
		std::string file;
	};
	bool getMD5s(std::list<pair_md5>& v,const std::string&);
 	std::string getfilename_url(const std::string&);
	/*
	*\brief 
	*param url url de descarga
	*param in archivo de colacion
	**/
	int wget(const std::string& url,const std::string& in,std::ostream& out);
	int mkdir(const std::string&,bool recursive);
	bool exists(const std::string& filename);
	int cp(const std::string&,const std::string&);
	
};


}

#endif