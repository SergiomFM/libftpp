#include "libftpp.hpp"
#include <iostream>

class example{

    private:

        int _secretNumber;
        void *_something_allocated;

    public:

        std::string name;


        example(): name("unknown"){
            std::cout << name << " has been created" <<std::endl;

        };
        example(const std::string& nname):name(nname){
            std::cout << name << " has been created" <<std::endl;
        };
        ~example(){
           std::cout << name << " has been destroyed" <<std::endl;
        };


}
;

static void int_test(void)
{
    std::cout << "=== Int Test ===" << std::endl;

    Pool<int> pool(5);

    std::cout << "Current Pool Size is 5 " << std::endl;
    Pool<int>::Object first = pool.acquire();
    std::cout << "First: " << first.operator->() << std::endl;
    Pool<int>::Object second = pool.acquire();
    std::cout << "Second: " << second.operator->() << std::endl;
    Pool<int>::Object third = pool.acquire();
    std::cout << "Third: " << third.operator->() << std::endl;
    Pool<int>::Object fourth = pool.acquire();
    std::cout << "Fourth: " << fourth.operator->() << std::endl;
    Pool<int>::Object fifth = pool.acquire();
    std::cout << "Fifth: " << fifth.operator->() << std::endl;
    Pool<int>::Object imp_sixt = pool.acquire();
    std::cout << "Imposible Sixth: " << imp_sixt.operator->() << std::endl;

    pool.resize(5);
    std::cout << "pool.resize() was called " << std::endl;
    std::cout << "Current Pool Size is 10 " << std::endl;
    Pool<int>::Object sixt = pool.acquire();
    std::cout << "Sixth: " << sixt.operator->() << std::endl;
    Pool<int>::Object seven = pool.acquire();
    std::cout << "Seventh: " << seven.operator->() << std::endl;
    Pool<int>::Object eight = pool.acquire();
    std::cout << "Eighth: " << eight.operator->() << std::endl;
    Pool<int>::Object ninth = pool.acquire();
    std::cout << "Ninth: " << ninth.operator->() << std::endl;
    Pool<int>::Object tenth = pool.acquire();
    std::cout << "Tenth: " << tenth.operator->() << std::endl;
    Pool<int>::Object eleventh = pool.acquire();
    std::cout << "Eleventh: " << eleventh.operator->() << std::endl;

    std::cout << "=== Test Int Memory Alocations ===" << std::endl;

    for(unsigned int i = 0; i < 100000; i++)
    {
        Pool<int>::Object temp = pool.acquire();
    }

    std::cout << "=== Int Test End ===" << std::endl;
}

static void class_test(void)
{
    std::cout << "=== Class Test ===" << std::endl;

    Pool<example> pool(5);

    std::cout << "Current Pool Size is 5 " << std::endl;
    Pool<example>::Object first = pool.acquire("First");
    std::cout << "First: " << first->name << std::endl;
    Pool<example>::Object second = pool.acquire("Second");
    std::cout << "Second: " << second->name << std::endl;
    Pool<example>::Object third = pool.acquire("Third");
    std::cout << "Third: " << third->name << std::endl;
    Pool<example>::Object fourth = pool.acquire("Fourth");
    std::cout << "Fourth: " << fourth->name << std::endl;
    Pool<example>::Object fifth = pool.acquire("Fifth");
    std::cout << "Fifth: " << fifth->name << std::endl;
    Pool<example>::Object imp_sixt = pool.acquire("Impossible Sixth");
    std::cout << "Impossible Sixth pointer: " << imp_sixt.operator->() << std::endl;

    pool.resize(5);
    std::cout << "pool.resize() was called " << std::endl;
    std::cout << "Current Pool Size is 10 " << std::endl;
    Pool<example>::Object sixt = pool.acquire("Sixth");
    std::cout << "Sixth: " << sixt->name << std::endl;
    Pool<example>::Object seven = pool.acquire("Seventh");
    std::cout << "Seventh: " << seven->name << std::endl;
    Pool<example>::Object eight = pool.acquire("Eighth");
    std::cout << "Eighth: " << eight->name << std::endl;
    Pool<example>::Object ninth = pool.acquire("Ninth");
    std::cout << "Ninth: " << ninth->name << std::endl;
    Pool<example>::Object tenth = pool.acquire("Tenth");
    std::cout << "Tenth: " << tenth->name << std::endl;
    Pool<example>::Object eleventh = pool.acquire("Eleventh");
    std::cout << "Eleventh pointer: " << eleventh.operator->() << std::endl;


    std::cout << "=== Class Test End ===" << std::endl;
}

int main(void)
{
    std::cout << "=== Pool Test ===" << std::endl;
    
    int_test();
    class_test();

    std::cout << "=== Pool Test End ===" << std::endl;

   
    
   
    return(0);
}