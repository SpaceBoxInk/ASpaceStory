 loadfile("Robot.lua")
 loadfile("Perso.lua")
 loadfile("Enigme.lua")
 loadfile("Objet.lua")
 
 
 
-- Création niveau 1
       
      --  Création des énigmes du niveau (positions, informations et tout ça)
    
      enigme1 = newEnigme("enigme1","description","test.png",type,{1,2},objd,dec,res)
     
      
      
      --  Création des objets du niveau (positions, noms et tous les attributs)
      
      inventaireRobot = newInventaire(1)
      
      pieceRobot1 = newPieceRobot({"piece1",{0,1}})
      pr1 = newItem(pieceRobot1) -- création d'un item pièce1
      pr1:setAction()
      
      pieceRobot2 = newPieceRobot({"piece2",{1,1}})
      pr2 = newItem(pieceRobot2) -- création d'un item piece 2
      
      pieceRobot3 = newPieceRobot({"piece3", {2,2}})
      pr3 = newItem(pieceRobot3) -- creation d'un item piece 3
      
      coffre = newCoffre({"Coffre1",{4,5}})
      c1 = newElement(coffre)-- création d'un element coffre
      
      Tombe = {
        enigme = enigme1,
        position= {1,2},
        imageTombe = ""
      }
      
      tombe = newElement(Tombe)
      
      newItem(tombe)
      
 

  dire("... Où suis-je ? Je ne me souviens de rien...") -- le personnage se parle lui même quand il arrive
  dire("Il faut que je bouge...")
 -- GESTION DES CONDITIONS DANS LE NIVEAU
 
 -- Enigme: Evenement de la sortie
 function RobotReussi()
  if pieceRobot1.
 end
 
  if enigmeF == false and Perso.x == positionDeSortieX and Perso.y == positionDeSortieY then -- positionDeSortie à fixer
    dire("*VISION* ... Je pense qu'il y a encore des choses à regarder")
    sendMessageToUser("Compétence: curiosité maximale atteinte")
  elseif enigmeF == true and Perso.x == positionDeSortieX and Perso.y == positionDeSortieY then 
   chargerTerrain("niv2.nbg",0)
   chargerTerrain("niv2.nvc",0)
   -- charger alpha
  end

-- RobotPret : Lorsque le joueur a regroupé toutes les pieces du robot (3)
  
  if nbDePiecesRobot == 3 then
     Robot.nbPieces = 3
     Robot.actif = true
  end
  
  if interactionPossible(Robot) then
    dire("Oh il se met à bouger !")
    sendMessageToUser("Le robot semble content de vous rencontrer, mais il ne se souvient plus de son nom, comment s'appelle-il ?")
    nomR = interagirUtilisateur()
    idNewRobot = newId(nomR,1,2)
    sendMessageToUser("Vous possédez désormais utilser la tablette de Programmation, elle vous permettra de communiquer avec le robot comme bon vous semble ! (comme pour passer dans des passaes étroits par exemple...")
    -- ajouter à l'inventaire tablette de programmation
   end
   
  -- Vérificaion intéraction 
  
  if interactionPossible(Tombe) then
    
    afficheEnigme(enigme)
    
  end
  
  if enigme.whenInput == true then
    sendMessageToUser("Félicitations vous avez réussi  l'énigme ! ")
  end
   
  if interactionPossible(Coffre) then
  
    interragiObjet(Coffre)
    -- ajouter à l'inventaire objets dans le coffre: épée et bouclier 
  
  end


actionOuvertureGrotte = function ()
  -- charge le fond 
  chargerTerrain("niv1-grotteOuverte.nbg",0) -- niveau background
  -- charge la grotte ouverte avec coffre ...
  chargerTerrain("niv1-grotteOuverte.nvc",1)-- niveau view common/currant
  
end

-- x = 5, y = 10, couche = 1
ajoutActionAuDeclenchement(5, 10, 1, actionOuvertureGrotte)

