Enigme = {

nom,
description,
image,
type,
positionDescription,
objectDeclencheur, 
decouverte, -- enigme decouverte ? 
resultat, -- resultat attendu de l'enigme


  setPosDes = function(x,y) 
    self.positionDescription = {x,y}
  end,
  
  
  
  whenInput = function(userInput) -- renvoie true si egnime reussie
  
     if userInput == resultat then
         sendMessageToUser("Enigme réussie")
         verif = true
      else 
         sendMessageToUser("Faux !") 
         verif = false
      end
      
    return verif
   end

}
