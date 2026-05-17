#pragma once
#include<exception>
#include<string>
#include<format>
#include <source_location>


class Exception : public std::exception {
    protected:
    std::string message;
    public:
    explicit Exception(const char* func_name,  const char* file_name, uint32_t line, const std::string& msg = "Неизвестная ошибка"): message(std::format("{} Функция: {} Файл: {}:{}", msg, func_name, file_name, line )){}
    const char* what() const noexcept override {
        return message.c_str();
    }
};


class IndexOutOfRange : public Exception{
    public:
    explicit IndexOutOfRange(int index, int size, const std::source_location& loc = std::source_location::current())
        : Exception(loc.function_name(), loc.file_name(), loc.line(), 
        std::format("Выход за границы! Индекс: {}, Размер: {}", index, size)){}

        explicit IndexOutOfRange(int index,  const std::source_location& loc = std::source_location::current())
        : Exception(loc.function_name(), loc.file_name(), loc.line(), std::format("Выход за границы! Индекс: {}",
        index)){}

        explicit IndexOutOfRange( const std::source_location& loc = std::source_location::current())
        : Exception(loc.function_name(), loc.file_name(), loc.line(), "Неверный индекс!"){}
};

class InvalidPointer : public Exception{
    public:
    explicit InvalidPointer( const std::source_location& loc = std::source_location::current())
        : Exception(loc.function_name(), loc.file_name(), loc.line(), "Ошибка: указатель не действителен!"){}
};

class ReadOnlyError : public Exception{
    public:
    explicit ReadOnlyError( const std::source_location& loc = std::source_location::current())
        : Exception(loc.function_name(), loc.file_name(), loc.line(), "Данные только для чтения!"){}
};

class InvalidEnumerator : public Exception{
    public:
    explicit InvalidEnumerator( const std::source_location& loc = std::source_location::current())
        : Exception(loc.function_name(), loc.file_name(), loc.line(), "Недопустимый элемент перечисления!"){}
};

class InvalidArgument : public Exception{
    public:
    explicit InvalidArgument( const std::source_location& loc = std::source_location::current())
        : Exception(loc.function_name(), loc.file_name(), loc.line(), "Недопустимый аргумент!"){}
};

class InvalidBitSequenceLength : public Exception{
    public:
    explicit InvalidBitSequenceLength( const std::source_location& loc = std::source_location::current())
        : Exception(loc.function_name(), loc.file_name(), loc.line(), "Длины битовых последовательностей должны быть равны!"){}
};


class EmptySequence : public Exception{
    public:
    explicit EmptySequence( const std::source_location& loc = std::source_location::current())
        : Exception(loc.function_name(), loc.file_name(), loc.line(), "Последовательность пуста!"){}
};