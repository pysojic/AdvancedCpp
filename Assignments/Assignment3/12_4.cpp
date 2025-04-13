#include <iostream>
#include <memory>

#include "factory.h"

using namespace cspp51045;

struct Locomotive
{
    Locomotive() 
        : m_TrainID{0}, m_HorsePower{0}
    {}
    Locomotive(size_t ID, size_t horsepower) 
        : m_TrainID{ID}, m_HorsePower{horsepower}
    {}
    virtual ~Locomotive() = default;

    virtual void start_engine() = 0;
    virtual void show_horsepower() const = 0;
    virtual void show_ID() const = 0;

protected:
    size_t m_TrainID;
    size_t m_HorsePower;
};

struct FreightCar
{
    FreightCar() 
        : m_Capacity{0}
    {}
    FreightCar(size_t capacity) 
        : m_Capacity{capacity}
    {}
    virtual ~FreightCar() = default;
    virtual void attach() = 0;
    virtual void show_capacity() const = 0;

    protected:
    size_t m_Capacity;
};

struct Caboose
{
    virtual ~Caboose() = default;
    virtual void clean() = 0;
};

struct ModelLocomotive : public Locomotive
{
    ModelLocomotive() : Locomotive()
    {}
    ModelLocomotive(size_t ID, size_t horsepower) : Locomotive(ID, horsepower)
    {}
    void show_horsepower() const override
    {
        std::cout << "This model train horsepower is: " << m_HorsePower << '\n';
    }
    void show_ID() const override
    {
        std::cout << "This model train ID is: " << m_TrainID << '\n';
    }
    void start_engine() override
    {
        std::cout << "Model locomotive engine started!" << std::endl;
    }
};

struct ModelFreightCar : public FreightCar
{
    ModelFreightCar() 
        : FreightCar()
    {}
    ModelFreightCar(size_t capacity) 
        : FreightCar(capacity)
    {}
    void attach() override
    {
        std::cout << "Model freight car attached!" << std::endl;
    }
    void show_capacity() const override
    {
        std::cout << "Model freight car capacity is: " << m_Capacity << std::endl;
    }
};

struct ModelCaboose : public Caboose
{
    void clean() override
    {
        std::cout << "Model caboose cleaned!" << std::endl;
    }
};

struct RealLocomotive : public Locomotive
{
    RealLocomotive() 
        : Locomotive()
    {}
    RealLocomotive(size_t ID, size_t horsepower) 
        : Locomotive(ID, horsepower)
    {}
    void show_horsepower() const override
    {
        std::cout << "This real train horsepower is: " << m_HorsePower << '\n';
    }
    void show_ID() const override
    {
        std::cout << "This real train ID is: " << m_TrainID << '\n';
    }
    void start_engine() override
    {
        std::cout << "Real locomotive engine started!" << std::endl;
    }
};

struct RealFreightCar : public FreightCar
{
    RealFreightCar() 
        : FreightCar()
    {}
    RealFreightCar(size_t capacity) 
        : FreightCar(capacity)
    {}
    void attach() override
    {
        std::cout << "Real freight car attached!" << std::endl;
    }
    void show_capacity() const override
    {
        std::cout << "Real freight car capacity is: " << m_Capacity << std::endl;
    }
};

struct RealCaboose : public Caboose
{
    void clean() override
    {
        std::cout << "Real caboose cleaned!" << std::endl;
    }
};

using AbstractTrainFactory = flexible_abstract_factory<Locomotive(size_t, size_t), FreightCar(size_t), Caboose()>;
using ModelTrainFactory = flexible_concrete_factory<AbstractTrainFactory, ModelLocomotive, ModelFreightCar, ModelCaboose>;
using RealTrainFactory = flexible_concrete_factory<AbstractTrainFactory, RealLocomotive, RealFreightCar, RealCaboose>;

int main()
{
    // Model Factory
    unique_ptr<AbstractTrainFactory> modelTrainFactory  = std::make_unique<ModelTrainFactory>();

    unique_ptr<FreightCar> freightCarModel(modelTrainFactory->create<FreightCar>(200ul));
    unique_ptr<Caboose> cabooseModel(modelTrainFactory->create<Caboose>());
    unique_ptr<Locomotive> locomotiveModel(modelTrainFactory->create<Locomotive>(0ul, 20ul));
    std::cout << "Model train: \n";
    freightCarModel->attach();
    freightCarModel->show_capacity();
    cabooseModel->clean();
    locomotiveModel->start_engine();
    locomotiveModel->show_ID();
    locomotiveModel->show_horsepower();
    
     // Real Factory
    unique_ptr<AbstractTrainFactory> realTrainfactory  = std::make_unique<RealTrainFactory>();

    unique_ptr<FreightCar> freightCarReal(realTrainfactory->create<FreightCar>(100ul));
    unique_ptr<Caboose> cabooseReal(realTrainfactory->create<Caboose>());
    unique_ptr<Locomotive> locomotiveReal(realTrainfactory->create<Locomotive>(1ul, 100ul));
    std::cout << "\nReal train: \n";
    freightCarReal->attach();
    freightCarReal->show_capacity();
    cabooseReal->clean();
    locomotiveReal->start_engine();
    locomotiveReal->show_ID();
    locomotiveReal->show_horsepower();
}