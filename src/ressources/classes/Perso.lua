
 function getPerso(profilG,profilD,profilB,profilH)
  Perso = {
    x=0,
    y=0,
    getCoordonnees = function(self)
    	return cppGetCoordonnees()
    end,
    
    setCoordonnees = function(self,x,y)
     self.x=x
     self.y=y
    end,

    pG=profilG, -- profil gauche
    pD=profilD, -- profil droit, je suis pas homophobe hein
    pB=profilB, -- profil bas
    pH=profilH, -- profil haut
    
  }
  return Perso
end