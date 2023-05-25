#include <IOC_Container.h>
#include <IProcessor.h>
#include <iostream>


int IOCContainer::s_nextTypeId = 115094801;

int main()
{
    // Пример через регистрацию уже готовой сущности
    // Создаем контейнер
    IOCContainer container_1;

    // Создаем сущность
    std::shared_ptr<IProcessor> amdProcessor = std::make_shared<AMDProcessor>();

    // Задаем информацию
    amdProcessor->SetProcessorInfo("Ryzen7", ProcessorType::x64, 5.3);

    // Регистрируем сущность - через вызов функции RegisterInstance
    container_1.RegisterInstance<IProcessor>(amdProcessor);

    // Создаем компьютер с процессором AMD из контейнера - зависимость от абстракции
    Computer testComputer(container_1.GetObject<IProcessor>().get());

    // Выводим информацию о процессоре для компьютера
    cout << "Computer 1 Processor Info: " << testComputer.ComputerProcessorInfo() << endl;

    // Сравним указатели, чтобы понять, что RegisterInstance использует готовый объект, а не создает новый
    if (container_1.GetObject<IProcessor>() == amdProcessor) {cout << "RegisterInstance uses AMDProcessor." << endl; }
    else {cout << "RegisterInstance creates new object AMDProcessor." << endl;}

    // Дополнительная проверка
    std::shared_ptr<IProcessor> amdProcessorTest12 = container_1.GetObject<IProcessor>();
    std::shared_ptr<IProcessor> amdProcessorTest22 = container_1.GetObject<IProcessor>();
    // Сравнение указателей, чтобы проверить, что это разные объекты
    if (amdProcessorTest12 != amdProcessorTest22)
    {
        cout << "RegisterInstance creates a new object for every GetObject function" << endl;
    } else
    {
        cout << "RegisterInstance uses the same object for every GetObject function" << endl;
    }

    cout << endl;

    //-----------------------------------------------------------------------------------------------------------
    // Можно отдать создание сущности контейнеру путем перегруженной функцией RegisterInstance
    // Создаем контейнер
    IOCContainer container_2;

    // Регистрируем сущность - через вызов перегруженной функции RegisterInstance
    container_2.RegisterInstance<IProcessor, IntelProcessor>();

    // Берем процессор из контейнера и устанавливаем информацию
    container_2.GetObject<IProcessor>()->SetProcessorInfo("Core i9", ProcessorType::x64, 3.8);

    // Создаем компьютер с процессором
    Computer testComputer2(container_2.GetObject<IProcessor>().get());

    // Выводим информацию о процессоре для компьютера
    cout << "Computer 2 Processor Info: " << testComputer.ComputerProcessorInfo() << endl << endl;


    //-----------------------------------------------------------------------------------------------------------
    // Другой пример - через регистрацию фабрики
    // Создаем контейнер
    IOCContainer container_3;

    // Регистрируем фабрики для процессоров - компьютеры на базе Intel
    container_3.RegisterFactory<IProcessor, IntelProcessor>();

    // Получаем экземпляры процессоров из контейнера
    std::shared_ptr<IProcessor> intelProcessor2 = container_3.GetObject<IProcessor>();

    // Устанавливаем информацию о процессорах
    intelProcessor2->SetProcessorInfo("Core i9", ProcessorType::x64, 3.8);

    // Создаем компьютер c процессором AMD
    Computer test_computer3(intelProcessor2.get());

    // Выводим информацию о процессоре компьютера
    cout << "Computer 3 Processor Info: " << test_computer3.ComputerProcessorInfo() << endl;

    // Устанавливаем новый процессор - процессор AMD в компьютер, регистрируем фабрику
    container_3.RegisterFactory<IProcessor, AMDProcessor>();

    // Получаем экземпляры процессоров из контейнера
    std::shared_ptr<IProcessor> amdProcessor2 = container_3.GetObject<IProcessor>();

    // Устанавливаем информацию о процессоре
    amdProcessor2->SetProcessorInfo("Ryzen7", ProcessorType::x64, 5.3);

    // Устанавливаем новый процессор в компьютер
    test_computer3.InstallProcessor(amdProcessor2.get());

    // Выводим обновленную информацию о процессоре компьютера
    cout << "Computer 3 Processor Info: " << test_computer3.ComputerProcessorInfo() << endl;

    // Таким образом при работе через фабрику мы должны получать экземпляр класса из контейнера
    // Проверка работы фабрики:

    std::shared_ptr<IProcessor> amdProcessorTest1 = container_3.GetObject<IProcessor>();
    std::shared_ptr<IProcessor> amdProcessorTest2 = container_3.GetObject<IProcessor>();

    // Сравнение указателей, чтобы проверить, что это разные объекты
    if (amdProcessorTest1 != amdProcessorTest2)
    {
        cout << "RegisterFactory creates a new object for every GetObject function" << endl;
    } else
    {
        cout << "RegisterFactory uses the same object for every GetObject function" << endl;
    }

}
