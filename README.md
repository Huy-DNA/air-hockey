# Air hockey

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
