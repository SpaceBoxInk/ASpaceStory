package.path = package.path .. ";" .. cppGetResourcesPath() .. "classes/?.lua"

local Robot = require("Robot")
local Personnage = require("Perso")
local Enigme = require("Enigme")
local Objet = require("Objet")

cppLoadCouche("../FichierCouche/level1.1.nbg", 0)
cppLoadCouche("../FichierCouche/level1.1.nvc", 1)

-- recupere la clé d'une action :
print("Est ce que je peux bouger...")
print("Il faut que j'essaye...")
print("Avec " .. cppGetKeyFor("upKey") .. " je devrais pouvoir avancer")
print("Et avec " .. cppGetKeyFor("downKey") .. " reculer")
print("Et puis aller à gauche et droite avec " .. cppGetKeyFor("leftKey") .. " et " .. cppGetKeyFor("rightKey"))

-- Création niveau 1
--Initialisation de la position
cppSetPosition(2, 2)
cppSetTaille(0.9)
cppSetTexture(cppGetResourcesPath() .. "sprites/perso_face_32.png")
--  Création des énigmes du niveau (positions, informations et tout ça)

-- enigme1 = NewEnigme("enigme1","description", cppGetResourcesPath() .. "pictures/tombe.png")

cppNewEnigme("nom", "desc", cppGetResourcesPath() .. "pictures/tombe.png")

--  Création des objets du niveau (positions, noms et tous les attributs)

-- /!\ Modifier comportements des entites

local nbPieceRobotGet = 0

getPiece = function(entite, item, x, y) -- on créée une fonction qui renvoie la piece robot
  nbPieceRobotGet = nbPieceRobotGet + 1

  if nbPieceRobotGet == 3 then
    cppNewRobot("robot1", cppGetResourcesPath() .. "sprites/robot_face_32.png", x, y, 0.4)
    -- dire("Oh il se met à bouger !")
    -- sendMessageToUser("Le robot semble content de vous rencontrer, mais il ne se souvient plus de son nom, comment s'appelle-il ?")
    -- sendMessageToUser("Vous possédez désormais utilser la tablette de Programmation, elle vous permettra de communiquer avec le robot comme bon vous semble ! (comme pour passer dans des passaes étroits par exemple...")
  end
  return cppNewItem("pieceRobot","leak skvsf",  cppGetResourcesPath() .. "pictures/epee_niv1.png")
end

cppAddActionMining("piece_robot",getPiece) -- lorsque l'objet est ramassé(miné au niveau 0) la piece1 est mise dans l'inventaire du joueur par le C++
-- création du coffre

cppAddInventory(15, 7, 3, 3)
idIt = cppNewItem("epee", "test",  cppGetResourcesPath() .. "pictures/epee_niv1.png", 2, 3, 3, false, 1)
cppPutNewItemOn(15, 7)

-- ca ca marche pas ^^
--if nbPieceRobotGet == 3 then
--
--  actionOuvertureGrotte = function ()
--    -- charge le fond
--    cppLoadCouche("../FichierCouche/level1.2.nbg", 0)
--    cppLoadCouche("../FichierCouche/level1.2.nvc", 1)
--  end
--
--  cppAddActionDeclenchement(10, 9, 1, actionOuvertureGrotte)
--end

-- ce serait plus comme ca :P
actionOuvertureGrotte = function ()
  if nbPieceRobotGet == 3 then
    -- charge le fond
    cppLoadCouche("../FichierCouche/level1.2.nbg", 0)
    cppLoadCouche("../FichierCouche/level1.2.nvc", 1)
  end
end
cppAddActionDeclenchement(10, 9, 1, actionOuvertureGrotte)

 
-- getCoffre = function() -- on créée une fonction qui renvoie un coffre
 -- return Objet.getCouche(1,-15,-7)
-- end
-- coffre = getCoffre()
-- Création d'une épée
-- getEpee = function() -- on créée une fonction qui renvoie une épée
  -- return newItem("Epee", 0)
-- end
-- coffre:setActionDeclenche(getEpee)
-- cppAddActionMining("coffre",getCoffre)

-- Création d'une tombe
--getTombe = function() -- on créée une fonction qui renvoie la piece robot
  -- return getCouche(1,24,-10)
-- end

--cppAddActionDeclenchement(1,24,10,function(entite)
 -- cppAfficherEnigme("nom")
--end)

-- entree_secrete = getCouche(1,-14,13)
-- entree_secrete:setActionDeclenchement(10, 8, 0,actionOuvertureGrotte)

--dire("... Où suis-je ? Je ne me souviens de rien...") -- le personnage se parle lui même quand il arrive
--dire("Il faut que je bouge...")


-- GESTION DES CONDITIONS DANS LE NIVEAU


