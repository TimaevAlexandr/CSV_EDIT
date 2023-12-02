// smartphon.h
#ifndef SMARTPHONE_H
#define SMARTPHONE_H

#include <QString>
#include <QtAlgorithms>

class Smartphone {
private:
    // Название
    QString name = "";
    // Модель
    QString model = "";
    // Производитель
    QString manufacturer = "";
    // Память
    QString memory = "";
    // Год выпуска
    QString year = "";

public:
    // Конструктор по умолчанию
    Smartphone();

    // Конструктор
    explicit Smartphone(QString name, QString model, QString manufacturer, QString memory, QString year);

    // Конструктор копирования
    Smartphone(const Smartphone &other);

    // Оператор копирования
    Smartphone &operator=(const Smartphone &other);

    // Конструктор перемещения
    Smartphone(Smartphone &&other) noexcept;

    // Оператор перемещения
    Smartphone &operator=(Smartphone &&other) noexcept;

    // Деструктор
    virtual ~Smartphone();

    // Оператор получения элемента по индексу I
    QString &operator[](int i);

    // Очистка массива
    void clear();

    // Оператор приведения к типу bool
    explicit operator bool();

    // Установка названия
    void setName(QString arg);

    // Получение названия
    const QString &getName();

    // Установка модели
    void setModel(QString arg);

    // Получение модели
    const QString &getModel();

    // Установка производителя
    void setManufacturer(QString arg);

    // Получение производителя
    const QString &getManufacturer();

    // Установка памяти
    void setMemory(QString arg);

    // Получение памяти
    const QString &getMemory();

    // Установка года выпуска
    void setYear(QString arg);

    // Получение года выпуска
    const QString &getYear();

    friend void swap(Smartphone &first, Smartphone &second) noexcept;

    // Класс итератора по аргументам
    class iterator {
    public:
        QString *i;
        typedef std::random_access_iterator_tag  iterator_category;
        typedef ptrdiff_t  difference_type;
        typedef QString value_type;
        typedef QString *pointer;
        typedef QString &reference;

        inline iterator() : i(nullptr) {}
        inline explicit iterator(QString *n) : i(n) {}
        inline iterator(const iterator &o): i(o.i){}
        inline QString &operator*() const { return *i; }
        inline QString *operator->() const { return i; }
        inline QString &operator[](int j) const { return i[j]; }
        inline bool operator==(const iterator &o) const { return i == o.i; }
        inline bool operator!=(const iterator &o) const { return i != o.i; }
        inline bool operator<(const iterator& other) const { return i < other.i; }
        inline bool operator<=(const iterator& other) const { return i <= other.i; }
        inline bool operator>(const iterator& other) const { return i > other.i; }
        inline bool operator>=(const iterator& other) const { return i >= other.i; }
        inline iterator &operator++() { ++i; return *this; }
        inline const iterator operator++(int) { QString *n = i; ++i; return iterator(n); }
        inline iterator &operator--() { i--; return *this; }
        inline const iterator operator--(int) { QString *n = i; i--; return iterator(n); }
        inline iterator &operator+=(int j) { i+=j; return *this; }
        inline iterator &operator-=(int j) { i-=j; return *this; }
        inline iterator operator+(int j) const { return iterator(i+j); }
        inline iterator operator-(int j) const { return iterator(i-j); }
        inline int operator-(iterator j) const { return int(i - j.i); }
    };

    inline typename Smartphone::iterator begin() { return iterator(&name); }
    inline typename Smartphone::iterator end() { return iterator(&year) + 1; }
};

#endif // SMARTPHONE_H
