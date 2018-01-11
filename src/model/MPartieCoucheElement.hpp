/**
 * @file MPartieCoucheElement.hpp
 *
 * Early optimization is the root of all evil
 * DRY ! Don't repeat yourself
 *
 *  @date 20 déc. 2017
 *  @author FederAndInk
 *  @brief TODO complete
 */

#pragma once

#include "MEntite.hpp"
#include "MPartieCouche.hpp"

#include <functional>
#include <memory>
#include <string>

class MPartieCoucheElement : public MPartieCouche
{
//========================>Attributes<========================
private:
  int miningLevel;
  /**
   * action when this couche is mined
   * THIS POINTER is copied !! it's to share the action between all same couche
   */
  std::shared_ptr<std::function<void(MEntite* entite, int item, int xMined, int yMined)>> actionMining; // replace by item

//=======================>Constructors<=======================
public:
  MPartieCoucheElement(Id ID, MTypeCouche type, std::string name, std::string fichierImg,
                       float placeDispo, int miningLevel = -1);
  MPartieCoucheElement(MPartieCoucheElement const&);
  MPartieCoucheElement& operator=(MPartieCoucheElement const&);
  // TODO: rule of five ? copyandswap
  virtual ~MPartieCoucheElement();

private:

//=========================>Methods<==========================
public:
  void mine(MEntite* entite, int item, MCoordonnees minedCoords) override;
private:

//=====================>Getters&Setters<======================
public:
  int getMiningLevel() const override;
  void setActionMining(
      std::function<void(MEntite* entite, int item, int xMined, int yMined)> actionMining)
      override;
  void unSetActionMining() override;
private:

};
//------------------------------------------------------------
//=====================>Implementations<======================
//------------------------------------------------------------

