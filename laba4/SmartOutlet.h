#pragma once
#include "PoweredDevice.h"
#include "ISensor.h"

class SmartOutlet : public PoweredDevice, public ISensor {
    double voltage;
public:
    SmartOutlet(const std::string& name, double power, double voltage);
    SmartOutlet(const SmartOutlet& other);
    SmartOutlet& operator=(const SmartOutlet& other);
    double getCurrentVoltage() const override;
    void setVoltage(double value);
    std::string getStatus() const override;
};
