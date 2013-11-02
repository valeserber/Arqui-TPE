 cd ./bin
rm -rf *
nasm -f aout ../src/asm/libasm.asm -o libasm.o
nasm -f aout ../src/asm/loader.asm -o kstart.o
nasm -f aout ../src/asm/int.asm -o int.o
gcc -c ../src/c/kernel.c -o kernel.o -fno-builtin
gcc -c ../src/c/libc.c  -o libc.o -fno-builtin
gcc -c ../src/c/int.c -o intc.o -fno-builtin
gcc -c ../src/c/keyboard.c -o keyboard.o -fno-builtin
ld -T ../src/asm/link.ld -o kernel.bin kernel.o kstart.o libc.o libasm.o int.o intc.o keyboard.o
