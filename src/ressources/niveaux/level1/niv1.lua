loadCouche("level1.nbg", 0)
loadCouche("level1.nvc", 1)
addActionDeclenchement(10, 8, 0, function(entite)
  loadCouche("level1.2.nbg", 0)
  loadCouche("level1.2.nvc", 1)
end);