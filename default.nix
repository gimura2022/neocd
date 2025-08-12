{ pkgs ? import <nixpkgs> { }, subdir ? "" }: pkgs.stdenv.mkDerivation rec {
	pname = "neocd";
	version = "1.0.0";

	src = ./.;

	nativeBuildInputs = [ pkgs.stdenv.cc ];

	buildPhase = ''
		make
	'';

	installPhase = ''
		mkdir -p $out/bin
		mv ${pname}0 $out/bin/
		mv ${pname}1 $out/bin/
	'';
}
