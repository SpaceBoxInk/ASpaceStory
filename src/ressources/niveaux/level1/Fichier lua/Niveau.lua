loadfile("Robot.lua")
loadfile("Perso.lua")
loadfile("Enigme.lua")
loadfile("Objet.lua")



-- Création niveau 1

--  Création des énigmes du niveau (positions, informations et tout ça)

enigme1 = newEnigme("enigme1","description","test.png",type,{1,2},objd,dec,res)
joueur = getJoueur("profilGauche.png","profilDroit.png","profilBas.png","profilHaut.png")
--  Création des objets du niveau (positions, noms et tous les attributs)

-- /!\ Modifier comportements des entites

local nbPieceRobotGet = 0

getPiece = function() -- on créée une fonction qui renvoie la piece robot
  nbPieceRobotGet = nbPieceRobotGet + 1
  return newItem("pieceRobot"..nbPieceRobotGet, 0)
end

cppAddActionMining("piece_robot",getPiece) -- lorsque l'objet est ramassé(miné au niveau 0) la piece1 est mise dans l'inventaire du joueur par le C++


-- création du coffre
getCoffre = function() -- on créée une fonction qui renvoie un coffre
  return getCouche(1,-15,-7)
end
coffre = getCoffre()

-- Création d'une épée
getEpee = function() -- on créée une fonction qui renvoie une épée
  return newItem("Epee", 0)
end

coffre:setActionDeclenche(getEpee)

cppAddActionMining("coffre",getCoffre)

-- Création d'une tombe
getTombe = function() -- on créée une fonction qui renvoie la piece robot
  return getCouche(1,24,-10)
end

cppAddActionMining("tombe",getTombe)


-- gestion comportement ouverture grotte
actionOuvertureGrotte = function ()
  -- charge le fond
  chargerTerrain("niv1-grotteOuverte.nbg",0) -- niveau background
  -- charge la grotte ouverte avec coffre ...
  chargerTerrain("niv1-grotteOuverte.nvc",1)-- niveau view common/currant

end

entree_secrete = getCouche(1,-14,13)
entree_secrete:setActionDeclenchement(actionOuvertureGrotte)

dire("... Où suis-je ? Je ne me souviens de rien...") -- le personnage se parle lui même quand il arrive
dire("Il faut que je bouge...")


-- GESTION DES CONDITIONS DANS LE NIVEAU

-- TODO : finir fonction Enigme: Evenement de la sortie

if not enigme1.whenInput and (Perso.x == 21 or Perso.x == 22)  and Perso.y == 15 then -- positionDeSortie à fixer
  dire("*VISION* ... Je pense qu'il y a encore des choses à regarder ")
  sendMessageToUser("Compétence: curiosité maximale atteinte")
elseif enigme1.whenInput and Perso.x == positionDeSortieX and Perso.y == positionDeSortieY then
  chargerTerrain("niv2.nbg",0)
  chargerTerrain("niv2.nvc",0)
  -- charger alpha
end

-- RobotPret : Lorsque le joueur a regroupé toutes les pieces du robot (3)

robotReussi = function()
  return nbPieceRobotGet == 3
end

if robotReussi() then
  x, y = joueur:getCoordonnees()
  robot = getRobot(x +1, y +1)
  dire("Oh il se met à bouger !")
  sendMessageToUser("Le robot semble content de vous rencontrer, mais il ne se souvient plus de son nom, comment s'appelle-il ?")
  sendMessageToUser("Vous possédez désormais utilser la tablette de Programmation, elle vous permettra de communiquer avec le robot comme bon vous semble ! (comme pour passer dans des passaes étroits par exemple...")
  -- ajouter à l'inventaire tablette de programmation
end

