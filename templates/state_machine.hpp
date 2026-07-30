#ifndef	STATE_MACHINE_HPP
# define STATE_MACHINE_HPP

#include <vector>
#include <deque>
#include <functional>
#include <algorithm>
#include <iostream>

template<typename TState>

class StateMachine
{
    private:

        struct Transition {
            TState finalState;
            std::function<void()> action;

            Transition(): finalState(), action(nullptr) {};
            Transition(const TState& state, const std::function<void()>& lambda) : finalState(state), action(lambda) {}
        };

        struct State {
            TState state;
            std::function<void()> action;
            std::deque<Transition> transitions;

            State(): state(), action(nullptr) {};
            State(const TState& state) : state(state), action(nullptr) {}
        };


        std::deque<State> _states;
        State *_current_state;

      

        // Check if state already exists, throws exception if it does
        auto  _findState(const TState& state) {
            
            auto it = std::find_if(_states.begin(), _states.end(), [&state](const State& s) { return s.state == state; } ); ;

            if (it == _states.end())
                throw std::invalid_argument("State not found");
            return(it);
        }


            // Check if state already exists, throws exception if it does
        void  _stateAlreadyExists(const TState& state) {
            
            auto it = std::find_if(_states.begin(), _states.end(), [&state](const State& s) { return s.state == state; } ); ;

            if (it != _states.end())
                throw std::invalid_argument("State already exists");

        }

    public:

        StateMachine(): _current_state(nullptr) {}
        ~StateMachine() = default;
        StateMachine(const StateMachine&) = default;
        StateMachine& operator=(StateMachine&&) = default;


        //Adds a specific possible state to the object
        void addState(const TState& state){

            _stateAlreadyExists(state);
            _states.push_back(State(state));
            if ( _current_state == nullptr)
                _current_state = &_states.back();
        }

        //Specifies what to execute uppon a specific transition
        void addTransition(const TState& startState, const TState& finalState, const std::function<void()>& lambda)
        {
            auto it = _findState(startState);
            (void)_findState(finalState);
            it->transitions.push_back(Transition(finalState, lambda));
        }

        //Specifies what to execute when the StateMachine is in a specific state
        void addAction(const TState& state, const std::function<void()>& lambda)
        {
            auto it = _findState(state);
            it->action = lambda;
            
        }
        //Executes the transition to a specific state
        void transitionTo(const TState& state)
        {
            for(auto it = _current_state->transitions.begin(); it != _current_state->transitions.end(); it++)
            {
                if(it->finalState == state)
                {
                    if(it->action)
                        it->action();
                    else
                        throw std::invalid_argument("No action registered for this transition");
                }
            }
            _current_state = &(*(_findState(state)));
        }
        //Executes the action registred for the current state
        
        void update()
        {
            if (_current_state->action == nullptr)
                 throw std::invalid_argument("No action registered for current state");
            _current_state->action();
        }

};


#endif