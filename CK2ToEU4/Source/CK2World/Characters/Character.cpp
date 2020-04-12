#include "Character.h"
#include "Domain.h"
#include "Log.h"
#include "ParserHelpers.h"

CK2::Character::Character(std::istream& theStream, int chrID): charID(chrID)
{
	registerKeys();
	parseStream(theStream);
	clearRegisteredKeywords();
}

void CK2::Character::registerKeys()
{
	registerKeyword("bn", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString nameStr(theStream);
		name = nameStr.getString();
	});
	registerKeyword("cul", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString cultureStr(theStream);
		culture = cultureStr.getString();
	});
	registerKeyword("rel", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString religionStr(theStream);
		religion = religionStr.getString();
	});
	registerKeyword("fem", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString femStr(theStream);
		female = femStr.getString() == "yes";
	});
	registerKeyword("gov", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString govStr(theStream);
		government = govStr.getString();
	});
	registerKeyword("b_d", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString dateStr(theStream);
		birthDate = date(dateStr.getString());
	});
	registerKeyword("d_d", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString dateStr(theStream);
		deathDate = date(dateStr.getString());
	});
	registerKeyword("dnt", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt dynastyInt(theStream);
		dynasty = std::pair(dynastyInt.getInt(), nullptr);
	});
	registerKeyword("lge", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt liegeInt(theStream);
		liege = std::pair(liegeInt.getInt(), nullptr);
	});
	registerKeyword("piety", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble pieryDbl(theStream);
		piety = pieryDbl.getDouble();
	});
	registerKeyword("att", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::intList skillsList(theStream);
		const auto theList = skillsList.getInts();
		skills.diplomacy = theList[0];
		skills.martial = theList[1];
		skills.stewardship = theList[2];
		skills.intrigue = theList[3];
		skills.learning = theList[4];
	});
	registerKeyword("spouse", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt spouseInt(theStream);
		spouses.insert(std::pair(spouseInt.getInt(), nullptr));
	});
	registerKeyword("dmn", [this](const std::string& unused, std::istream& theStream) {
		const auto newDomain = Domain(theStream);
		primaryTitle = newDomain.getPrimaryTitle();
		capital = newDomain.getCapital();
	});
	registerRegex("[A-Za-z0-9\\:_.-]+", commonItems::ignoreItem);
}
