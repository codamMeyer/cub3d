# Cud3D TODO list 

 - [x] **use the miniLibX**
 - [x] **The management of your window must remain smooth: changing to another window, minimizing, etc.**
 - [x] **Display different wall textures (the choice is yours) that vary depending on which side the wall is facing (North, South, East, West).**
 - [ ] **Your program must be able to display an item (sprite) instead of a wall.**
 - [x] **Your program must be able to set the floor and ceilling colors to two different ones.**
 - [ ] **save the first rendered image in bmp format when its second argument is "– –save".**

### **If no second argument is supllied, the program displays the image in a window and respects the following rules:**
 - [x] **The left and right arrow keys of the keyboard must allow you to look left and right in the maze.**
- [x] **The W, A, S and D keys must allow you to move the point of view through the maze.**
- [x] **Pressing ESC must close the window and quit the program cleanly.**
- [ ] **Clicking on the red cross on the window’s frame must close the window and quit the program cleanly.**
- [x] **If the declared screen size in the map is greater than the display resolution, the window size will be set depending to the current display resolution.**
- [x] **The use of images of the minilibX is strongly recommended.**
- [x] **Your program must take as a first argument a scene description file with the .cub extension.**
- [x] **The map must be composed of only 4 possible characters: 0 for an empty space, 1 for a wall, 2 for an item and N,S,E or W for the player’s start position and spawning orientation.**
- [x] **The map must be closed/surrounded by walls, if not the program must return an error.**
- [x] **Except for the map content, each type of element can be separated by one or more empty line(s).**
- [x] **Except for the map content which always has to be the last, each type of element can be set in any order in the file.**
- [x] **Except for the map, each type of information from an element can be separated by one or more space(s).**
- [x] **The map must be parsed as it looks like in the file. Spaces are a valid part of the map, and is up to you to handle. You must be able to parse any kind of map, as long as it respects the maps rules.**
- [ ] **If any misconfiguration of any kind is encountered in the file, the program
must exit properly and return "Error\n" followed by an explicit error message
of your choice.**

bonus

- [x] Wall collisions.
- [ ] A skybox.
- [ ] Floor and/or ceiling texture.
- [ ] An HUD.
- [ ] Ability to look up and down.
- [ ] Jump or crouch.
- [ ] A distance related shadow effect.
- [ ] Life bar.
- [ ] More items in the maze.
- [x] Object collisions.
- [ ] Earning points and/or losing life by picking up objects/traps.
- [ ] Doors which can open and close.
- [ ] Secret doors.
- [ ] Animations of a gun shot or animated sprite.
- [ ] Several levels.
- [ ] Sounds and music.
- [ ] Rotate the point of view with the mouse.
- [ ] Weapons and bad guys to fight!
