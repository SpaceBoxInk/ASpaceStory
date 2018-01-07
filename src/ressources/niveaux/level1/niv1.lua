
loadfile("testLoad.lua")();

cppAddActionMining("montagne", function(entite, item)
  print(entite.." mine montagne avec "..item)
  local id = cppNewItem("Montagne", "Ceci est gros", cppGetResourcesPath() .. "pictures/epee_niv1.png")
  return id
end)

cppSetTaille(0.9);
cppSetPosition(5, 2);
cppSetTexture(cppGetResourcesPath() .. "sprites/perso_face_32.png");

cppNewEntity("test", cppGetResourcesPath() .. "sprites/texture3.png", 2, 1, 0.9)
cppNewRobot("robot1", cppGetResourcesPath() .. "sprites/robot_face_32.png", 3, 2, 0.4)
idIt = cppNewItem("jean", "leak skvsf",  cppGetResourcesPath() .. "pictures/epee_niv1.png", 2, 3, 3, false, 1)

cppAddActionUtilisation(function(entite)
	print("utilise jean")
end)

cppGiveNewItemToPerso()

cppNewEnigme("nom", "desc", cppGetResourcesPath() .. "pictures/tombe.png")


cppAddActionDefense("test", function(entiteAtt, degat)
	print("arg")
end)

cppAddActionDeclenchement(10, 8, 0, function(entite)
  cppLoadCouche("level1.2.nbg", 0)
  cppLoadCouche("level1.2.nvc", 1)
end);

cppAddActionPassage(1, 1, 0, function(entite)
  cppAfficherEnigme("nom")
end);

print("done")
