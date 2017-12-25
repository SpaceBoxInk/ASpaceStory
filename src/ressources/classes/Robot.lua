-- création Robot
function getRobot(x,y)
Robot = {
  x=x,
  y=y,
  
  setCoordonnes = function(x,y) 
    self.x = x
    self.y = y
  end
}

return Robot

end