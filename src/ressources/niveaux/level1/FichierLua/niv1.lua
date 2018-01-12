-- on load les couches depuis un fichier
-- exemple du loadfile
-- loadfile("../testLoad.lua")();
cppLoadCouche("../FichierCouche/level1.1.nbg", 0)
cppLoadCouche("../FichierCouche/level1.1.nvc", 1)
-- on ajoute l'action de minage pour l'element montage
cppAddActionMining("montagne", function(entite, item, x, y)
  print(entite.." mine montagne avec "..item)
  -- on créé un nouvel item
  local id = cppNewItem("Montagne", "Ceci est gros", cppGetResourcesPath() .. "pictures/epee_niv1.png")
  
  -- le fait de retourner l'id permet de mettre dans l'inventaire le dernier item créé
  return id
end)

-- regle la taille du personnage
cppSetTaille(0.9);
-- regle la position du personnage
cppSetPosition(4, 2);
-- regle la texture du personnage
cppSetTexture(cppGetResourcesPath() .. "sprites/perso_face_32.png")

cppAddInventory(2, 1, 10, 10)

cppNewEntity("test", cppGetResourcesPath() .. "sprites/texture3.png", 0, 0, 0.9)
cppNewRobot("robot1", cppGetResourcesPath() .. "sprites/robot_face_32.png", 3, 2, 0.4)

idIt = cppNewItem("jean", "leak skvsf",  cppGetResourcesPath() .. "pictures/epee_niv1.png", 2, 3, 3, false, 1)

-- on ajoute une action d'utilisation pour le nouvel item créé
cppAddActionUtilisation(function(entite)
	print("utilise jean")
end)
-- puis on le donne au personnage
cppPutNewItemOn(2, 1)

cppNewEnigme("nom", "desc", cppGetResourcesPath() .. "pictures/tombe.png")

-- on définie l'action de défense de l'entité test
cppAddActionDefense("test", function(entiteAtt, degat)
	print("arg")
end)

cppAddActionDeclenchement(10, 8, 0, function(entite)
  cppLoadCouche("../FichierCouche/level1.2.nbg", 0)
  cppLoadCouche("../FichierCouche/level1.2.nvc", 1)
end)

cppAddActionPassage(1, 1, 0, function(entite)
  cppAfficherEnigme("nom")
end)

print("done")


