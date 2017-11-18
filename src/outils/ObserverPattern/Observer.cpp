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
  names.push_back(eventName);
  actions.push_back(actionMethod);
}

template<class EventName, class Content>
void Observer::doEventActions(EventName eventName, Content content,
    Observed const& observed) const
{
  using namespace std;
  using opAny::operator ==;
  for (uint i = 0; i < names.size(); ++i)
  {
    if (names[i] == eventName)
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
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

#endif // OBSERVER_HPP

