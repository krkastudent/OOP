/**
 * @file SmartOutlet.h
 * @brief Объявление класса SmartOutlet.
 */
#pragma once
#include "PoweredDevice.h"
#include "ISensor.h"

using namespace std;

/**
 * @brief Умная розетка с датчиком напряжения.
 * @details Демонстрирует множественное наследование от PoweredDevice и ISensor.
 */
class SmartOutlet : public PoweredDevice, public ISensor {
    double voltage; ///< Показание входного напряжения в вольтах.
public:
    /**
     * @brief Создаёт выключенную розетку.
     * @param name Имя розетки.
     * @param power Мощность подключённой нагрузки в ваттах.
     * @param voltage Входное напряжение в вольтах.
     * @throws invalid_argument Если мощность недопустима.
     */
    SmartOutlet(const string& name, double power, double voltage);
    /**
     * @brief Создаёт независимую копию состояния и параметров.
     * @param other Копируемый объект.
     */
    SmartOutlet(const SmartOutlet& other);
    /**
     * @brief Присваивает состояние и параметры другого объекта.
     * @param other Объект-источник.
     * @return Ссылка на текущий объект.
     * @details Самоприсваивание сохраняет объект без изменений.
     */
    SmartOutlet& operator=(const SmartOutlet& other);
    /**
     * @brief Реализует интерфейс датчика напряжения.
     * @return Сохранённое входное напряжение в вольтах, в том числе при выключенном реле.
     */
    double getCurrentVoltage() const override;
    /**
     * @brief Обновляет показание датчика.
     * @param value Входное напряжение в вольтах.
     */
    void setVoltage(double value);
    /**
     * @brief Формирует строку с типом, состоянием и параметрами устройства.
     * @return Строка состояния.
     */
    string getStatus() const override;
};
