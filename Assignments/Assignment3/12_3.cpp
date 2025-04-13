#include <iostream>
#include <memory>

#include "factory.h"

using namespace cspp51045;

struct Locomotive
{
    virtual void start_engine() = 0;
    virtual ~Locomotive() = default;
};

struct FreightCar
{
    virtual void attach() = 0;
    virtual ~FreightCar() = default;
};

struct Caboose
{
    virtual void clean() = 0;
    virtual ~Caboose() = default;
};

struct ModelLocomotive : public Locomotive
{
    void start_engine() override
    {
        std::cout << "Model locomotive engine started!" << std::endl;
    }
};

struct ModelFreightCar : public FreightCar
{
    void attach() override
    {
        std::cout << "Model freight car attached!" << std::endl;
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
    void start_engine() override
    {
        std::cout << "Real locomotive engine started!" << std::endl;
    }
};

struct RealFreightCar : public FreightCar
{
    void attach() override
    {
        std::cout << "Real freight car attached!" << std::endl;
    }
};

struct RealCaboose : public Caboose
{
    void clean() override
    {
        std::cout << "Real caboose cleaned!" << std::endl;
    }
};

using AbstractTrainFactory = abstract_factory<Locomotive, FreightCar, Caboose>;
using ModelTrainFactory = concrete_factory<AbstractTrainFactory, ModelLocomotive, ModelFreightCar, ModelCaboose>;
using RealTrainFactory = concrete_factory<AbstractTrainFactory, RealLocomotive, RealFreightCar, RealCaboose>;

int main()
{
    // Model Factory
    unique_ptr<AbstractTrainFactory> modelTrainFactory  = std::make_unique<ModelTrainFactory>();

    unique_ptr<FreightCar> freightCarModel(modelTrainFactory->create<FreightCar>());
    unique_ptr<Caboose> cabooseModel(modelTrainFactory->create<Caboose>());
    unique_ptr<Locomotive> locomotiveModel(modelTrainFactory->create<Locomotive>());
    std::cout << "Model train: \n";
    freightCarModel->attach();
    cabooseModel->clean();
    locomotiveModel->start_engine();
    
     // Real Factory
    unique_ptr<AbstractTrainFactory> realTrainfactory  = std::make_unique<RealTrainFactory>();

    unique_ptr<FreightCar> freightCarReal(realTrainfactory->create<FreightCar>());
    unique_ptr<Caboose> cabooseReal(realTrainfactory->create<Caboose>());
    unique_ptr<Locomotive> locomotiveReal(realTrainfactory->create<Locomotive>());
    std::cout << "\nReal train: \n";
    freightCarReal->attach();
    cabooseReal->clean();
    locomotiveReal->start_engine();
}