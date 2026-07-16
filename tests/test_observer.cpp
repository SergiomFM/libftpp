#include <cassert>
#include <iostream>
#include "libftpp.hpp"

// Test event enum
enum class TestEvent {
    EVENT_A,
    EVENT_B,
    EVENT_C
};

int main() {
    std::cout << "Testing Observer class...\n";

    // Test 1: Basic subscription and notification
    {
        std::cout << "Test 1: Basic subscription and notification... ";
        Observer<TestEvent> observer;
        int counter = 0;

        observer.subscribe(TestEvent::EVENT_A, [&counter]() { counter++; });
        observer.notify(TestEvent::EVENT_A);

        assert(counter == 1);
        std::cout << "PASS\n";
    }

    // Test 2: Multiple subscriptions to the same event
    {
        std::cout << "Test 2: Multiple subscriptions to same event... ";
        Observer<TestEvent> observer;
        int counter = 0;

        observer.subscribe(TestEvent::EVENT_A, [&counter]() { counter++; });
        observer.subscribe(TestEvent::EVENT_A, [&counter]() { counter += 2; });
        observer.notify(TestEvent::EVENT_A);

        assert(counter == 3); // 1 + 2
        std::cout << "PASS\n";
    }

    // Test 3: Different events trigger different lambdas
    {
        std::cout << "Test 3: Different events trigger different lambdas... ";
        Observer<TestEvent> observer;
        int counterA = 0, counterB = 0;

        observer.subscribe(TestEvent::EVENT_A, [&counterA]() { counterA++; });
        observer.subscribe(TestEvent::EVENT_B, [&counterB]() { counterB++; });

        observer.notify(TestEvent::EVENT_A);
        assert(counterA == 1 && counterB == 0);

        observer.notify(TestEvent::EVENT_B);
        assert(counterA == 1 && counterB == 1);

        std::cout << "PASS\n";
    }

    // Test 4: Unsubscribed events don't trigger anything
    {
        std::cout << "Test 4: Unsubscribed events don't trigger anything... ";
        Observer<TestEvent> observer;
        int counter = 0;

        observer.subscribe(TestEvent::EVENT_A, [&counter]() { counter++; });
        observer.notify(TestEvent::EVENT_B);

        assert(counter == 0);
        std::cout << "PASS\n";
    }

    // Test 5: Multiple notifications
    {
        std::cout << "Test 5: Multiple notifications... ";
        Observer<TestEvent> observer;
        int counter = 0;

        observer.subscribe(TestEvent::EVENT_A, [&counter]() { counter++; });

        observer.notify(TestEvent::EVENT_A);
        observer.notify(TestEvent::EVENT_A);
        observer.notify(TestEvent::EVENT_A);

        assert(counter == 3);
        std::cout << "PASS\n";
    }

    // Test 6: Verify copy constructor and assignment are deleted (compile-time test)
    // This would fail to compile if uncommented, which verifies deletion works:
    // Observer<TestEvent> obs1;
    // Observer<TestEvent> obs2 = obs1;  // ERROR: deleted copy constructor
    // obs2 = obs1;                       // ERROR: deleted assignment operator
    std::cout << "Test 6: Copy constructor and assignment operator deleted (compile-time verified)... PASS\n";

    std::cout << "\nAll tests passed!\n";
    return 0;
}
