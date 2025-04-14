#ifndef FACTORY_H
#define FACTORY_H

#include<tuple>
#include<memory>

using std::tuple;
using std::unique_ptr;
using std::make_unique;
#pragma warning(disable : 4250)

namespace cspp51045 
{
template<typename T>
struct TT 
{};

template<typename T>
struct abstract_creator
{
    virtual unique_ptr<T> doCreate(TT<T>&&) = 0;
};

template<typename... Ts>
struct abstract_factory 
	: public abstract_creator<Ts>... 
{
	template<class U> 
	unique_ptr<U> create() 
	{
		abstract_creator<U> &creator = *this;
		return creator.doCreate(TT<U>());
	}
	virtual ~abstract_factory() = default;
};

template<typename AbstractFactory, typename Abstract, typename Concrete>
struct concrete_creator 
	: virtual public AbstractFactory 
{
	unique_ptr<Abstract> doCreate(TT<Abstract> &&) override 
	{
		return make_unique<Concrete>();
	}
};

template<typename AbstractFactory, typename... ConcreteTypes>
struct concrete_factory;

template<typename... AbstractTypes, typename... ConcreteTypes>
struct concrete_factory<abstract_factory<AbstractTypes...>, ConcreteTypes...> 
	: public concrete_creator<abstract_factory<AbstractTypes...>, 
	                        AbstractTypes, ConcreteTypes>... 
{};

// ------- Assignment 12_4 ---------

template<typename Signature>
struct flexible_abstract_creator;

template<typename T, typename... Args>
struct flexible_abstract_creator<T(Args...)> 
{
    virtual unique_ptr<T> doCreate(TT<T>, Args&&... args) = 0;
};

template<typename... Signatures>
struct flexible_abstract_factory : public flexible_abstract_creator<Signatures>... 
{
    template<typename U, typename... Args>
    unique_ptr<U> create(Args&&... args) 
	{
        flexible_abstract_creator<U(Args...)>& creator = *this;
        return creator.doCreate(TT<U>{}, std::forward<Args>(args)...);
    }

    virtual ~flexible_abstract_factory() = default;
};

template<typename AbstractFactory, typename Abstract, typename Concrete, typename Signature>
struct flexible_concrete_creator;

template<typename AbstractFactory, typename Abstract, typename Concrete, typename... Args>
struct flexible_concrete_creator<AbstractFactory, Abstract, Concrete, Abstract(Args...)>
    : virtual public AbstractFactory
{
    unique_ptr<Abstract> doCreate(TT<Abstract>, Args&&... args) override 
	{
        return make_unique<Concrete>(std::forward<Args>(args)...);
    }
};

template<typename Signature>
struct product_type;

template<typename T, typename... Args>
struct product_type<T(Args...)> 
{
    using type = T;
};

template<typename T>
struct product_type 
	: product_type<T()> {};

template<typename AbstractFactory, typename... ConcreteTypes>
struct flexible_concrete_factory;

template<typename... AbstractSignatures, typename... ConcreteTypes>
struct flexible_concrete_factory<flexible_abstract_factory<AbstractSignatures...>, ConcreteTypes... >
    : public flexible_concrete_creator<
           flexible_abstract_factory<AbstractSignatures...>,
           typename product_type<AbstractSignatures>::type,
           ConcreteTypes,
           AbstractSignatures>...
{};

}
#endif
