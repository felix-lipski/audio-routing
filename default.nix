{ pkgs, nixpkgs }:
let
  lib           = nixpkgs.lib;
in
pkgs.pkgs.stdenv.mkDerivation rec {
  pname       = "bmt-sink";
  version     = "0.0.3";
  unpackPhase = ''
    true
    '';
  buildInputs = (import ./build-inputs.nix) { inherit pkgs; };

  buildPhase  = ''
    mkdir -p $out/bin
	g++ -o sink ${src/sink.cpp} -lm -lrt -lasound -ljack -lpthread -lportaudio -largtable3
	gcc -o writer ${src/writer.c} -lm
    '';

  installPhase = ''
    cp sink $out/bin/bmt-sink
    cp writer $out/bin/bmt-test-writer
    '';
}
