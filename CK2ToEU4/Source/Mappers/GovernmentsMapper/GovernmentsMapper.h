#ifndef GOVERNMENTS_MAPPER
#define GOVERNMENTS_MAPPER

#include "GovernmentsMapping.h"
#include "newParser.h"

namespace mappers
{
class GovernmentsMapper: commonItems::parser
{
  public:
	GovernmentsMapper();
	explicit GovernmentsMapper(std::istream& theStream);

	[[nodiscard]] std::optional<std::pair<std::string, std::string>> matchGovernment(const std::string& ck2Government, const std::string& ck2Title) const;

  private:
	void registerKeys();
	std::vector<GovernmentsMapping> govMappings;
};
} // namespace mappers

#endif // GOVERNMENTS_MAPPER