
#ifndef BDT_HEADER
#define BDT_HEADER

#include <string>
#include <octetos/core/Version.hh>


namespace pkmt
{

class Header
{
private:
	std::string rootDir;
	std::string target;
	octetos::core::Semver version;
	std::string rootRepo;

public:	
	Header(const std::string& rootDir,const std::string& target,const octetos::core::Semver& version,const std::string& rootRepo);
	const std::string getRootDir() const;
	const std::string& getTarget() const;
	const octetos::core::Semver& getVersion()const;
	const octetos::core::Semver& setVersion(const octetos::core::Semver&);
	const std::string getRoot_Repository() const;
};

class HeaderLFS : public Header
{
protected:
	std::string LFS;
	std::string LFS_PART;
	std::string LFS_TGT;
	std::string REPO_ORIGIN_PACKAGES_TMPSYS;
	std::string REPO_SOURCES;
	std::string datadir;
	std::string ORIGIN_PACKAGES_CROSSTOOLCHAIN;
	
	
public:
	HeaderLFS();
	HeaderLFS(octetos::core::Semver& v);
	const std::string getREPO_SOURCES() const;
	const std::string getREPO_ORIGIN_PACKAGES_TMPSYS() const;
	const std::string& getLFS() const;
	const std::string& getLFS_PART() const;
	const std::string& getdatadir()const;
};

}

#endif
