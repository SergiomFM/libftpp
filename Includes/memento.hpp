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

        Snapshot();
        ~Snapshot();
        Snapshot(const Snapshot &snapshot);
        Snapshot& operator=(const Snapshot &snapshot);


    };

    protected:

    virtual void _saveToSnapshot(Memento::Snapshot& snapshot) = 0;
    virtual void _loadFromSnapshot(Memento::Snapshot&snapshot) = 0;


    public:

    Memento(){};
    virtual ~Memento() = 0;
    Memento(const Memento &memento) = delete;
    Memento& operator=(const Memento &memento) = delete;
    Snapshot Save();
    void load(const Memento::Snapshot& state);
   
};

