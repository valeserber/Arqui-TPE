if [ ! -d ./bin ]
    then mkdir bin
fi
cd ./bin
rm -rf *
nasm -f aout ../src/asm/libasm.asm -o libasm.o
nasm -f aout ../src/asm/loader.asm -o kstart.o
nasm -f aout ../src/asm/int.asm -o int.o
gcc -g -c ../src/c/kernel.c -o kernel.o -fno-builtin -fno-stack-protector
gcc -g -c ../src/c/libc.c  -o libc.o -fno-builtin -fno-stack-protector
gcc -g -c ../src/c/int.c -o intc.o -fno-builtin -fno-stack-protector
gcc -g -c ../src/c/keyboard.c -o keyboard.o -fno-builtin -fno-stack-protector
gcc -g -c ../src/c/ctype.c -o ctype.o -fno-builtin -fno-stack-protector
gcc -g -c ../src/c/string.c -o string.o -fno-builtin -fno-stack-protector
gcc -g -c ../src/c/stdio.c -o stdio.o -fno-builtin -fno-stack-protector
gcc -g -c ../src/c/shell.c -o shell.o -fno-builtin -fno-stack-protector
gcc -g -c ../src/c/video.c -o video.o -fno-builtin -fno-stack-protector
gcc -g -c ../src/c/test.c -o test.o -fno-builtin -fno-stack-protector
ld -T ../src/asm/link.ld -o kernel.bin kernel.o kstart.o libc.o libasm.o int.o intc.o keyboard.o stdio.o string.o ctype.o shell.o video.o test.o

