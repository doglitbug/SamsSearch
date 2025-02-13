#pragma once
#include <cstring>
#include <map>
#include <string>
#include <utility>

/// @brief Custom Properties parsing object
class CPO {
public:
    CPO() = default;

    explicit CPO(std::map<std::string, std::string> properties) {
        m_properties = std::move(properties);
    }

    ~CPO() = default;

    bool getBool(std::string &name, bool defaultValue = false) {  try {
        if (const auto it = m_properties.find(name); it != m_properties.end()) {
            return strcmp(it->second.c_str(), "true");
        }
    } catch (...) {
    }
        return defaultValue;}
    //color (a 32-bit color value)
    //file (a file reference, which is saved as a relative path)
    float getFloat(const std::string &name, const float defaultValue = 0.0f) {
        try {
            if (const auto it = m_properties.find(name); it != m_properties.end()) {
                return stof(it->second);
            }
        } catch (...) {
        }
        return defaultValue;
    }

    int getInt(const std::string &name, const int defaultValue = 0) {
        try {
            if (const auto it = m_properties.find(name); it != m_properties.end()) {
                return stoi(it->second);
            }
        } catch (...) {
        }
        return defaultValue;
    }

    std::string getString(const std::string &name, std::string defaultValue = "") {
        try {
            if (const auto it = m_properties.find(name); it != m_properties.end()) {
                return it->second;
            }
        } catch (...) {
        }
        return defaultValue;
    }

private:
    std::map<std::string, std::string> m_properties;
};