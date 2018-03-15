CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -Wall -c -s 
LFLAGS = `sdl-config --libs` -lSDL
OBJ = Disgraph.o Screen.o Class.o Board.o Piece.o Rules.o GUI.o ChessGame.o UserIO.o AI.o

AIM= AlphaGun

all: $(AIM)

AlphaGun: $(OBJ)
	$(CC)  $(OBJ) -o ../bin/AlphaGun $(LFLAGS)




Board.o: Board.c Board.h Type.h
	gcc -Wall -ansi -c Board.c -o Board.o
Piece.o: Piece.c Piece.h Type.h
	gcc -Wall -ansi -c Piece.c -o Piece.o
GUI.o: GUI.c GUI.h Type.h
	gcc -Wall -ansi -c GUI.c -o GUI.o
Rules.o: Type.h Rules.c Rules.h
	gcc -Wall -ansi -c Rules.c -o Rules.o
UserIO.o:UserIO.h UserIO.c Type.h
	gcc -Wall -ansi -c UserIO.c -o UserIO.o	

AI.o: Rules.h AI.h Type.h Piece.h
	gcc -Wall -ansi -c AI.c -o AI.o


Screen.o: Screen.c Screen.h Lib.h
	$(CC) $(CFLAGS) Screen.c -o Screen.o

Disgraph.o: Disgraph.c Disgraph.h Lib.h
	$(CC) $(CFLAGS) Disgraph.c -o Disgraph.o

Class.o: Class.c Class.h Lib.h Type.h
	$(CC) $(CFLAGS) Class.c -o Class.o



clean:
	rm -f *.o ../*.tar.gz ../bin/AlphaGun
fclean:
	rm -f ../bin/AlphaGun

tar:
	gtar cvzf Chess_V1.0.tar.gz ../bin --exclude 'CVS' ../doc --exclude 'CVS' --exclude 'Chess_SoftwareSpec.pdf' ../README ../INSTALL ../COPYRIGHT

tarsrc:
	gtar cvzf Chess_V1.0_src.tar.gz ../bin --exclude 'CVS' ../doc --exclude 'CVS' ../src --exclude 'CVS' --exclude 'Chess_Alpha_src.tar.gz' ../README ../Makefile ../INSTALL ../COPYRIGHT

