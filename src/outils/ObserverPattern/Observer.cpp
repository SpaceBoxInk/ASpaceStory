/**
 * @file Observer.cpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 11 nov. 2017
 *  @author nihil
 */
#ifdef OBSERVER_HPP
#include <iostream>
#include <typeinfo>

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
void Observer<EventName, Content>::addAction(EventName eventName,
    actionMethod<EventName, Content> method)
{
  actions.insert(std::make_pair(eventName, method));
}

template<class EventName, class Content>
void Observer<EventName, Content>::doEventActions(EventName eventName, Content content,
    Observed<EventName, Content> const& observed) const
{
  using namespace std;
  auto actionsForEvent = actions.equal_range(eventName);
  for (auto i = actionsForEvent.first; i != actionsForEvent.second; ++i)
  {
    i->second(content, observed);
  }
}
//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

#endif
