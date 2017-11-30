/**
 * @file Observed.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 11 nov. 2017
 *      Author: nihil
 */

#ifndef OBSERVED_HPP
#define OBSERVED_HPP

#include "Observer.hpp"

#include <algorithm>
#include <iterator>
#include <vector>

/**
 * @class Observed
 * @tparam EventName is the type for the event names
 * @tparam Content is the type for the event's content
 *
 * @brief  it's the Observed of the Observer pattern
 * this class is a attempt to send event to #Observed subscribed to it
 */
class Observed
{
//========================>Attributes<========================
private:
  /**
   * @brief the list of observers subscribed to this #Observed
   */
  std::vector<Observer const*> observers;

  /**
   * @brief the state of this #Observed
   * if it's going to send an event or not
   */
  bool changed;
//=======================>Constructors<=======================
public:
  Observed();
  // TODO: rule of five ? copyandswap
  virtual ~Observed() = default;

private:

//=========================>Methods<==========================
public:
  /**
   *
   * @param observer the observer to add to the #observers subsciption list
   */
  void addObserver(Observer const* observer);

  /**
   * delete the specified #Observer from the subscribe list #observers
   * @param observer the #Observer to delete
   */
  void deleteObserver(Observer const* observer);

  /**
   * delete all observers for this #Observed object
   */
  void deleteObservers();

  /**
   * @return the number of subscribed Observers
   */
  int countObservers() const;
protected:
  /**
   *
   * @param eventName the event name which will called associated eventAction
   * @param content the content of the event
   */
  template<class EventName, class Content>
  void notifyObservers(EventName eventName, Content content);

  /**
   *
   * @param eventName the event name which will called associated eventAction
   */
  template<class EventName>
  void notifyObservers(EventName eventName);
private:

//=====================>Getters&Setters<======================
public:
  /**
   * @brief getter for changed
   * @return the state of this #Observed
   */
  bool hasChanged() const;

protected:
  /**
   * @brief setter for changed (set)
   *
   * to activate notifications to Observers
   */
  void setChanged();

  /**
   * @brief setter for changed (unset)
   *
   * to desactivate notifications to #Observer<br>
   * notifyObserver(EventName eventName, Content content) won't work
   */
  void clearChanged();
private:

};

template<class EventName, class Content>
void Observed::notifyObservers(EventName eventName, Content content)
{
  if (hasChanged())
  {
    for (Observer const* obs : observers)
    {
      obs->doEventActions(eventName, content, *this);
    }
  }
  clearChanged();
}

template<class EventName>
void Observed::notifyObservers(EventName eventName)
{
  if (hasChanged())
  {
    for (Observer const* obs : observers)
    {
      obs->doEventActions(eventName, *this);
    }
  }
  clearChanged();
}

inline void Observed::addObserver(Observer const* observer)
{
  observers.push_back(observer);
}

inline void Observed::deleteObserver(Observer const* observer)
{
  observers.erase(std::find(observers.begin(), observers.end(), observer));
}

inline int Observed::countObservers() const
{
  return observers.size();
}

//------------------------------------------------------------
//=====================>Getters&Setters<======================
//------------------------------------------------------------

inline bool Observed::hasChanged() const
{
  return changed;
}

inline void Observed::setChanged()
{
  changed = true;
}

inline void Observed::clearChanged()
{
  changed = false;
}

#endif
