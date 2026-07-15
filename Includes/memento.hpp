#include <vector>
#include <stdexcept>
#include "data_structures.hpp"


class Memento
{

    public:

    class Snapshot
    {
        private:

            DataBuffer _save_state;

        public:

        Snapshot() = default;
        ~Snapshot() = default;
        Snapshot(const Snapshot &snapshot) _save_state(snapshot._save_state){};
        Snapshot& operator=(const Snapshot &snapshot) = default;


    };

    protected:

    virtual void _saveToSnapshot(Memento::Snapshot& snapshot) = 0;
    virtual void _loadFromSnapshot(Memento::Snapshot&snapshot) = 0;


    public:

    Memento(){};
    virtual ~Memento() = 0;
    Memento(const Memento &memento) = delete;
    Memento& operator=(const Memento &memento) = delete;

    Snapshot Save(){
        Snapshot snapshot;
        _saveToSnapshot(snapshot);
        return(snapshot);
    };

    void load(const Memento::Snapshot& state){

        Snapshot snapshot = state;

        _loadFromSnapshot(snapshot);
    };
   
};

