
loadfile(getScriptPath() .. "testLoad.lua")();

setTaille(0.9);
setPosition(2, 2);
setTexture(getResourcesPath() .. "sprites/perso_face_32.png");

newEntity("test", getResourcesPath() .. "sprites/texture3.png", 2, 1, 0.9)
newRobot("robot1", getResourcesPath() .. "sprites/robot_face_32.png", 3, 2, 0.4)

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