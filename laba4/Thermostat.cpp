#include "Thermostat.h"
#include <sstream>

Thermostat::Thermostat(const std::string& name, double power, double temperature,
                       const std::string& mode)
    : PoweredDevice(name, power), temperature(temperature), mode(mode) {}
Thermostat::Thermostat(const Thermostat& other)
    : PoweredDevice(other), temperature(other.temperature), mode(other.mode) {}
Thermostat& Thermostat::operator=(const Thermostat& other) {
    if (this != &other) {
        PoweredDevice::operator=(other);
        temperature = other.temperature;
        mode = other.mode;
    }
    return *this;
}
void Thermostat::setTemperature(double value) { temperature = value; }
std::string Thermostat::getStatus() const {
    std::ostringstream out;
    out << "Thermostat " << (on ? "ON" : "OFF") << ", " << powerConsumption
        << " W, temperature=" << temperature << ", mode=" << mode;
    return out.str();
}
