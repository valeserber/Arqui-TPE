sudo ./compila
sudo mkdir -p isodir
sudo mkdir -p isodir/boot
sudo cp     bin/kernel.bin isodir/boot/kernel.bin
sudo mkdir -p isodir/boot/grub
sudo cp grub.cfg isodir/boot/grub/grub.cfg
sudo grub-mkrescue -o kernel.iso isodir
cp kernel.iso ~/VBShared/
