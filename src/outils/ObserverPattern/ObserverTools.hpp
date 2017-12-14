/**
 * @file ObserverTools.hpp
 *
 * Early optimization is the root of all evil
 *
 *  Created on: 20 nov. 2017
 *      Author: nihil
 */

#pragma once

#include <cxxabi.h>
#include <stdlib.h>
#include <any>
#include <cstdio>
#include <functional>
#include <sstream>
#include <string>

class Observed;

/**
 * @brief alias for event function signature <br>
 * @code void(Content, Observed const&) @endcode
 *
 * with lambda :
 * @code
 * auto action1 = [](Content content, Observed const& obs)
 * {
 *  std::cout << content;
 * };
 * @endcode
 */
template<class Content>
using EventAction = std::function<void(Content, Observed const&)>;

/**
 * @brief alias for event without content function signature <br>
 * @code void(Observed const&) @endcode
 *
 * with lambda :
 * @code
 * auto action1 = [](Observed const& obs)
 * {
 *  std::cout << typeid(obs).name();
 * };
 * @endcode
 */
using SingleEventAction = std::function<void(Observed const&)>;

namespace opAny
{

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

}  // namespace opAny

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
