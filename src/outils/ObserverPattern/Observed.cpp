/**
 * @file Observed.cpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 11 nov. 2017
 *      Author: nihil
 */
#ifdef OBSERVED_HPP

//------------------------------------------------------------
//========================>Constants<=========================
//------------------------------------------------------------

//------------------------------------------------------------
//=======================>Constructors<=======================
//------------------------------------------------------------
template<class EventName, class Content>
Observed<EventName, Content>::Observed(): changed(false)
{
}

//------------------------------------------------------------
//=========================>Methods<==========================
//------------------------------------------------------------

template<class EventName, class Content>
inline void Observed<EventName, Content>::addObserver(
    Observer<EventName, Content> const* observer)
{
  observers.push_back(observer);
}

template<class EventName, class Content>
inline void Observed<EventName, Content>::deleteObserver(
    Observer<EventName, Content> const* observer)
{
  observers.erase(std::find(observers.begin(), observers.end(), observer));
}

template<class EventName, class Content>
void Observed<EventName, Content>::deleteObservers()
{
  observers.clear();
}

template<class EventName, class Content>
inline int Observed<EventName, Content>::countObservers() const
{
  return observers.size();
}

template<class EventName, class Content>
inline void Observed<EventName, Content>::notifyObserver(EventName eventName,
    Content content)
{
  if (hasChanged())
  {
    for(Observer<EventName, Content>const* obs : observers)
    {
      obs->doEventActions(eventName, content, *this);
    }
  }
  clearChanged();
}

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

template<class EventName, class Content>
inline bool Observed<EventName, Content>::hasChanged() const
{
  return changed;
}

template<class EventName, class Content>
inline void Observed<EventName, Content>::setChanged()
{
  changed=true;
}

template<class EventName, class Content>
inline void Observed<EventName, Content>::clearChanged()
{
  changed=false;
}
#endif
