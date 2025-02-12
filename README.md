# Air hockey

First time:
- Making a game using C++ and SDL.
- Using CMake.
- Organizing a C++ project.

![image](https://github.com/user-attachments/assets/8eeeada8-a011-485b-b2f7-2f7f60a3d1c4)

All because of school project >:(

## Environment setup

### Nix

```bash
nix develop [--command <shell>]
```

### Others

Ensure that the followings exist on your system:
  - `cmake`: supporting version >= 3.12
  - `gnumake`
  - `g++`: supporting the C++17 standard
  - `SDL2`: [Guide](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)
  - `SDL2_ttf`: [Guide](https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index.php)
  - `SDL2_image`: [Guide](https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index.php)
  - `SDL2_mixer`: [Guide](https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index.php)

## Workflows

### Build

```bash
cmake .
cmake --build .
./out.o # Run the game
```

### Develop

1. Run `cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .` to generate `compile_commands.json`, which can be picked up by C++ LSP such as `clangd`.
2. If you're simply changing the source files, rerun this everytime to rebuild:
   ```bash
   cmake --build .
   ```
   More intrusive changes require rerunning (or if the above command fails):
   ```bash
   cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .
   cmake --build .
   ```
3. Run the game: `./out.o`.

## Project organization

```
└── src
    ├── bin
    │   └── game
    ├── include
    └── lib
```

This organization is based on what I saw + I saw the resemblance with Cargo package:
- `bin`: All source code for a binary goes here.
- `include`: Header files for the library.
- `lib`: All source code for the library.

## Design

The design is very simple, there's a class for every game object:
- [`Puck`](/src/include/object/puck.hpp)
- [`Bat`](/src/include/object/bat.hpp)
- [`Board`](/src/include/board.hpp)

### Moving game objects

Each moving game object i.e. puck and bat has 3 vectors:
- Position vector
- Velocity vector
- Acceleration vector

These also have a `move` method that accepts a time parameter, which modify these vectors according to time.

### Box (Static game objects)

There's the class [`Box`](/src/include/box.hpp) for representing a box that every moving game object is bound within. It's nothing more than a rect with texture.

The [`Board`](/src/include/board.hpp) is actually a box, with additional methods to determine various game condition. It also has a capping method for every moving game object types, i.e. `capPuckPosition` or `capBatPosition`, to ensure they are in the field.

### Vector2d

The class [`Vector2d`] is straightforward.

## Collision and Reflection

Because there are very few type of game objects, we decide that each game object will have a `doesCollide` method overloaded with every other game object.

Reflection is based on taking the normal vector of the collided surface right at the collision point and using some vector mathematics, see [collision.hpp](/src/include/collision.hpp).

## Remarks

We can see that for some methods, we have to define a version for each moving game object, and all of these somewhat relate to collision detection i.e. `doesCollide`, `cpPuckPosition`, `capBatPosition`. The reason for this is that, some future game objects may have different shapes so defining a single method that would work for any game objects is difficult. Therefore, we opted for this route.

For small games like this, doing this is simple and fine. But if there are very many kinds of game objects, this quickly becomes out of hand.

An idea would be:
- Each game object defines a method that returns its "collision shape".
- A centralized function that would detect collision, determine collision point, etc. based on 2 collision shapes.

However, this only solves the collision detection problem, we also need to fix collision: In real life, objects are rarely collided. Therefore, if we detect a collision, we have to adjust the objects a little so that they are not actually collided, to model objects that are pushing each other.


### Challenges and workaround

There's a challenge regarding the interaction of 2 game objects colliding but also being bound in the box at the same time.

1. A bat and a puck are colliding each other.
2. Collision detected & call fix collide method to make the 2 uncollided.
3. However, the puck is at the boundary of the box! Call capping method of the box.

The puck is now inside the box, but because the position of the puck is changed again regardless of the bat, they now actually overlap.

So how do we solve this problem? My work around is to loop the above 3 steps: fixing collision, fixing out of boundary, fixing collision, etc. with hopes that they would reach a consistent state at some point.
