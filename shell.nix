{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.openssl
  ];

  shellHook = ''
    touch control-list.txt
    make
  '';
}
