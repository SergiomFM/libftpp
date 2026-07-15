#include "libftpp.hpp"
#include <iostream>
#include <string>

// Simple predefined class for demonstration
class Person
{
public:
    int age;
    char initial;
    
    Person() : age(0), initial('A') {}
    Person(int a, char i) : age(a), initial(i) {}
};

int main()
{
    DataBuffer buffer;
    
    // Create 5 different variables with different types
    int count = 42;
    double temperature = 98.6;
    char grade = 'A';
    bool isActive = true;
    Person person(25, 'J');
    
    std::cout << "=== PUTTING DATA INTO BUFFER ===" << std::endl;
    std::cout << "Inserting:" << std::endl;
    std::cout << "  - int: " << count << std::endl;
    std::cout << "  - double: " << temperature << std::endl;
    std::cout << "  - char: " << grade << std::endl;
    std::cout << "  - bool: " << isActive << std::endl;
    std::cout << "  - Person: age=" << person.age << ", initial=" << person.initial << std::endl;
    
    // Put all variables into the buffer
    buffer << count << temperature << grade << isActive << person;
    
    std::cout << "\n=== EXTRACTING DATA FROM BUFFER ===" << std::endl;
    
    // Extract and print each variable
    int extracted_count;
    buffer >> extracted_count;
    std::cout << "Extracted:" << std::endl;
    std::cout << "  - int: " << extracted_count << std::endl;
    
    double extracted_temp;
    buffer >> extracted_temp;
    std::cout << "  - double: " << extracted_temp << std::endl;
    
    char extracted_grade;
    buffer >> extracted_grade;
    std::cout << "  - char: " << extracted_grade << std::endl;
    
    bool extracted_active;
    buffer >> extracted_active;
    std::cout << "  - bool: " << extracted_active << std::endl;
    
    Person extracted_person;
    buffer >> extracted_person;
    std::cout << "  - Person: age=" << extracted_person.age 
              << ", initial=" << extracted_person.initial << std::endl;
    
    std::cout << "\n=== TESTING ERROR CASES ===" << std::endl;
    
    // Test 1: Try to read from empty buffer
    std::cout << "\nTest 1: Attempting to read from empty buffer..." << std::endl;
    try
    {
        int dummy;
        buffer >> dummy;
        std::cout << "ERROR: Should have thrown exception!" << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    // Test 2: Try to read a larger variable than available in buffer
    std::cout << "\nTest 2: Attempting to read a large variable from limited buffer..." << std::endl;
    DataBuffer smallBuffer;
    smallBuffer << count;  // Put only one int
    
    try
    {
        int first;
        smallBuffer >> first;
        std::cout << "Successfully extracted first int: " << first << std::endl;
        
        // Now try to read another int from empty buffer
        int second;
        smallBuffer >> second;
        std::cout << "ERROR: Should have thrown exception!" << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    return 0;
}

