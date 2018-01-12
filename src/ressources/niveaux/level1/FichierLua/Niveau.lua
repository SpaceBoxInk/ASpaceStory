package.path = package.path .. ";" .. cppGetResourcesPath() .. "classes/?.lua"

local Robot = require("Robot")
local Personnage = require("Perso")
local Enigme = require("Enigme")
local Objet = require("Objet")

cppLoadCouche("../FichierCouche/level1.1.nbg", 0)
cppLoadCouche("../FichierCouche/level1.1.nvc", 1)

local socket = require("socket")
local nbPieceRobotGet = 0

function sleep(sec)
  socket.sleep(sec)
end

pngPersoParl = cppGetResourcesPath() .. "sprites/persoParle.png"

-- recupere la clé d'une action :
main = function()
  sleep(0.5)
  cppParler(pngPersoParl, "Qu'est ce que je fais là... ?")
  cppParler(pngPersoParl, "Est ce que je peux bouger... ?")
  cppParler(pngPersoParl, "Il faut que j'essaye...")
  cppParler(pngPersoParl, "Avec " .. cppGetKeyFor("upKey") .. " je devrais pouvoir avancer")
  cppParler(pngPersoParl, "Et avec " .. cppGetKeyFor("downKey") .. " reculer")
  cppParler(pngPersoParl, "Et puis aller à gauche et droite avec " .. cppGetKeyFor("leftKey") .. " et " .. cppGetKeyFor("rightKey"))
  sleep(3)
  cppParler(pngPersoParl, "Oh il y a quelque chose là-bas !\n" ..
    "Je pourrais sans doute utiliser la touche " .. cppGetKeyFor("mineKey") .. " pour les ramasser")
end

indice1 = function ()
  if nbPieceRobotGet == 3 then
    cppParler(pngPersoParl, "Oh il y a un levier, peut-être que je devrais appuyer sur la touche " .. cppGetKeyFor("interactEnvKey") .." pour l'actionner")
  end
end
-- Création niveau 1
--Initialisation de la position
cppSetPosition(2, 2)
cppSetTaille(0.9)
cppSetTexture(cppGetResourcesPath() .. "sprites/perso_face_32.png")
--  Création des énigmes du niveau (positions, informations et tout ça)

-- enigme1 = NewEnigme("enigme1","description", cppGetResourcesPath() .. "pictures/tombe.png")

cppNewEnigme("enigme1", "", cppGetResourcesPath() .. "pictures/tombe2.png")

guidageRobot = function()
  cppParler(pngPersoParl, "Je peux accéder au robot à distance avec ma tablette de programmation en appuyant sur la touche " .. cppGetKeyFor("openEditorKey"))
end

guidageEnigme = function()
  sleep(3)
  cppParler(pngPersoParl, "Pour localiser l'enigme mon gps en bas à gauche me permettra de connaitre la position(x et y) d'une case en la survolant avec la souris")
end

cppAddActionPassage(53,25,0, guidageEnigme)
cppAddActionPassage(42,24,0, guidageRobot)

getPiece = function(entite, item, x, y) -- on créée une fonction qui renvoie la piece robot
  nbPieceRobotGet = nbPieceRobotGet + 1

  if nbPieceRobotGet == 3 then
    cppNewRobot("robot1", cppGetResourcesPath() .. "sprites/robot_face_32.png", x, y, 0.4)
    cppAddActionPassage(16,11,0, indice1)
    cppParler(pngPersoParl, "Oh le robot se met à bouger !")
    cppParler(pngPersoParl, "Il est magnifique...")
    cppParler(pngPersoParl, "Peut-être que je devrais essayer de jeter un coup d'oeil à cette tombe grâce à mon nouveau robot, le passage semble vraiment étroit !")
    cppParler(pngPersoParl, "Je crois que pour l'utiliser il faudrait que j'apprenne à comprendre son langage...")
    cppParler(pngPersoParl, "Pour demander au robot d'avancer j'écris avancer() ")
    cppParler(pngPersoParl, "Pour demander au robot d'intéragir avec un objet(comme une tombe) j'écris activer() ")
    cppParler(pngPersoParl, "Pour demander au robot de tourner j'écris tournerDe(angle) ")
    cppParler(pngPersoParl, "L'angle peut prendre les valeurs suivantes : 90, -90, 180 et -180")
    cppParler(pngPersoParl, "Je peux utiliser les raccourcis présents dans le menu à gauche de ma tablette de programmation. Ils me seront très utiles ! ")
    cppParler("Pour le programmager je peux utiliser " .. cppGetKeyFor("interactEntityKey") .. " !")
  elseif nbPieceRobotGet == 2 then
    cppParler(pngPersoParl, "Avec une pièce de plus je devrais pouvoir construire un robot !")
  end
 
  return cppNewItem("pieceRobot","leak skvsf",  cppGetResourcesPath() .. "pictures/epee_niv1.png")
end

cppAddActionMining("piece_robot",getPiece) -- lorsque l'objet est ramassé(miné au niveau 0) la piece1 est mise dans l'inventaire du joueur par le C++
-- création du coffreutiliser

nouvellesCouches = function()
  cppAddInventory(15, 22, 3, 3)
  idIt = cppNewItem("epee", "test",  cppGetResourcesPath() .. "pictures/epee_niv1.png", 2, 3, 3, false, 1)
  cppPutNewItemOn(15, 22)
  parlerCoffre = function ()
    cppParler(pngPersoParl, "On dirait bien que j'ai accompli tout ce que j'avais à faire ici, je pourrais continuer d'explorer d'autres horizons...")
  end

  cppAddActionDeclenchement(15, 22, 0, parlerCoffre)
  niveauSuivant = function ()
    cppLoadCouche("../../level2/level2_data/level2-FIN.nbg",0)
    cppLoadCouche("../../level2/level2_data/level2-FIN.nvc",1)
  end

  cppAddActionPassage(51,0,0,niveauSuivant)
  cppAddActionPassage(52,0,0,niveauSuivant)

end

actionOuvertureGrotte = function ()
  if nbPieceRobotGet == 3 then
    -- charge le fond
    cppLoadCouche("../FichierCouche/level1.2.nbg", 0)
    cppLoadCouche("../FichierCouche/level1.2.nvc", 1)
    cppParler(pngPersoParl, "Quelle est donc cette sorcelerie !")
    nouvellesCouches()
  end
end

cppAddActionDeclenchement(16, 12, 1, actionOuvertureGrotte)

cppAddActionDeclenchement(54,25,0,function(entite)
  cppAfficherEnigme("enigme1")
  cppParler(pngPersoParl, "Oh non une enigme !")
  sleep(1)
  cppParler("Elle n'a pas l'air évidente...")
end)

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



-- entree_secrete = getCouche(1,-14,13)
-- entree_secrete:setActionDeclenchement(10, 8, 0,actionOuvertureGrotte)

--dire("... Où suis-je ? Je ne me souviens de rien...") -- le personnage se parle lui même quand il arrive
--dire("Il faut que je bouge...")


-- GESTION DES CONDITIONS DANS LE NIVEAU
