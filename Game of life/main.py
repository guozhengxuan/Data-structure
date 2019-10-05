import life


print("The game is on!")
living_cells = life.get_living_cells()
life_configuration = life.Life(living_cells)
life_configuration.show()
while life.get_command():
    life_configuration.update()
    life_configuration.show()
