#ifndef	MEMENTO_HPP
# define MEMENTO_HPP

#include "data_structures.hpp"

template<typename TType>

class Memento: public TType
{
    private:

        DataBuffer _state;
        
        void _saveToSnapshot(Memento::Snapshot& snapshot);
        void _loadFromSnapshot(Memento::Snapshot& snapshot);
    public:

        class Snapshot
        {
            friend class Memento;

            private:

                DataBuffer _snapshot_state;

            public:

                Snapshot(const DataBuffer& state) : _snapshot_state(state) {}


        };

        Snapshot save();
        void load(const Memento::Snapshot& state);
};

#endif