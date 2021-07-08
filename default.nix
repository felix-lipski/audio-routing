{ pkgs, nixpkgs }:
let
  lib           = nixpkgs.lib;
in
pkgs.pkgs.stdenv.mkDerivation rec {
  pname       = "bmt-master-writer";
  version     = "0.0.1";
  unpackPhase = ''
    true
    '';
  buildInputs = (import ./build-inputs.nix) { inherit pkgs; };

  buildPhase  = ''
    mkdir -p $out/bin
	g++ -o master ${src/master.cpp} -lm -lrt -lasound -ljack -lpthread -lportaudio
	gcc -o writer ${src/writer.c} -lm
    '';

  installPhase = ''
    cp master $out/bin/master
    cp writer $out/bin/writer
    cp master $out/master
    cp writer $out/writer
    '';
}
