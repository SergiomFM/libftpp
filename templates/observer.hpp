#ifndef	OBSERVER_HPP
# define OBSERVER_HPP


#include <vector>
#include <functional>

// An Observer class templated by TEvent, which allows users to
// subscribe to events and be notified when those specifics events
// are triggered.


template<typename TEvent>

 class Observer
 {
     private:
    
        std::vector<std::function<void()>> _subscribed_lambdas;
        std::vector<TEvent> _subscribed_events;


     
    
     public:

        Observer() = default;
        ~Observer() = default;
        Observer(const Observer&) = delete;
        Observer& operator=(const Observer&) = delete;

        //Subscribes a lambda to a specific event

       void subscribe(const TEvent& event, const std::function<void()>& lambda)
       {

            _subscribed_lambdas.push_back(lambda);
            _subscribed_events.push_back(event);
       };


       //executes all lambdas subscribed to the event.

       void notify(const TEvent& event)
       {
            for(size_t i = 0 ; i < _subscribed_events.size() ; i++)
            {
                if(_subscribed_events[i] == event)
                {
                    _subscribed_lambdas[i]();
                }
            }
       };


 };

 #endif