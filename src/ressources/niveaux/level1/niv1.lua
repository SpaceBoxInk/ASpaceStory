
loadfile(getScriptPath() .. "testLoad.lua")();

setTaille(getCurrentPerso(), 0.9);
setPosition(getCurrentPerso(), 2, 2);

addActionDeclenchement(10, 8, 0, function(entite)
  loadCouche("level1.2.nbg", 0)
  loadCouche("level1.2.nvc", 1)
end);

addActionPassage(1, 1, 0, function(entite)
  loadCouche("level1.2.nbg", 0)
  loadCouche("level1.2.nvc", 1)
end);