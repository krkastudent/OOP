/**
 * @file Thermostat.cpp
 * @brief Реализация класса Thermostat.
 */
#include "Thermostat.h"
#include <sstream>

using namespace std;

Thermostat::Thermostat(const string& name, double power, double temperature, const string& mode): PoweredDevice(name, power), temperature(temperature), mode(mode) {}
Thermostat::Thermostat(const Thermostat& other): PoweredDevice(other), temperature(other.temperature), mode(other.mode) {}
Thermostat& Thermostat::operator=(const Thermostat& other) {
    if (this != &other) {
        PoweredDevice::operator=(other);
        temperature = other.temperature;
        mode = other.mode;
    }
    return *this;
}

void Thermostat::setTemperature(double value) { temperature = value; }
string Thermostat::getStatus() const {
    ostringstream out;
    out << "Thermostat " << (on ? "ON" : "OFF") << ", " << powerConsumption << " W, temperature=" << temperature << ", mode=" << mode;
    return out.str();
}
