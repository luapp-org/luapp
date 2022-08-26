{
  description = "The Lua++ Compiler";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-22.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    with flake-utils.lib;
    eachDefaultSystem (system:
      let pkgs = import nixpkgs { inherit system; };
      in {

        defaultPackage = pkgs.stdenv.mkDerivation {
          name = "luapp";
          version = "0.1.0";
          src = ./compiler;
          buildInputs = with pkgs; [ bison flex gcc ];
          buildPhase = ''
            mkdir -p $out/bin
            make OUTPUT=$out/bin/luappc
          '';
          installPhase = ''
            true
          '';
        };
        packages = flattenTree {
          static = pkgs.stdenv.mkDerivation {
            name = "luapp-static";
            version = "0.1.0";
            src = ./compiler;
            buildInputs = with pkgs; [ bison flex pkgsStatic.musl pkgsStatic.gcc ];
            buildPhase = ''
              mkdir -p $out/bin
              make OUTPUT=$out/bin/luappc CFLAGS='-lm -static'
            '';
            installPhase = ''
              true
            '';
          };
        };
        devShell =
          pkgs.mkShell { buildInputs = with pkgs; [ bison flex gcc ]; };
        formatter = nixpkgs.legacyPackages."${system}".nixfmt;

      });
}
