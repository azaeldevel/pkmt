
#ifndef PKMT_COMMANDS
#define PKMT_COMMANDS


namespace pkmt
{
struct Configure
{
};
struct ConfigureLFS : public Configure
{
	std::string LFS;
	std::string LFS_PART;
	std::string LFS_TGT;
	std::string LFS_REPO_TMPSYS;
	std::string PKM;
	ConfigureLFS();
};
class Interpret
{
private:
	const Configure* configure;
	//
	void pkmt(int argc, char* argv[]);
	void prephost(int argc, char* argv[]);
	void prephost_build(int argc, char* argv[]);
	void prephost_install(int argc, char* argv[]);
	void prephost_remove(int argc, char* argv[]);
	void prephost_sync(int argc, char* argv[]);
	void writeParamschar (std::string& argout, int argc, char *argv[]);
	
public:
	Interpret(const Configure& configure);
	void execute(int argc, char* argv[]);
};

class pkmt
{

};


}

#endif