#pragma once
#include<exception>
#include<string>


class Exception : public std::exception {
    protected:
    std::string message;
    public:
    explicit Exception(const std::string& msg = "Неизвестная ошибка"): message(msg){}
    const char* what() const noexcept override {
        return message.c_str();
    }
};


class IndexOutOfRange : public Exception{
    public:
    explicit IndexOutOfRange(int index, int size)
        : Exception("Выход за границы! Индекс: "
        + std::to_string(index) + ", Размер: " +  std::to_string(size)){}

        explicit IndexOutOfRange(int index)
        : Exception("Выход за границы! Индекс: "
        + std::to_string(index)){}

        explicit IndexOutOfRange()
        : Exception("Неверный индекс!"){}
};

class InvalidPointer : public Exception{
    public:
    explicit InvalidPointer()
        : Exception("Ошибка: указатель не действителен!"){}
};

class ReadOnlyError : public Exception{
    public:
    explicit ReadOnlyError()
        : Exception("Данные только для чтения!"){}
};

class InvalidEnumerator : public Exception{
    public:
    explicit InvalidEnumerator()
        : Exception("Недопустимый элемент перечисления!"){}
};



class EmptySequence : public Exception{
    public:
    explicit EmptySequence()
        : Exception("Последовательность пуста!"){}
};