



#include "header.hh"
#include "config.h"


namespace pkmt
{
	const std::string Header::getRoot_Repository() const
	{
		return rootRepo;
	}
	Header::Header(const std::string& r,const std::string& t,const octetos::core::Semver& v,const std::string& rr)
	{
		rootDir = r;
		target = t;
		version = v;
		rootRepo = rr;
	}
	const std::string Header::getRootDir()const
	{
		return rootDir;
	}
	const octetos::core::Semver& Header::getVersion()const
	{
		return version;
	}
	const octetos::core::Semver& Header::setVersion(const octetos::core::Semver& v)
	{
		version = v;
		return v;
	}
	const std::string& Header::getTarget()const
	{
		return target;
	}
	
	
	
	
	
	const std::string& HeaderLFS::getdatadir()const
	{
		return datadir;
	}
	const std::string HeaderLFS::getREPO_SOURCES()const
	{
		std::string str = REPO_SOURCES  + "/" + getVersion().toString();
		return str;
	}
	const std::string HeaderLFS::getREPO_ORIGIN_PACKAGES_TMPSYS()const
	{
		std::string str = REPO_ORIGIN_PACKAGES_TMPSYS + "/" + getVersion().toString();
		return str;
	}
	const std::string& HeaderLFS::getLFS()const
	{
		return LFS;
	}
	const std::string& HeaderLFS::getLFS_PART()const
	{
		return LFS_PART;
	}
	HeaderLFS::HeaderLFS():Header("/mnt/lfs","x86_64-lfs-linux-gnu",octetos::core::Semver(8,4),"/home/azael/develop/repos/pkmt")
	{
		REPO_ORIGIN_PACKAGES_TMPSYS="/home/azael/develop/repos/pkmt/sources/lfs";		
		LFS="/mnt/lfs";
		LFS_PART="/dev/sda14";
	}
	HeaderLFS::HeaderLFS(octetos::core::Semver& v):Header("/mnt/lfs","x86_64-lfs-linux-gnu",v,"/home/azael/develop/repos/pkmt")
	{
		REPO_ORIGIN_PACKAGES_TMPSYS="/home/azael/develop/repos/pkmt/packages/lfs/";		
		LFS="/mnt/lfs";
		LFS_PART="/dev/sda14";
	}

}
