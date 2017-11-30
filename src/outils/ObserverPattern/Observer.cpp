/**
 * @file Observer.cpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 11 nov. 2017
 *  @author nihil
 */
#include <iostream>
#include <typeinfo>
#include <any>

#ifdef OBSERVER_HPP
//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------
template<class EventName, class Content>
void Observer::addAction(EventName eventName,
    EventAction<Content> actionMethod)
{
  using namespace std;
  actionNames.push_back(eventName);
  actions.push_back(actionMethod);
}

template<class EventName>
void Observer::addAction(EventName eventName, SingleEventAction actionMethod)
{
  singleActionNames.push_back(eventName);
  singleActions.push_back(actionMethod);
}


template<class EventName, class Content>
void Observer::doEventActions(EventName eventName, Content content,
    Observed const& observed) const
{
  using namespace std;
  using opAny::operator ==;
  for (uint i = 0; i < actionNames.size(); ++i)
  {
    if (actionNames[i] == eventName)
    {
      try
      {
        auto const& f = any_cast<EventAction<Content>>(actions[i]);
        f(content, observed);
      }
      catch (std::bad_any_cast& e)
      {
        throw BadActionMethod(typeid(Content).name(), actions[i].type().name());
      }
    }
  }
}

template<class EventName>
void Observer::doEventActions(EventName eventName, Observed const & observed) const
{
  using namespace std;
  using opAny::operator ==;
  for (uint i = 0; i < singleActionNames.size(); ++i)
  {
    if (singleActionNames[i] == eventName)
    {
      try
      {
        auto const& f = any_cast<SingleEventAction>(singleActions[i]);
        f(observed);
      }
      catch (std::bad_any_cast& e)
      {
        throw "Sending SingleEvent failed";
      }
    }
  }
}

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

#endif // OBSERVER_HPP

