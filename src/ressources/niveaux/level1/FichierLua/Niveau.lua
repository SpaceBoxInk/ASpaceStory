loadfile("../testLoad.lua")();

loadfile("../classes/Robot.lua")();
loadfile("../classes/Perso.lua")();
loadfile("../classes/Enigme.lua")();
loadfile("../classes/Objet.lua")();



-- Création niveau 1

--  Création des énigmes du niveau (positions, informations et tout ça)

enigme1 = newEnigme("enigme1","description", cppGetResourcesPath() .. "pictures/tombe.png")
enigme1:setCpp()

--Initialisaiton de la position
cppSetPosition(2, 2)


--  Création des objets du niveau (positions, noms et tous les attributs)

-- /!\ Modifier comportements des entites

local nbPieceRobotGet = 0

getPiece = function(entite, item, x, y) -- on créée une fonction qui renvoie la piece robot
  nbPieceRobotGet = nbPieceRobotGet + 1
  
  
  
  return cppNewItem("pieceRobot"..nbPieceRobotGet, 0)
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
  cppLoadCouche("niv1-grotteOuverte.nbg",0) -- niveau background
  -- charge la grotte ouverte avec coffre ...
  cppLoadCouche("niv1-grotteOuverte.nvc",1)-- niveau view common/currant

end

entree_secrete = getCouche(1,-14,13)
entree_secrete:setActionDeclenchement(10, 8, 0,actionOuvertureGrotte)

--dire("... Où suis-je ? Je ne me souviens de rien...") -- le personnage se parle lui même quand il arrive
--dire("Il faut que je bouge...")


-- GESTION DES CONDITIONS DANS LE NIVEAU

-- TODO : finir fonction Enigme: Evenement de la sortie
entreePossible = function() 
  return Perso.x == 21 or Perso.x == 22 and Perso.y == 15 
end 

if not enigme1.whenInput and entreePossible() then -- positionDeSortie à fixer
  -- dire("*VISION* ... Je pense qu'il y a encore des choses à regarder ")
  -- sendMessageToUser("Compétence: curiosité maximale atteinte")
elseif enigme1.whenInput and entreePossible() then
  -- chargerTerrain("niv2.nbg",0)
  -- chargerTerrain("niv2.nvc",0)
  -- charger alpha
end

-- RobotPret : Lorsque le joueur a regroupé toutes les pieces du robot (3)

robotReussi = function()
  return nbPieceRobotGet == 3
end

if robotReussi() then
  x, y = joueur:getCoordonnees()
  cppNewRobot("robot1", cppGetResourcesPath() .. "sprites/robot_face_32.png", x+1, y+1, 0.4)
  -- dire("Oh il se met à bouger !")
  -- sendMessageToUser("Le robot semble content de vous rencontrer, mais il ne se souvient plus de son nom, comment s'appelle-il ?")
  -- sendMessageToUser("Vous possédez désormais utilser la tablette de Programmation, elle vous permettra de communiquer avec le robot comme bon vous semble ! (comme pour passer dans des passaes étroits par exemple...")
  -- ajouter à l'inventaire tablette de programmation
end

