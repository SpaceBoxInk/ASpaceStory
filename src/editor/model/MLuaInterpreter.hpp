/**
 * @file MLuaInterpreter.hpp
 *
 * Early optimization is the root of all evil
 *
 *  @date 22 nov. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#ifndef M_LUA_INTERPRETER
#define M_LUA_INTERPRETER

#include "../../outils/ObserverPattern/Observed.hpp"

#include <mutex>
#include <string>

class Editor;

class MRobot;
class MTerrain;

struct lua_State;

class MLuaInterpreter : public Observed
{
//========================>Attributes<========================
private:
  static std::string output;
  lua_State* lua;
  static bool abort;
  std::mutex running;

  static Editor* ihmEditor;
  static MTerrain* terrain;
  static MRobot* robot;

//=======================>Constructors<=======================
public:
  MLuaInterpreter(MTerrain* terrain, Editor* ihmEditor);
  // TODO: rule of five ? copyandswap
  virtual ~MLuaInterpreter();

private:
//=========================>Methods<==========================
public:
  void execute(std::string const& exePath);
  void interrupt();

  static int avancer(lua_State* l);
  static int avancerDe(lua_State* l);
  static int tournerDe(lua_State* l);
  static int activer(lua_State* l);
  static int print(lua_State* l);

  template<class Type>
  friend std::string& operator<<(std::string& ss, Type t);
  friend std::string& operator<<(std::string& ss, int t);
private:
  void registerFonctions();

//=====================>Getters&Setters<======================
public:
  void setRobot(MRobot* robot);
  bool isRunning();
  void clearOutput();
  std::string const& getOutput() const;
private:

};

inline void MLuaInterpreter::setRobot(MRobot* robot)
{
  MLuaInterpreter::robot = robot;
}

inline bool MLuaInterpreter::isRunning()
{
  if (!running.try_lock())
  {
    return true;
  }
  running.unlock();
  return false;
}

#endif
