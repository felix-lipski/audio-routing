{ pkgs ? import <nixpkgs> { } }:
with pkgs;
[ portaudio alsaLib libjack2 ]
