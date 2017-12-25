function newItem(name, miningLevel)
  return {
   id = cppNewItem(name, miningLevel),
   
   setActionUtilisation = function (self, action)
    addActionUtilisation()
   end,
   
   setActionAttaque = function (self, action)
    self.actionAttaque = action
   end
   
   } 
   
end


function getCouche(coucheLevel,x,y)

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
