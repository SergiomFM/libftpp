#ifndef	STATE_MACHINE_HPP
# define STATE_MACHINE_HPP

template<typename TState>

class StateMachine
{
    private:

        

    public:

        StateMachine(){};

        ~StateMachine(){};


        //Adds a specific possible state to the object
        void addState(const TState& state){

        }

        //Specifies what to execute uppon a specific transition
        void addTransition(const TState& startState, const TState& finalState, const std::function<void()>& lambda)
        {

        }

        //Specifies what to execute when the StateMachine is in a specific state
        void addAction(const TState& state, const std::function<void()>& lambda)
        {

        }
        //Executes the transition to a specific state
        void transitionTo(const TState& state)
        {

        }
        //Executes the action registred for the current state
        void update()
        {
            
        }

};


#endif