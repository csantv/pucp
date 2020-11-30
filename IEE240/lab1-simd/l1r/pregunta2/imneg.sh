#sudo apt-get install nasm
#sudo apt-get install gcc-multilib
#pip3 install --user numpy pillow

#nasm -f elf32 -o imneg.o ./pregunta2/imneg.asm
#gcc -m32 -march=i686 -g ./pregunta2/testImneg.c imneg.o -o labp2

./labp2 ./data/goldhill_gray.pgm
python3 ./pregunta2/verifyImneg.py ./data/goldhill_gray.pgm

./labp2 ./data/img1.pgm
python3 ./pregunta2/verifyImneg.py ./data/img1.pgm

./labp2 ./data/img2.pgm
python3 ./pregunta2/verifyImneg.py ./data/img2.pgm
