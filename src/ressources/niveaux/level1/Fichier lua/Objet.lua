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
  
   actionAttasue = function()
  
   end
  
  }
end

function newPieceRobot(nom,inventaire)
  PieceRobot = { -- piece d'un robot
  
    nom = nom,
    type="pieceR",
    estPris = function(actionUser) -- lorsque l'utilisateur/Joueur a effectué une interaction sur une piece, envoie un signal boolean (actionUser)
    inventaire.nbDePiecesRobot = inventaire.nbDePiecesRobot + 1
      return actionUser
    end,
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

TabletteProg = {

    editeur = LanceEditeur(),

}

