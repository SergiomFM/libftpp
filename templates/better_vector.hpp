#include <vector>
#include <stdexcept>

#ifndef BETTER_VECTOR_HPP
#define BETTER_VECTOR_HPP

template<typename TType>
class better_vector : public std::vector<TType> {

    public:

        TType safe_pop(){

            if(this->empty())
                throw std::out_of_range("pop_back on empty vector");

            TType aux  = this->back();

            this->pop_back();
            return(aux);
        }
};

#endif