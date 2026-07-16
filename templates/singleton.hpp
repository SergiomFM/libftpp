#ifndef	OBSERVER_HPP
# define OBSERVER_HPP




// Ensures that a templated TType class has only one instance and provides a way to access it


template<typename TType>

class Singleton
 {
     private:
    

    static TType *_the_chosen_one;
    
    
     public:

    Singleton() = default;
    ~Singleton(){   
        if(_the_chosen_one != nullptr)
            delete _the_chosen_one;
    };
    Singleton(const Singleton&) = default;
    Singleton& operator=(const Singleton&) = default;


    //Returns the managed instance of the TType classes

    TType* instance(){
        
        return(_the_chosen_one);   
    };


    // Sets up the managed instance of the class. If the instance is already set, this method must throw an exception.
    
    template<typename ... TArgs>

    void instantiate(TArgs&& p_args){
        
        if(_the_chosen_one != nullptr)
            throw std::runtime_error("Singleton: Instance already exists");
        
        _the_chosen_one = new TType(std::forward<TArgs>(p_args)...);

    };

 };

 #endif