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

#include <any>
#include <cxxabi.h>
#include <iomanip>
#include <functional>
#include <vector>
#include <sstream>
#include <type_traits>

class Observed;

/**
 * @brief alias for event function signature <br>
 * @code void(Content const&, Observed<Content, EventName> const&) @endcode
 *
 * with lambda :
 * @code
 * auto action1 = [](Content const& content, Observed<Content, EventName> const& Obs)
 * {
 *  std::cout << content;
 * };
 * @endcode
 */
template<class Content>
using EventAction = std::function<void(Content const&, Observed const&)>;

template<class T>
bool operator==(std::any l, T r)
{
  try
  {
    if constexpr(std::is_pointer<T>::value)
    {
      return *r == *std::any_cast<T>(l);
    }
    else
    {
      return r == std::any_cast<T>(l);
    }
  }
  catch (std::bad_any_cast& e)
  {
    return false;
  }
}

template<class T>
bool operator!=(std::any l, T r)
{
return !(l == r);
}

/**
 * @class BadActionMethod
 * when the type of the content in #Observer::addAction(EventName eventName, EventAction<Content> method) for
 * #EventAction
 * @code
 * EventAction aka { void(Content const&, Observed const&) }
 * @endcode
 * and for the type of content in Observed#notifyObserver(EventName eventName, Content content)
 * mismatch
 */
class BadActionMethod : public std::exception
{
private:
char* msg;

public:
BadActionMethod(char const * typeNameNotObs, char const * typeNameAddAct)
{
  std::stringstream msgT;
  int status = -4;
  char * typeDemNotObs = abi::__cxa_demangle(typeNameNotObs, nullptr, nullptr, &status);
  char * typeDemAddAct = abi::__cxa_demangle(typeNameAddAct, nullptr, nullptr, &status);

  msgT << "Type Content in notifyObserver and in addAction<Content> mismatch,\n\n"
      "notifyObserver is sending : " << typeDemNotObs << "\naddAction specify :"
      << typeDemAddAct << "\n\n"
      << "And EventAction must have signature : void(Content const&, Observed const&)\n";
  free(typeDemAddAct);
  free(typeDemNotObs);

  msg = new char[msgT.str().size() + 1];
  sprintf(msg, msgT.str().c_str());
}

~BadActionMethod()
{
  delete[] msg;
}

virtual char const* what() const noexcept
{
  return msg;
}
};

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
std::vector<std::any> names;
std::vector<std::any> actions;
//=======================>Constructors<=======================
public:
Observer() = default;
// TODO: rule of five ? copyandswap
virtual ~Observer()
{
  names.empty();
  actions.empty();
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
void addAction(EventName eventName, EventAction<Content> method);

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
private:

//=====================>Getters&Setters<======================
public:

private:

};

#include "Observer.cpp"
#endif
