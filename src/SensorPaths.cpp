#include "SensorPaths.hpp"

#include <regex>
#include <string>

namespace sensor_paths
{

// This is an allowlist of the units a sensor can measure. Should be in sync
// with
// phosphor-dbus-interfaces/blob/master/yaml/xyz/openbmc_project/Sensor/Value.interface.yaml#L38

/**
 * @brief Returns the path for the given unit.
 *
 * @param[in] units The unit to search for.
 * @return const std::string& The path for the unit, or an empty string if not found.
 */
const std::string& getPathForUnits(const std::string& units) const
{
    for (const auto& unit : unitsMap)
    {
        if (unit.dbusUnitName == units || unit.dbusPathName == units)
        {
            return unit.emUnitName;
        }
    }
    static const std::string emptyString;
    return emptyString;
}

std::string escapePathForDbus(const std::string& name)
{
    std::string result;
    result.reserve(name.size());
    for (char c : name)
    {
        if (std::isalnum(c) || c == '/' || c == '_')
        {
            result += c;
        }
        else
        {
            result += '_';
        }
    }
    return result;
}

std::string convertToFullUnits(const std::string& units)
{
    for (const auto& unit : unitsMap)
    {
        if (unit.dbusUnitName == units)
        {
            return std::string(unit.dbusPathName);
        }
    }
    return "";
}

} // namespace sensor_paths
