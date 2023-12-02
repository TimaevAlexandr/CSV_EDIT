// smartphon.cpp
#include "smartphone.h"
#include <QtAlgorithms>

// Конструктор по умолчанию
Smartphone::Smartphone() {}

// Конструктор
Smartphone::Smartphone(QString name, QString model, QString manufacturer, QString memory, QString year)
    : name(name), model(model), manufacturer(manufacturer), memory(memory), year(year) {
}

// Конструктор копирования
Smartphone::Smartphone(const Smartphone &other) : Smartphone(other.name, other.model, other.manufacturer, other.memory, other.year) {}

// Оператор копирования
Smartphone &Smartphone::operator=(const Smartphone &other) {
    Smartphone temp(other);
    swap(*this, temp);
    return *this;
}

// Конструктор перемещения
Smartphone::Smartphone(Smartphone &&other) noexcept {
    name = std::move(other.name);
    model = std::move(other.model);
    manufacturer = std::move(other.manufacturer);
    memory = std::move(other.memory);
    year = std::move(other.year);
}

// Оператор перемещения
Smartphone &Smartphone::operator=(Smartphone &&other) noexcept {
    if (this != &other) {
        swap(*this, other);
        other.clear();
    }
    return *this;
}

// Деструктор
Smartphone::~Smartphone() {
    // Вызывается автоматически при удалении объекта
}

// Оператор получения элемента по индексу I
QString &Smartphone::operator[](int i) {
    switch (i) {
    case 0: return name;
    case 1: return model;
    case 2: return manufacturer;
    case 3: return memory;
    case 4: return year;
    default: throw std::out_of_range("Index out of range");
    }
}

// Очистка массива
void Smartphone::clear() {
    name = model = manufacturer = memory = year = "";
}

// Оператор приведения к типу bool
Smartphone::operator bool() {
    return !name.isEmpty() || !model.isEmpty() || !manufacturer.isEmpty() || !memory.isEmpty() || !year.isEmpty();
}

// Установка названия
void Smartphone::setName(QString arg) {
    name = arg;
}

// Получение названия
const QString &Smartphone::getName() {
    return name;
}

// Установка модели
void Smartphone::setModel(QString arg) {
    model = arg;
}

// Получение модели
const QString &Smartphone::getModel() {
    return model;
}

// Установка производителя
void Smartphone::setManufacturer(QString arg) {
    manufacturer = arg;
}

// Получение производителя
const QString &Smartphone::getManufacturer() {
    return manufacturer;
}

// Установка памяти
void Smartphone::setMemory(QString arg) {
    memory = arg;
}

// Получение памяти
const QString &Smartphone::getMemory() {
    return memory;
}





// Установка года выпуска
void Smartphone::setYear(QString arg) {
    year = arg;
}

// Получение года выпуска
const QString &Smartphone::getYear() {
    return year;
}

void swap(Smartphone &first, Smartphone &second) noexcept {
    using std::swap;
    swap(first.name, second.name);
    swap(first.model, second.model);
    swap(first.manufacturer, second.manufacturer);
    swap(first.memory, second.memory);
    swap(first.year, second.year);
}
