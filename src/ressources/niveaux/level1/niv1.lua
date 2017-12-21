
loadfile(getScriptPath() .. "testLoad.lua")();

addActionMining("montagne", function(entite, item)
  print(entite.." mine montagne avec "..item)
  
--  return newItem();
end)

addActionDeclenchement(10, 8, 0, function(entite)
  loadCouche("level1.2.nbg", 0)
  loadCouche("level1.2.nvc", 1)
end);

addActionPassage(1, 1, 0, function(entite)
  loadCouche("level1.2.nbg", 0)
  loadCouche("level1.2.nvc", 1)
end);
