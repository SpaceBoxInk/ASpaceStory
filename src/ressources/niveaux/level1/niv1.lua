
loadfile(getScriptPath() .. "testLoad.lua")();

setTaillePersonnage(getCurrentPerso(), 0.9);
setPositionPersonnage(getCurrentPerso(), 2, 2);

idIt = newItem("jean", "leak skvsf")

addActionUtilisation(function(entite)
	print("utilise jean")
end)

giveNewItemToPerso(getCurrentPerso())

newEntity("test", 2, 1, 0.9)

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
