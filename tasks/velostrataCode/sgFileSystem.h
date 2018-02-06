// ============================================================================================================================================================
/*
*
*
*
*/
// ============================================================================================================================================================

#include <functional>

enum ErrorCode
{
	SP_M2M_ERROR_CODE_SUCCESS = 0,
	SP_M2M_ERROR_CODE_GENERAL_FAUILRE
};

class Result
{
public:
	Result(const enum ErrorCode& errorCode)
		: m_errorCode(errorCode)
	{

	}

	bool IsSuccess() const
	{
		return (m_errorCode == ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
	}

private:
	ErrorCode m_errorCode;
};

class SgFileSystem
{
	public:
	SgFileSystem(const std::string& rootPath);
	~SgFileSystem();

	void Delete(const std::string& fileName, const std::function<void(Result& res)>& callback);
	void Exsists(const std::string& fileName, char* buff, size_t numOfByteToRead, const std::function<void(Result& res)>& callback);
	void Write(const std::string& fileName, const char* buff, size_t len, const std::function<void(Result& res)>& callback);
	void Read(const std::string& fileName, char* buff, size_t numOfByteToRead, const std::function<void(Result& res)>& callback);
	void List(const std::string& fileName, char* buff, size_t numOfByteToRead, const std::function<void(Result& res)>& callback);


	// getters & setters
	std::string GetRootPath() const;

	private:
	std::string m_rootPath;
};
