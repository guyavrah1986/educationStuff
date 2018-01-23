#include <string>

class CStatsCollectedBase
{
	public:
		CStatsCollectedBase(const char* pName, bool bIsEnabled, bool isOutputEnabled);
		virtual ~CStatsCollectedBase();

		virtual bool Update() = 0;
		virtual bool ostream() = 0;

	protected:
		std::string m_pObjectName;
		bool m_bIsEnabled;
		bool m_bIsOutputEnabled;
};
