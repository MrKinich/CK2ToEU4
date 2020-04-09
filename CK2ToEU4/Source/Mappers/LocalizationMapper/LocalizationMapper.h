#ifndef LOCALIZATION_MAPPER
#define LOCALIZATION_MAPPER
#include <string>
#include <optional>
#include <map>

class Configuration;
namespace mappers
{
typedef struct {
	std::string english;
	std::string french;
	std::string german;
	std::string spanish;
} LocBlock;
	
class LocalizationMapper
{
  public:
	LocalizationMapper() = default;
	void scrapeLocalizations(const Configuration& theConfiguration);

	[[nodiscard]] std::optional<LocBlock> getLocBlockForKey(const std::string& key) const;

  private:

	std::map<std::string, LocBlock> localizations;
};
} // namespace mappers

#endif // LOCALIZATION_MAPPER