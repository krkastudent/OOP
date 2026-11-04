/**
 * @file ISensor.h
 * @brief Объявление класса ISensor.
 */
#pragma once

/**
 * @brief Абстрактный интерфейс датчика напряжения.
 * @details Самостоятельный экземпляр интерфейса создать нельзя.
 */
class ISensor {
public:
    /**
     * @brief Обеспечивает удаление реализации через указатель ISensor.
     */
    virtual ~ISensor();
    /**
     * @brief Получает показание датчика.
     * @return Текущее входное напряжение в вольтах.
     */
    virtual double getCurrentVoltage() const = 0;
};
