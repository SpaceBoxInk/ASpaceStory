-- Création personnage
 require("Inventaire")
 function NewPerso()
  Perso = {
    x = 0,
    y = 0, 
    nom ="",
    
    --[[ deplacement = function(signal)
     
      if signal == "gauche" then
        self.x = self.x - 1
      elseif signal == "droite" then
        self.x = self.x +1
      elseif signal == "haut" then 
        self.y = self.y + 1
      elseif signal == "bas" then 
        self.y = self.y - 1
      end
      
    end, ]]--
    
    profilG="", -- profil gauche
    profilD="", -- profil droit
    profilB="", -- profil bas
    profilH="", -- profil haut
    inventaire = newInventaire(self.nom),
  }
  return Perso
end