require("Inventaire.lua")

function newElement(nom)
  return {
   nom = nom,
   actionInteraction = function ()
    
   end,
   
   actionPassage = function ()
    
   end,
   
   setActionInteraction = function (self, action)
    self.actionInteraction = action
   end,
   setActionPassage = function (self, action)
    self.actionPassage = action
   end
  }
end


function newItem(nom)
  return {
   nom = nom,
   actionUtilisation = function ()
    
   end,
  
   actionAttaque = function()
  
   end,
   
   setActionUtilisation = function (self, action)
    self.actionInteraction = action
   end,
   
   setActionAttaque = function (self, action)
    self.actionPassage = action
   end
   
   } 
end

function newPieceRobot(nom,inventaire)
  PieceRobot = { -- piece d'un robot
  
    nom = nom,
    type="pieceR",
    estPris = nil
    
  }
  
  return PieceRobot
  
end

function newCoffre(nom,inventaire)
  Coffre = {
     id = nom,
     inventaire,
  }
  
  return Coffre
  
end
