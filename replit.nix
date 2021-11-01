{ pkgs }: {
	deps = [
		pkgs.qemu
		pkgs.gcc
		pkgs.binutils
		pkgs.grub2
		pkgs.xorriso
		pkgs.nasm
		pkgs.python37
	];
}