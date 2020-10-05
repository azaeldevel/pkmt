#include "Shell.hh"


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

#include <vector>


//
#include "Shell.hh"


namespace pkmt 
{

int Shell::cp(const std::string& from,const std::string& to)
{
	int fd_to, fd_from;
    char buf[4096];
    ssize_t nread;
    int saved_errno;

    fd_from = open(from.c_str(), O_RDONLY);
    if (fd_from < 0)
        return -1;

 	std::string strto;
	if(strcmp(to.c_str(),".") == 0)
	{
		strto = basename((char*)from.c_str());
	}
	else
	{
		strto = to;
	}
    fd_to = open(strto.c_str(), O_WRONLY | O_CREAT | O_EXCL, 0666);
    if (fd_to < 0)
        goto out_error;

    while (nread = read(fd_from, buf, sizeof buf), nread > 0)
    {
        char *out_ptr = buf;
        ssize_t nwritten;

        do {
            nwritten = write(fd_to, buf, nread);

            if (nwritten >= 0)
            {
                nread -= nwritten;
                out_ptr += nwritten;
            }
            else if (errno != EINTR)
            {
                goto out_error;
            }
        } while (nread > 0);
    }

    if (nread == 0)
    {
        if (close(fd_to) < 0)
        {
            fd_to = -1;
            goto out_error;
        }
        close(fd_from);

        /* Success! */
        return 0;
    }

  out_error:
    saved_errno = errno;

    close(fd_from);
    if (fd_to >= 0)
        close(fd_to);

    errno = saved_errno;
    return -1;    
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
   	std::vector<std::string> result;
   	std::stringstream s_stream(path); //create string stream from the string
   	while(s_stream.good()) 
   	{
      	std::string substr;
      	getline(s_stream, substr, '/'); //get first string delimited by comma
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
   	
   	return 0;
}
size_t Shell::write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}
int Shell::wget(const std::string& url,const std::string& in)
{
	CURL *curl_handle;
	static std::string fullpath = in + "/" + getfilename_url(url);
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
 
  	/* cleanup curl stuff */ 
  	curl_easy_cleanup(curl_handle);
 
  	curl_global_cleanup();  
  	
  	return 0;	
}




}