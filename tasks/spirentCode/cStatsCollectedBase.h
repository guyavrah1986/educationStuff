#include <string>

class CStatsCollectedBase
{
	public:
		CStatsCollectedBase();
		virtual ~CStatsCollectedBase();

		virtual bool Update() = 0;
		virtual bool ostream() = 0;

	protected:
		std::string m_pObjectName;
		bool m_bIsEnabled;
		bool m_bIsOutputEnabled;
};
