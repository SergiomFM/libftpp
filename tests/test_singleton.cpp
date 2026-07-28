#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include "singleton.hpp"

struct MoveOnlyValue
{
    std::unique_ptr<int> value;

    explicit MoveOnlyValue(std::unique_ptr<int> p_value)
        : value(std::move(p_value))
    {
    }

    MoveOnlyValue(const MoveOnlyValue&) = delete;
    MoveOnlyValue& operator=(const MoveOnlyValue&) = delete;
};

struct TwoArgumentValue
{
    int number;
    std::string label;

    TwoArgumentValue(int p_number, std::string p_label)
        : number(p_number), label(std::move(p_label))
    {
    }
};

int main()
{
    std::cout << "Testing Singleton class...\n";

    {
        std::cout << "Test 1: Initial instance is null... ";
        Singleton<MoveOnlyValue> singleton;

        assert(singleton.instance() == nullptr);
        std::cout << "PASS\n";
    }

    {
        std::cout << "Test 2: Instantiation with move-only argument... ";
        Singleton<MoveOnlyValue> singleton;

        singleton.instantiate(std::make_unique<int>(42));
        assert(singleton.instance() != nullptr);
        assert(singleton.instance()->value != nullptr);
        assert(*singleton.instance()->value == 42);
        std::cout << "PASS\n";
    }

    {
        std::cout << "Test 3: Second instantiation throws... ";
        Singleton<MoveOnlyValue> singleton;

        bool threw = false;

        singleton.instantiate(std::make_unique<int>(7));

        try
        {
            singleton.instantiate(std::make_unique<int>(9));
        }
        catch (const std::runtime_error& e)
        {
            threw = true;
            std::cout << "Caught exception: " << e.what() << std::endl;
            assert(std::string(e.what()) == "Singleton Instance already exists");
        }

        assert(threw);
        std::cout << "PASS\n";
    }

    {
        std::cout << "Test 4: Multiple constructor arguments are forwarded... ";
        Singleton<TwoArgumentValue> singleton;

        singleton.instantiate(123, std::string("singleton"));

        assert(singleton.instance() != nullptr);
        assert(singleton.instance()->number == 123);
        assert(singleton.instance()->label == "singleton");
        std::cout << "PASS\n";
    }

    std::cout << "\nAll Singleton tests passed!\n";
    return 0;
}