// Author: Lucas Oliveira Vilas-Bôas
// Year: 2022
// Repository: https://github.com/lucoiso/CppExamples

#include <iostream>
#include <functional>

template<typename ArgTy, typename ...Args>
constexpr void callFunctorParam_T(const ArgTy& arg, Args&& ...args)
{
    arg(std::forward<Args>(args)...);
}

void callFunctorParam(std::function<void(const std::string&)> functor)
{
    functor("Example 3");
}

template<typename ObjectType, typename FunctorType, typename ...Args>
constexpr void callFunctorParamFromObject(const ObjectType& object, const FunctorType& functor, Args&& ...args)
{
    if constexpr (std::is_pointer<ObjectType>::value)
    {
        (object->*functor)(std::forward<Args>(args)...);
    }
    else
    {
        (&object->*functor)(std::forward<Args>(args)...);
    }
}

class ExampleClass
{
public:
    constexpr ExampleClass() = delete;
    constexpr ExampleClass(const std::string& object_name) : m_object_name(object_name) {}

    constexpr ~ExampleClass() = default;

    void printFromClass() const
    {
        std::cout << m_object_name << std::endl;
    } 

private:
    std::string m_object_name;
};

int main()
{
    { // Calling a lambda without param
        constexpr auto Example_1 = []
        {
            std::cout << "Example 1" << std::endl;
        };

        callFunctorParam_T(Example_1);
    }

    { // Calling a lambda with params
        constexpr auto Example_2 = [](const std::string& output_str)
        {
            std::cout << output_str << std::endl;
        };

        callFunctorParam_T(Example_2, "Example 2");
    }

    { // Calling a lambda with params without using a template
        constexpr auto Example_3 = [](const std::string& output_str)
        {
            std::cout << output_str << std::endl;
        };

        callFunctorParam(Example_3);
    }

    { // Call a function from an object
        const ExampleClass Example_4("Example 4");
        callFunctorParamFromObject(Example_4, &ExampleClass::printFromClass);

        const ExampleClass* const Example_5 = new ExampleClass("Example 5");
        callFunctorParamFromObject(Example_5, &ExampleClass::printFromClass);

        delete Example_5;
    }

    return 0;
}