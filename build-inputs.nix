{ pkgs ? import <nixpkgs> { } }:
with pkgs;
[ gcc portaudio alsaLib libjack2 argtable ]
