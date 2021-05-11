let
  pkgs = import <nixpkgs> { };
in
with pkgs;
stdenv.mkDerivation {
  pname = "audio-routing";
  version = "0.0.1";

  buildInputs = [ portaudio alsaLib libjack2 ];

# src = ./.;

# buildPhase = '' '';

# installPhase = '' '';
}
