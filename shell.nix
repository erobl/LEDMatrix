{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
   name = "platformio-shell";
   buildInputs = with pkgs;
                  [ 
                    platformio
                   ];
   shellHook = ''
   '';          
}
