# Balls Physics Engine

This project is a particle physics simulation that allows free placement of balls, manipulation of forces, and different gravity settings and supports realistic elastic collisions between objects. To begin manipulating the balls, there are three distinct setting modes:

# Ball Placement: (Press 'B' to enter | Green Ball Icon):
When in this mode, you can place and delete balls from the screen using the mouse. A ghost ball will hover over your cursor to show your current ball settings.

Left click to place a ball, and right click on a ball to delete it.
Use the scroll wheel to change the size and mass of the balls.
Use the number keys ('0' - '9') to change the color of placed balls.

# Velocity Setting: (Press 'V' to enter | Orange Vector Icon):
This mode allows you to set inital velocities to balls by clicking and dragging.

Left click a ball and drag in a direction to set it's velocity. The farther you drag, the stronger the force.
Right click a ball to erase any velocity it currently has.
Press 'W' to toggle collision with the walls of the window.
Press 'A' to toggle between the air resistance modes. The current mode will display in the icon in the bottom left. 
(Red: Strong Resistance, Purple: Weak Resistance, None: No Resistance)

# Gravity Setting: (Press 'G' to enter | Blue Arrow Icon):
This mode allows you to change the gravity that will affect the ball.

Press '1', '2', or '3' to increase the strength of the gravity. Press '0' to omit gravity.
Press the arrow keys to chose the cardinal direction of the gravity.
Left click anywhere to set an "Attract Point". Gravity will pull balls to this point. It is displayed by a '-'.
Right click anywhere to set a "Repel Point". Gravity will push balls away from this point. It is displayed by a '+'.


After creating the inital conditions, press 'SPACE' to start the simulation. To pause, press 'SPACE' again or press 'B', 'V', or 'G' to enter those modes again.
