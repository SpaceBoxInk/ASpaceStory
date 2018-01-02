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

#include <sstream>
#include <string>

class MRobot;
class MTerrain;

struct lua_State;

class MLuaInterpreter
{
//========================>Attributes<========================
private:
  static std::stringstream output;
  lua_State* lua;

  static MTerrain* terrain;
  static MRobot* robot;

//=======================>Constructors<=======================
public:
  MLuaInterpreter(MTerrain* terrain);
  // TODO: rule of five ? copyandswap
  virtual ~MLuaInterpreter();

private:
//=========================>Methods<==========================
public:
  void execute(std::string const& exePath);

  static int avancer(lua_State* l);
  static int avancerDe(lua_State* l);
  static int tournerDe(lua_State* l);
  static int print(lua_State* l);
private:
  void registerFonctions();

//=====================>Getters&Setters<======================
public:
  void setRobot(MRobot* robot);
  void clearOutput();
  std::stringstream const& getOutput() const;
private:

};

inline void MLuaInterpreter::setRobot(MRobot* robot)
{
  MLuaInterpreter::robot = robot;
}

#endif
