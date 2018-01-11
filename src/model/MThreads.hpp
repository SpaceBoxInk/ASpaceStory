/**
 * @file MThreads.hpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 11 janv. 2018
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include <future>

class MThreads
{
//========================>Attributes<========================
private:
  static std::future<void> thread1;
  static std::future<void> thread2;
//=======================>Constructors<=======================
public:

private:

//=========================>Methods<==========================
public:
  template<class fct, class ... Args>
  static void parallelize(fct&& function, Args&& ... args)
  {
    if (!thread1.valid() || is_ready(thread1))
    {
      thread1 = std::async(std::launch::async, std::forward<fct>(function),
                           std::forward<Args>(args) ...);
    }
    else
    {
      if (thread2.valid() && !is_ready(thread2))
      {
        thread2.wait();
      }
      thread2 = std::async(std::launch::async, std::forward<fct>(function),
                           std::forward<Args>(args) ...);
    }
  }
private:
  template<typename R>
  static bool is_ready(std::future<R> const& f)
  {
    return f.valid() && f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
  }

//=====================>Getters&Setters<======================
public:

private:

};

//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

