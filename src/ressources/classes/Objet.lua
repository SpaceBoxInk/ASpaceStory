local Objet = {}

Objet.newItem = function (name,description, texture, degat, protection, supprimable, miningLevel )
  cppNewItem(name,description,texture,degat,protection, supprimable, miningLevel)
  return {
    id = cppNewItem(name, miningLevel),

    setActionUtilisation = function (self,action)
      addActionUtilisation(action)
    end,

    setActionAttaque = function (self, action)
      self.actionAttaque = action
    end

  }

end


Objet.getCouche = function (coucheLevel,x,y)

  return {
    cL = coucheLevel,
    x=x,
    y=y,
    setActionDeclenche = function(self,f)
      cppAddActionDeclenchement(self.x,self.y,self.coucheLevel,f)
    end,
    setActionPassage = function(self,f)
      cppAddActionPassage(self.x,self.y,self.coucheLevel,f)
    end
  }
end

return Objet
