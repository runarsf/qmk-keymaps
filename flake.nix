# {
#   description = "a simple flake that echoes hi";
# 
#   inputs = {
#     flake-utils.url = "github:numtide/flake-utils";
#     nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
#   };
# 
#   outputs = { nixpkgs, flake-utils, ... }:
#     flake-utils.lib.eachdefaultsystem (system:
#       let
#         pkgs = import nixpkgs {
#           inherit system;
#         };
#       in {
#         devshell = pkgs.mkshell {
#           buildinputs = [ pkgs.hello ];
#         };
# 
#         defaultpackage = pkgs.writeshellscriptbin "say-hi" ''
#           echo "hi ''${name:-there}"!
#         '';
#       });
# }

{
  description = "Personal QMK keymaps";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }: utils.lib.eachDefaultSystem (system: rec {
    packages = {
      blank = lib.mkKeymap {
        keyboard = "";
        keymap = "";
        target = "";
        extension = "";
        sha = "7620c64b99dc5bec480bfaa2708cb3fae709e2b3";
      };

      air40 = lib.mkKeymap {
        keyboard = "ymdk/ymd40/air40";
        keymap = "air40";
        target = "flash";
        extension = "hex";
        sha = "2fd56317763e8b3b73f0db7488ef42a70f5b946e";
      };

      default = packages.blank;
    };

    lib = {
      mkKeymap = { keyboard, keymap, target, extension, sha }:
        let
          pkgs = nixpkgs.legacyPackages.${system};
          name = "qmk-keymap-${keymap}";
          firmware = builtins.fetchGit {
            url = "https://github.com/qmk/qmk_firmware.git";
            rev = sha;
            submodules = true;
          };
          buildScript = pkgs.writeShellScriptBin name ''
            echo "Hi $USER - ''${KEYMAP:-asd} ${keymap} for ${keyboard}"
            realpath $0
            dir="$(dirname $0)"
            echo $dir
          '';
        in pkgs.stdenv.mkDerivation rec {
          inherit name;

          nativeBuildInputs = with pkgs; [ qmk git buildScript ];

          src = firmware;

          BUILD_DIR = src;

          buildPhase = ''
            mkdir -p $out/{bin,lib,share}
            cp -r . "$out/lib/qmk_firmware"
          '';

          installPhase = ''
            ln -s "${buildScript}/bin/${name}" "$out/bin/${name}"
          '';
        };
    };
  });
}
