#pragma once
#include "PoweredDevice.h"

class Thermostat : public PoweredDevice {
    double temperature;
    std::string mode;
public:
    Thermostat(const std::string& name, double power, double temperature, const std::string& mode);
    Thermostat(const Thermostat& other);
    Thermostat& operator=(const Thermostat& other);
    void setTemperature(double value);
    std::string getStatus() const override;
};
