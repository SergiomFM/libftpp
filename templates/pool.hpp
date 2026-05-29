
#include "better_vector.hpp"
#include <algorithm>

#ifndef POOL_HPP
#define POOL_HPP

template<typename TType>


class Pool{

    private:

    better_vector<TType *>   _avaliable_types;
    better_vector<TType *>   _used_types;


    public:

        Pool(){};

        Pool(const size_t& numberOfObjectStored){

            for(size_t i = 0 ; i < numberOfObjectStored ; i++)
            {
                _avaliable_types.push_back((TType *)malloc(sizeof(TType)));
            }

        };

        
        void resize(const size_t& numberOfObjectStored){

            for(size_t i = 0 ; i < numberOfObjectStored ; i++)
            {
                _avaliable_types.push_back((TType *)malloc(sizeof(TType)));
            }
        };

        ~Pool(){

            for(size_t i = 0 ; i < _avaliable_types.size(); i++)
            {
                free(_avaliable_types[i]);
            }
            for(size_t i = 0 ; i <  _used_types.size() ; i++)
            {
                delete (_used_types[i]);
            }

        };
        

        class Object
        {
            friend class Pool;

            private:

                TType   *_type;
                Pool    &_owner;

            public:

                Object() = delete;
                Object(const Object&) = delete;
                Object& operator=(const Object&) = delete;
                
                Object(TType *type, Pool &owner): _type(type), _owner(owner) {};

                ~Object(){

                    if(_type)
                    {
                        _type->~TType();
                        _owner._used_types.erase(std::remove(_owner._used_types.begin(), _owner._used_types.end(), _type), _owner._used_types.end());
                        _owner._avaliable_types.push_back(_type);
                    }
                };

                
                TType* operator->()
                {
                    return _type;
                }
            };
        

        template<typename ... TArgs>

        Object acquire(TArgs&&... p_args){

            if(_avaliable_types.empty())
                return Object(NULL, *this);

            TType *aux= _avaliable_types.safe_pop();
            new(aux) TType(std::forward<TArgs>(p_args)...);
            _used_types.push_back(aux);
            return Object(aux, *this);
        };

};

#endif