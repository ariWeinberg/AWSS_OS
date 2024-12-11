srcdir=./src
builddir=./build

asmfile=main.asm
outfile=bootloader.o
imgfile=main.img

asmpath=$(srcdir)/$(asmfile)
outpath=$(builddir)/$(outfile)
imgpath=$(builddir)/$(imgfile)

ASM=nasm
ASMFLAGS=-f bin -o $(outpath)

emulator=qemu-system-i386
emulator_flags=-fda

$(imgpath): $(outpath)
	dd if=/dev/zero of=$(imgpath) bs=512 count=2880
	mkfs.fat -F 12 -n "AW_SS_OS" $(imgpath)
	dd if=$(outpath) of=$(imgpath) conv=notrunc
	

$(outpath): $(asmpath)
	$(ASM) $(ASMFLAGS) $(asmpath)

run: $(imgpath)
	sudo $(emulator) $(emulator_flags) $(imgpath)
