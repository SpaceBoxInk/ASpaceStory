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

-- recupere la clé d'une action :
main = function()
  sleep(0.5)
  cppParler("Qu'est ce que je fais là... ?")
  cppParler("Est ce que je peux bouger... ?")
  cppParler("Il faut que j'essaye...")
  cppParler("Avec " .. cppGetKeyFor("upKey") .. " je devrais pouvoir avancer")
  cppParler("Et avec " .. cppGetKeyFor("downKey") .. " reculer")
  cppParler("Et puis aller à gauche et droite avec " .. cppGetKeyFor("leftKey") .. " et " .. cppGetKeyFor("rightKey"))
  sleep(1)
  cppParler("Oh il y a quelque chose à là-bas, on dirait des... des... morceaux de quelque chose ! Il faudrait que je pense à appuyer sur la touche " .. cppGetKeyFor("mineKey") .. " pour les ramasser")
end

indice1 = function ()
  if nbPieceRobotGet == 3 then
    cppParler("Oh il y a un levier, peut-être que je devrais appuyer sur la touche " .. cppGetKeyFor("interactEnvKey") .." pour l'actionner")
  end
end
-- Création niveau 1
--Initialisation de la position
cppSetPosition(2, 2)
cppSetTaille(0.9)
cppSetTexture(cppGetResourcesPath() .. "sprites/perso_face_32.png")
--  Création des énigmes du niveau (positions, informations et tout ça)

-- enigme1 = NewEnigme("enigme1","description", cppGetResourcesPath() .. "pictures/tombe.png")

cppNewEnigme("enigme1", "Soit le point T(a,b) position de la tombe, le tunel se trouve au point M(x,y). Déterminez x et y pour trouver mon trésor... ", cppGetResourcesPath() .. "pictures/tombe2.png")

getPiece = function(entite, item, x, y) -- on créée une fonction qui renvoie la piece robot
  nbPieceRobotGet = nbPieceRobotGet + 1

  if nbPieceRobotGet == 3 then
    cppNewRobot("robot1", cppGetResourcesPath() .. "sprites/robot_face_32.png", x, y, 0.4)
    cppAddActionPassage(16,11,0, indice1)
    cppParler("Oh le robot se met à bouger !")
    cppParler("Il est magnifique...")
    cppParler("Je crois que pour l'utiliser il faudrait que j'apprenne à le comprendre son langage...")
    cppParler("Pour demander au robot d'avancer : utiliser avancer() ")
    cppParler("Pour demander au robot d'activer quelque chose: écrivez activer() ") 
    cppParler("Pour demander au robot de tourner : écrivez tournerDe(angle) ")    
    cppParler("L'angle peut prendre les valeurs suivantes : 90, -90, 180 et -180 ")  
    cppParler("Pour les boucles, amusez vous à les comprendre ;) !")
  else if nbPieceRobotGet == 2 then 
    cppParler("Ces pieces ressemblent à une sorte de... robot ? Peut être que je devrais ramasser la troisième... ?")
  end
  
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
      cppParler("On dirait bien que j'ai accompli tout ce que j'avais à faire ici...")
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
    cppParler("Quelle est donc cette sorcelerie !")
    nouvellesCouches()
  end
end

cppAddActionDeclenchement(16, 12, 1, actionOuvertureGrotte)

cppAddActionDeclenchement(54,25,0,function(entite)
  cppAfficherEnigme("enigme1")
  cppParler("Oh non une enigme !")
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
