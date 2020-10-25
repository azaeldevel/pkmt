#include "shell.hh"


//curl
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>

//mkdir
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <filesystem>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <libgen.h>

#include <vector>


//


namespace pkmt 
{

int Shell::cp(const std::string& from,const std::string& to)
{
	std::string tostr=to;
	std::ifstream in(from);
	if(to.compare(".") == 0)
	{
		std::cout << "Basename : " << from << "\n";
		tostr = basename((char*)from.c_str());
	}
	else
	{
		tostr = to;
	}
	std::ofstream out(tostr);
	
	std::string line;
	while (std::getline(in, line))
	{
		out << line << "\n";
	}
	
	in.close();
	out.close();
	
	return 0;
}
bool Shell::getMD5s(std::list<pair_md5>& v,const std::string& l)
{
	std::vector<std::string> result;
   	std::stringstream s_stream(l); //create string stream from the string
   	while(s_stream.good()) 
   	{
      	std::string substr;
      	getline(s_stream, substr, ' '); //get first string delimited by comma
      	result.push_back(substr);
   	}

   	pair_md5 md5;
   	md5.md5 = result[0];
   	md5.file = result[result.size() - 1];
   	std::cout << "md5:" << md5.md5 << " file:" << md5.file << "\n";
   	v.push_back(md5);
   	return true;  	
}
bool Shell::exists(const std::string& filename)
{
	struct stat buffer;
	int ret = stat(filename.c_str(),&buffer);
	if(ret == 0) return true;
	else return false;
}
	
std::string Shell::getfilename_url(const std::string& url)
{
   	std::vector<std::string> result;
   	std::stringstream s_stream(url); //create string stream from the string
   	while(s_stream.good()) 
   	{
      	std::string substr;
      	getline(s_stream, substr, '/'); //get first string delimited by comma
      	result.push_back(substr);
   	}
   	
   	return result[result.size() - 1];
}
int Shell::mkdir(const std::string& path,bool recursive) 
{
	if(recursive)
	{
	   	std::vector<std::string> result;
	   	std::stringstream s_stream(path); //create string stream from the string
	   	while(s_stream.good()) 
	   	{
		  	std::string substr;
		  	getline(s_stream, substr, '/'); //get first string delimited by /
		  	result.push_back(substr);
	   	}
	   	
	   	std::string newpath ;
	   	for(const std::string& s : result)
	   	{   		
	   		//newpath += "/";
	   		newpath += s + "/";
	   		//std::cout << newpath << "\n"; 
	   		//int retmk = exists(newpath);
	   		if(!exists(newpath)) 
	   		{
	   			if(!coreutils::Shell::mkdir(newpath))
	   			{
	   				std::cerr << "no se pudo crear " << newpath << "\n";
	   				return 1;
	   			}
	   		}
	   	}
   	}
   	else
   	{
   		
   	}
   	return 0;
}
size_t Shell::write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}
int Shell::wget(const std::string& url,const std::string& in,std::ostream& out)
{
	CURL *curl_handle;
	out << "\nDescargando '" << url << "'";
	static std::string fullpath;
	
	if(in.compare(".") == 0)
	{
		fullpath = in + "/" + getfilename_url(url);
	}
	else
	{
		fullpath = getfilename_url(url);
	}
	
  	FILE *pagefile;
	
  	curl_global_init(CURL_GLOBAL_ALL);
 
  	/* init the curl session */ 
  	curl_handle = curl_easy_init();
 
  	/* set URL to get here */ 
  	curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
 
  	/* Switch on full protocol/debug output while testing */ 
  	curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);
 
  	/* disable progress meter, set to 0L to enable it */ 
  	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
 
  	/* send all data to this function  */ 
  	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
 
  	/* open the file */ 
  	pagefile = fopen(fullpath.c_str(), "wb");
  	if(pagefile) 
  	{	 
		/* write the page body to this file handle */ 
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);
	 	
		/* get it! */ 
		curl_easy_perform(curl_handle);
	 
		/* close the header file */ 
		fclose(pagefile);
		
		return 1;
  	}
  	
  	out << " hecho.\n";
 
  	/* cleanup curl stuff */ 
  	curl_easy_cleanup(curl_handle);
 
  	curl_global_cleanup();  
  	
  	return 0;	
}




}