{
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShell = pkgs.mkShell {
        packages = with pkgs; [
          neovim
          SDL2
          SDL2_ttf
          SDL2_image
          SDL2_mixer
          ninja
          gcc
          cmake
        ];
        CMAKE_EXPORT_COMPILE_COMMANDS = 1;
      };
    });
}
