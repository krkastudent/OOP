#pragma once
#include "SmartDevice.h"
#include <chrono>

class PoweredDevice : public SmartDevice {
protected:
    double powerConsumption;
    PoweredDevice(const std::string& name, double powerConsumption);
    PoweredDevice(const PoweredDevice& other);
    PoweredDevice& operator=(const PoweredDevice& other);

private:
    std::chrono::steady_clock::time_point started;
    double sessionPower;
    static double totalEnergyConsumed;

public:
    ~PoweredDevice() override;
    void turnOn() override;
    void turnOff() override;
    virtual double getPowerUsage() const;
    static double getTotalEnergyConsumed();
};
