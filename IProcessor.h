#ifndef IPROCESSOR_H
#define IPROCESSOR_H

#include <iostream>

// В перечислении по условию задачи два типа процессоров
enum ProcessorType
{
   x86 = 86,
   x64 = 64
};

// Создаем абстрактный класс - процессор
class IProcessor
{
public:

    IProcessor(){}

    std::string GetProcessorInfo()
    {
        return "Processor by " + Version + ", Speed:" + std::to_string(Speed) + ", ProcessorType:" + 'x' + std::to_string(Type);
    }

    void SetProcessorInfo(std::string version, ProcessorType type, double speed)
    {
        Version = version;
        Type = type;
        Speed = speed;
    }

    virtual ~IProcessor() = default;


protected:
    std::string Version;
    ProcessorType Type;
    double Speed;
};

// Конкретные классы AMDProcessor и IntelProcessor
class AMDProcessor : public IProcessor{};
class IntelProcessor : public IProcessor {};

// Класс компьютер включающий в себя процессор
class Computer
{
public:
    Computer(IProcessor *new_processor)
    {
        processor = new_processor;
    }

    void InstallProcessor(IProcessor *new_processor)
    {
        processor = new_processor;
    }

    std::string ComputerProcessorInfo()
    {
        return processor->GetProcessorInfo();
    }

    ~Computer() = default;

private:
    IProcessor *processor;
};



#endif // IPROCESSOR_H
