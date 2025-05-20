{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    qtcreator
    qt5.full
    postgresql
    libpqxx
    pkg-config
    cmake
    gcc
    clang
  ];
}
