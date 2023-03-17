CFLAGS = -g -c -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline \
		 -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default \
 		 -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy \
		 -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers \
		 -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
		 -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

EXE_FLAG = valgrind -s --leak-check=yes --show-leak-kinds=all --log-file="./logs/valgrind_log.txt"

CC = g++
TARGET = List

DIR_GRAPHVIZ = ./graphviz
DIR_LIST     = ./List


all : Make_list 

clean_l: 
	cd $(DIR_LIST) && make clean 

clean_gf:
	cd $(DIR_GRAPHVIZ) && make clean_files

clean_g:
	cd $(DIR_GRAPHVIZ) && make clean

Make_g: 
	cd $(DIR_GRAPHVIZ) && make

Make_list: 
	cd $(DIR_LIST) && make


