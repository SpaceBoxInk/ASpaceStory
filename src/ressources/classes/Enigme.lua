function NewEnigme(nom,des,img,type,posDes,objectD,decouv,res)
Enigme = {

nom = nom,
description = des,
image = img,
type = type,
positionDescription = posDes,
objectDeclencheur= objectD, 
decouverte=decouv, -- enigme decouverte ? 
resultat=res, -- resultat attendu de l'enigme

  
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
  return Enigme
end