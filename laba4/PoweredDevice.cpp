#include "PoweredDevice.h"
#include <cmath>
#include <stdexcept>

double PoweredDevice::totalEnergyConsumed = 0.0;

PoweredDevice::PoweredDevice(const std::string& name, double powerConsumption)
    : SmartDevice(name), powerConsumption(powerConsumption), sessionPower(0.0) {
    if (!std::isfinite(powerConsumption) || powerConsumption <= 0)
        throw std::invalid_argument("Power must be positive and finite");
}
PoweredDevice::PoweredDevice(const PoweredDevice& other)
    : SmartDevice(other), powerConsumption(other.powerConsumption),
      started(std::chrono::steady_clock::now()), sessionPower(other.sessionPower) {}

PoweredDevice& PoweredDevice::operator=(const PoweredDevice& other) {
    if (this != &other) {
        turnOff();
        SmartDevice::operator=(other);
        powerConsumption = other.powerConsumption;
        started = std::chrono::steady_clock::now();
        sessionPower = other.sessionPower;
    }
    return *this;
}
PoweredDevice::~PoweredDevice() { turnOff(); }

void PoweredDevice::turnOn() {
    if (!on) {
        on = true;
        started = std::chrono::steady_clock::now();
        sessionPower = getPowerUsage();
    }
}
void PoweredDevice::turnOff() {
    if (on) {
        const double seconds = std::chrono::duration<double>(
            std::chrono::steady_clock::now() - started).count();
        totalEnergyConsumed += sessionPower * seconds / 3600000.0;
        on = false;
    }
}
double PoweredDevice::getPowerUsage() const { return on ? powerConsumption : 0.0; }
double PoweredDevice::getTotalEnergyConsumed() { return totalEnergyConsumed; }
