all:y86emul y86dis y86ass
y86emul:
	gcc y86emul.c -o y86emul -lm
y86dis:
	gcc y86dis.c -o y86dis -lm
y86ass:
	gcc y86ass.c -o y86ass -lm
clean:
	rm -rf y86emul y86dis y86ass  *.o *.txt
