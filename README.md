## About the Project:

This is a simple 2D graphics project made using OpenGL and GLUT.

In this project, I created a natural scene where birds are flying over mountains and a river. There are also clouds, a sun, grass, and flowers in the scene.

The main purpose of this project is to practice basic OpenGL drawing and animation.



 ## What the Project Does: 

The project creates a 2D animated scene with:

- Sun and sun rays
- Moving clouds
- Green mountains
- Green grass
- Flowers
- A river
- Flying birds
- Bird wing animation
- Moving water in the river

The birds fly from left to right. When they go outside the screen, they come back from the left side.

There are three birds in total. The first bird starts flying when the program starts. The second and third birds start flying after a short delay.



 ## Technologies Used: 

- C++
- OpenGL
- GLUT / FreeGLUT
- Math library
- GCC / MinGW-w64



 ## Requirements: 

To run this project, we need:

- A C++ compiler
- OpenGL
- GLUT or FreeGLUT
- Windows (if using the setup mentioned below)

I used MSYS2 MinGW64 with GCC to compile the project.

## Setup: 

First, make sure GCC is working.

Open the MSYS2 MinGW64 terminal and run:

g++ --version

If it shows the GCC version, the compiler is ready. Then install FreeGLUT .

pacman -S mingw-w64-x86_64-freeglut

The project uses:

#include <GL/glut.h>

So the GLUT header and library need to be installed properly.


## Project Structure: 

Flying-Birds-Animation/
│
├── Main-Folder/
│   └── MyProject.cpp
│
└── README.md

"MyProject.cpp" contains the main source code of the project.


 ## How to Build: 

Go to the folder where "MyProject.cpp" is located.

For example:

cd "/c/Users/User/Downloads/Graphics-Project-main/Graphics-Project-main/Main-Folder"

Then compile the program:

g++ MyProject.cpp -o MyProject.exe -lfreeglut -lopengl32 -lglu32

If everything is installed correctly, there should be no error and "MyProject.exe" will be created.



 ## How to Run: 

After building the project, run:

./MyProject.exe

A window will open and the animation will start automatically.



 ## Controls: 

The project has a few keyboard controls.

Key| What it does
"f"| Increases bird speed
"s"| Decreases bird speed
"r"| Resets the birds and their speed
"ESC"| Closes the program



 How the Animation Works: 

There are three main animations in this project.

1. Birds

The birds move from left to right continuously.

Their Y position is changed using the "sin()" function, so they move slightly up and down while flying.

When a bird goes outside the right side of the screen, it comes back from the left.

2. Wings

The wings have two states:

- Up
- Down

The "flapWings()" function changes between these two states every 120 milliseconds. This gives the birds a simple wing-flapping effect.

3. Clouds and River

The clouds slowly move from left to right.

The river also has some small lines that move continuously. These lines are used to show the movement of the water.



 ## Main Functions: 

Some important functions used in the project are:

"drawCircle()"

Used to draw circles.

It is used for the sun, clouds, flowers, and parts of the birds.

"drawFlower()"

Draws the flowers using lines, triangles, and circles.

"drawMountain()"

Creates the mountains using triangles.

"drawBird()"

Creates the bird using circles and triangles.

"drawRiver()"

Creates the river and the moving water lines.

"drawCloud()"

Creates the clouds using multiple circles.

"display()"

Draws the complete scene on the screen.

"moveScene()"

Controls the movement of birds, clouds, and river water.

"flapWings()"

Controls the bird wing animation.

"keyboard()"

Handles the keyboard controls.


OpenGL Concepts Used

While making this project, I used some basic OpenGL concepts such as:

- "glBegin()" and "glEnd()"
- "glVertex2f()"
- "glColor3f()"
- "GL_TRIANGLES"
- "GL_QUADS"
- "GL_LINES"
- "GL_TRIANGLE_FAN"
- 2D coordinates
- GLUT timer functions
- Keyboard input
- Basic animation
- "sin()" and "cos()"



 ## Output Preview: 

The output looks like a simple natural scene with a blue sky, sun, clouds, mountains, grass, flowers, a river, and flying birds.

 Screenshot of the running program:

 

 ## Conclusion: 

This project helped me understand how basic OpenGL shapes can be combined to create a complete 2D scene.

I also learned how to add simple animation using GLUT timers and how keyboard input can be used to control the animation.

Overall, it is a simple OpenGL project made for practicing 2D graphics and animation.
## Output Preview

![Project Output](output.png)
