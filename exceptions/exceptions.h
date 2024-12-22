#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

// Базовый класс для пользовательских исключений
class IException : public std::exception {
public:
    explicit IException(std::string message) : message{std::move(message)} {}
    
    // Переопределяем метод what() из std::exception
    virtual const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

// Исключение для отсутствия способностей
class NoAbilitiesException : public IException {
public:
    explicit NoAbilitiesException(const std::string& message) 
        : IException( "NoAbilitiesException: " + message) {}
};

// Исключение для размещения корабля
class ShipPlacementException : public IException {
public:
    explicit ShipPlacementException(const std::string& message) 
        : IException("ShipPlacementException: " + message) {}
};

// Исключение для выхода за границы
class OutOfBoundsException : public IException {
public:
    explicit OutOfBoundsException(const std::string& message) 
        : IException("OutOfBoundsException: " + message) {}
};

// исклчение для обработки событий
class EventHandler : public IException {
public:
    explicit EventHandler(const std::string& message) 
        : IException("EventHandler: " + message) {}
};

class AlreadyAttackedException : public IException{
        explicit AlreadyAttackedException(const std::string& message) 
        : IException("AlreadyAttackedException: " + message) {}
};



#endif 
