/**
 * @file PoweredDevice.cpp
 * @brief Реализация класса PoweredDevice.
 */
#include "PoweredDevice.h"
#include <cmath>
#include <stdexcept>

using namespace std;
using namespace std::chrono;

double PoweredDevice::totalEnergyConsumed = 0.0;

PoweredDevice::PoweredDevice(const string& name, double powerConsumption)
    : SmartDevice(name),
      powerConsumption(powerConsumption),
      sessionPower(0.0) {
    if (!isfinite(powerConsumption) || powerConsumption <= 0) {
        throw invalid_argument("Мощность должна быть положительным конечным числом");
    }
}

PoweredDevice::PoweredDevice(const PoweredDevice& other)
    : SmartDevice(other),
      powerConsumption(other.powerConsumption),
      started(steady_clock::now()),
      sessionPower(other.sessionPower) {
}

PoweredDevice& PoweredDevice::operator=(const PoweredDevice& other) {
    if (this != &other) {
        turnOff();
        SmartDevice::operator=(other);
        powerConsumption = other.powerConsumption;
        started = steady_clock::now();
        sessionPower = other.sessionPower;
    }

    return *this;
}

PoweredDevice::~PoweredDevice() {
    turnOff();
}

void PoweredDevice::turnOn() {
    if (!on) {
        on = true;
        started = steady_clock::now();
        sessionPower = getPowerUsage();
    }
}

void PoweredDevice::turnOff() {
    if (on) {
        const steady_clock::time_point now = steady_clock::now();
        const duration<double> elapsed = now - started;
        const double seconds = elapsed.count();

        const double energy = sessionPower * seconds / 3600000.0;
        totalEnergyConsumed += energy;
        on = false;
    }
}

double PoweredDevice::getPowerUsage() const {
    return on ? powerConsumption : 0.0;
}

double PoweredDevice::getTotalEnergyConsumed() {
    return totalEnergyConsumed;
}
