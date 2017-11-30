/**
 * @file Observer.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 11 nov. 2017
 *      Author: nihil
 */

#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "ObserverTools.hpp"
#include <vector>

/**
 * @class Observer
 * @brief it's the Observer of the Observer pattern
 * this class is a attempt to recieve event from #Observed by subscription system
 *
 * @tparam EventName is the type for the event names
 * @tparam Content is the type for the event's content
 *
 * @see Observed::addObserver(Observer<EventName, Content> const* observer)
 */
class Observer
{
//========================>Attributes<========================
private:
  /**
   * @brief the list of actions handle by event name
   */
  std::vector<std::any> actionNames;
  std::vector<std::any> actions;

  std::vector<std::any> singleActionNames;
  std::vector<std::any> singleActions;
//=======================>Constructors<=======================
public:
  Observer() = default;
// TODO: rule of five ? copyandswap
  virtual ~Observer()
  {
  }

private:

//=========================>Methods<==========================
public:
  /**
   *
   * @param eventName the name of this action which is called when an event of the same name is send
   * @param method the event behavior, the method/lambda defined for a specific event
   * @see Observed::notifyObserver(EventName eventName, Content content)
   */
  template<class EventName, class Content>
  void addAction(EventName eventName, EventAction<Content> actionMethod);

  /**
   *
   * @param eventName the name of this action which is called when an event of the same name is send
   * @param method the event behavior, the method/lambda defined for a specific event
   * @see Observed::notifyObserver(EventName eventName, Content content)
   */
  template<class EventName>
  void addAction(EventName eventName, SingleEventAction actionMethod);

  /**
   * @brief method called by the #Observed when an event is send
   *
   * @param eventName the name for the event
   * @param content the content message of the event
   * @param observed the source of the event
   * @note do not call this method, it's called automatically by #Observed
   */
  template<class EventName, class Content>
  void doEventActions(EventName eventName, Content content, Observed const& observed) const;

  /**
   * @brief method called by the #Observed when an event is send
   *
   * @param eventName the name for the event
   * @param observed the source of the event
   * @note do not call this method, it's called automatically by #Observed
   */
  template<class EventName>
  void doEventActions(EventName eventName, Observed const& observed) const;

private:

//=====================>Getters&Setters<======================
public:

private:

};

#include "Observer.cpp"
#endif
