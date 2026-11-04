#pragma once

class ISensor {
public:
    virtual ~ISensor();
    virtual double getCurrentVoltage() const = 0;
};
