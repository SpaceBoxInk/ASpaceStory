pngPersoParl = cppGetResourcesPath() .. "sprites/persoParle.png"

cppParler(pngPersoParl, "Toute une autre zone")

cppAddActionPassage(45,3,0, function()
  cppParler(pngPersoParl, "Je vois un levier")
end)

cppAddActionDeclenchement(45,4,0, function()
	
end)