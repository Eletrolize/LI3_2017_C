CC = gcc

OBJ_FILES := $(patsubst src/%.c, obj/%.o, $(wildcard src/*.c))

CFLAGS = -Wall -std=c11 -O2
PFLAGS = `pkg-config --cflags libxml-2.0`
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`


program: setup $(OBJ_FILES) interface.o
	$(CC) $(CLAGS) $(PFLAGS) $(LIBS) -o program program.c interface.o $(OBJ_FILES)

setup:
	mkdir -p obj

debug: CFLAGS := -g -O0
debug: program

obj/parser.o : src/parser.c
	$(CC) $(PFLAGS) $(CFLAGS) -o $@ -c $<

interface.o : interface.c
	$(CC) $(PFLAGS)  -o $@ -c $<

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

#obj/program.o: interface.h
#obj/interface.o: interface.h src/parser.h
#obj/parser.o: src/parser.h src/catartigos.h src/catcontribuidores.h
#obj/catartigos.o: src/catartigos.h src/catalogo.h src/revisao.h
#obj/catcontribuidores: src/catcontribuidores.h src/catalogo.h src/contribuidor.h
#obj/avl.o: src/avl.h src/set.h
#obj/set.o: src/set.h src/utils.h
#obj/utils.o: src/utils.h

run: setup $(OBJ_FILES)
		$(CC) $(CFLAGS) $(PFLAGS) -o program $(OBJ_FILES)
		./program

clean:
		-@rm -rf obj
		-@rm program
		-@rm *.o
		
cleanAll: clean
		-@rm -rf doc
		-@rm -rf html


.PHONY: doc
doc: setup $(OBJ_FILES)
	doxygen Doxyfile
