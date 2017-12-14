-- création Robot
function NewRobot(id)
Robot = {
 id = 1,
 nom,
 setNom = function(nom)
   self.nom = nom
 end,
 actif = false, -- boolean
 nbPiece = 0,
 
}

return Robot

end