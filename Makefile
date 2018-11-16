#All Character Makefile
CXX=g++-5
CXXFLAGS=-std=c++14 -Wall -MMD 
EXEC= exec
OBJECTS=cell.o door.o emptycell.o floortile.o passage.o wall.o dragonhoard.o gold.o merchanthoard.o normal.o small.o item.o subject.o character.o spawner.o invalidtype.o goblin.o halfling.o human.o merchant.o orc.o shade.o troll.o vampire.o drow.o dragon.o elf.o dwarf.o potion.o ba.o bd.o ph.o rh.o wa.o wd.o textdisplay.o stair.o floor.o chamber.o gamecontroller.o main.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
