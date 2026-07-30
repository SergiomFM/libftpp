#ifndef	SINGLETON_HPP
# define SINGLETON_HPP

#include <memory>



// template<typename TType>

// class Singleton
//  {
//     private:
    

//      TType *_the_chosen_one = nullptr;

//     public:

//     Singleton(): _the_chosen_one(nullptr) {};
//     ~Singleton(){   
//         delete _the_chosen_one;
//     };
//     Singleton(const Singleton&) = delete;
//     Singleton& operator=(const Singleton&) = delete;


//     //Returns the managed instance of the TType classes

//     TType* instance(){

//         return(_the_chosen_one);
//     };


//     // Sets up the managed instance of the class. If the instance is already set, this method must throw an exception.
    
//     template<typename ... TArgs>

//     void instantiate(TArgs&&... p_args){
        
//        if(_the_chosen_one != nullptr){
//             throw std::runtime_error("Singleton Instance already exists");
//         }
//         _the_chosen_one = new TType(std::forward<TArgs>(p_args)...);

//     };

//  };


template<typename TType>

class Singleton
 {
    private:
    

    static inline std::unique_ptr<TType> _the_chosen_one = nullptr;

    public:

    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;


    //Returns the managed instance of the TType classes

    static TType* instance(){

        return(_the_chosen_one.get());
    };


    // Sets up the managed instance of the class. If the instance is already set, this method must throw an exception.
    
    template<typename ... TArgs>

    static void instantiate(TArgs&&... p_args){
        
       if(_the_chosen_one != nullptr){
            throw std::runtime_error("Singleton Instance already exists");
        }
        _the_chosen_one = std::unique_ptr<TType>(new TType(std::forward<TArgs>(p_args)...));

    };

 };

 #endif