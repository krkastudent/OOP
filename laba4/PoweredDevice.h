/**
 * @file PoweredDevice.h
 * @brief Объявление класса PoweredDevice.
 */
#pragma once
#include "SmartDevice.h"
#include <chrono>

using namespace std;

/**
 * @brief Абстрактное устройство с питанием: второй уровень иерархии.
 * @details Реализует включение, выключение и общую статистику расхода энергии.
 * Остаётся абстрактным, поскольку getStatus() не реализован.
 */
class PoweredDevice : public SmartDevice {
protected:
    double powerConsumption; ///< Номинальная мощность в ваттах.

    /**
     * @brief Создаёт устройство с заданной номинальной мощностью.
     * @param name Имя устройства.
     * @param powerConsumption Положительная конечная мощность в ваттах.
     * @throws invalid_argument Если мощность неположительная или не является конечной.
     */
    PoweredDevice(const string& name, double powerConsumption);

    /**
     * @brief Создаёт независимую копию состояния и параметров.
     * @param other Копируемый объект.
     * @details Копирует включён/выключен, но начинает собственный отсчёт времени, не повторяя
     * прошлый расход.
     */
    PoweredDevice(const PoweredDevice& other);

    /**
     * @brief Присваивает состояние и параметры другого объекта.
     * @param other Объект-источник.
     * @return Ссылка на текущий объект.
     * @details Самоприсваивание сохраняет объект без изменений.
     * Перед заменой параметров учитывает старый расход приёмника. Новый отсчёт начинается сейчас.
     */
    PoweredDevice& operator=(const PoweredDevice& other);

private:
    chrono::steady_clock::time_point started; ///< Начало текущего интервала работы.
    double sessionPower;                      ///< Мощность в ваттах, зафиксированная при включении.
    static double totalEnergyConsumed;        ///< Общий учтённый расход в кВт·ч для всех устройств.

public:
    /**
     * @brief Учитывает оставшийся расход при уничтожении устройства.
     */
    ~PoweredDevice() override;

    /**
     * @brief Включает устройство и запоминает время и текущую мощность.
     * @details Повторное включение не сбрасывает начатый интервал.
     */
    void turnOn() override;

    /**
     * @brief Выключает устройство и добавляет расход в общий счётчик.
     * @details Энергия в кВт·ч = мощность в Вт * секунды / 3600000.
     * Повторное выключение не прибавляет энергию снова.
     */
    void turnOff() override;

    /**
     * @brief Возвращает мощность по умолчанию.
     * @return Номинальная мощность в ваттах при включении, иначе 0.
     */
    virtual double getPowerUsage() const;

    /**
     * @brief Возвращает общий учтённый расход всех устройств.
     * @return Энергия завершённых интервалов работы в кВт·ч.
     * @details Значение общее для всех наследников в одном процессе. При запуске равно нулю.
     */
    static double getTotalEnergyConsumed();
};
