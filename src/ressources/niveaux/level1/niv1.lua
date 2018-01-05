
loadfile("testLoad.lua")();

addActionMining("montagne", function(entite, item)
  print(entite.." mine montagne avec "..item)
  local id = newItem("Montagne", "Ceci est gros", getResourcesPath() .. "pictures/epee_niv1.png")
  return id
end)

setTaille(0.9);
setPosition(2, 2);
setTexture(getResourcesPath() .. "sprites/perso_face_32.png");

newEntity("test", getResourcesPath() .. "sprites/texture3.png", 2, 1, 0.9)
newRobot("robot1", getResourcesPath() .. "sprites/robot_face_32.png", 3, 2, 0.4)
idIt = newItem("jean", "leak skvsf",  getResourcesPath() .. "pictures/epee_niv1.png", 2, 3, 3, false, 1)

addActionUtilisation(function(entite)
	print("utilise jean")
end)

giveNewItemToPerso()

newEnigme("nom", "desc", getResourcesPath() .. "pictures/tombe.png")

afficherEnigme("nom")

addActionDefense("test", function(entiteAtt, degat)
	print("arg")
end)

addActionDeclenchement(10, 8, 0, function(entite)
  loadCouche("level1.2.nbg", 0)
  loadCouche("level1.2.nvc", 1)
end);

addActionPassage(1, 1, 0, function(entite)
  loadCouche("level1.2.nbg", 0)
  loadCouche("level1.2.nvc", 1)
end);

print("done")
