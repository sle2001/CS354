###############################################################################
# @file: Makefile
#
# Simple makefile for project maintanence, usage, and testing 
#
# @creator: 11/18/21 Bujji Setty (selagamsetty@wisc.edu)
# @modified: 6/26/22 Bujji Setty (selagamsetty@wisc.edu)
#
###############################################################################

all: build_ll build_ht build_stress build_tester build_llsize build_test15 build_test2 build_test11 build_test12 build_test14 build_test16 build_test17

build_ll: src/ll_functions.c drivers/ll_main.c
	@gcc -g -Iinc/ -o ll.out src/*.c drivers/ll_main.c -m64 -Wall -Werror=implicit-function-declaration
build_llsize: src/ll_functions.c drivers/ll_mainsize.c
	@gcc -g -Iinc/ -o llsize.out src/*.c drivers/ll_mainsize.c -m64 -Wall -Werror=implicit-function-declaration
build_ht: src/hash_table.c drivers/ht_main.c src/ll_functions.c
	@gcc -g -Iinc/ -o ht.out src/*.c drivers/ht_main.c -m64 -Wall -Werror=implicit-function-declaration
build_htsize: src/hash_table.c drivers/ht_mainsize.c src/ll_functions.c
	@gcc -g -Iinc/ -o htsize.out src/*.c drivers/ht_mainsize.c -m64 -Wall -Werror=implicit-function-declaration
build_stress: src/hash_table.c drivers/stress.c src/ll_functions.c
	@gcc -g -Iinc/  -o stress.out src/*.c drivers/stress.c -m64 -Wall -Werror=implicit-function-declaration
build_tester: src/hash_table.c drivers/tester.c src/ll_functions.c
	@gcc -g -Iinc/  -o tester.out src/*.c drivers/tester.c -m64 -Wall -Werror=implicit-function-declaration
build_test15: src/hash_table.c drivers/test15.c src/ll_functions.c
	@gcc -g -Iinc/  -o test15.out src/*.c drivers/test15.c -m64 -Wall -Werror=implicit-function-declaration
build_test2: src/hash_table.c drivers/test2.c src/ll_functions.c
	@gcc -g -Iinc/  -o test2.out src/*.c drivers/test2.c -m64 -Wall -Werror=implicit-function-declaration
build_test11: src/ll_functions.c drivers/test11.c
	@gcc -g -Iinc/ -o test11.out src/*.c drivers/test11.c -m64 -Wall -Werror=implicit-function-declaration
build_test12: src/ll_functions.c drivers/test12.c
	@gcc -g -Iinc/ -o test12.out src/*.c drivers/test12.c -m64 -Wall -Werror=implicit-function-declaration
build_test14: src/hash_table.c drivers/test14.c src/ll_functions.c
	@gcc -g -Iinc/ -o test14.out src/*.c drivers/test14.c -m64 -Wall -Werror=implicit-function-declaration
build_test16: src/hash_table.c drivers/test16.c src/ll_functions.c
	@gcc -g -Iinc/ -o test16.out src/*.c drivers/test16.c -m64 -Wall -Werror=implicit-function-declaration
build_test17: src/hash_table.c drivers/test17.c src/ll_functions.c
	@gcc -g -Iinc/ -o test17.out src/*.c drivers/test17.c -m64 -Wall -Werror=implicit-function-declaration

valgrind_ll: ll.out
	@valgrind -s --leak-check=full ./ll.out

valgrind_ht: ht.out
	@valgrind -s --leak-check=full ./ht.out

valgrind_stress: stress.out
	@valgrind -s --leak-check=full ./stress.out
    
valgrind_tester: tester.out
	@valgrind -s --leak-check=full ./tester.out

valgrind_test15: test15.out
	@valgrind -s --leak-check=full ./test15.out

valgrind_test2: test2.out
	@valgrind -s --leak-check=full ./test2.out

valgrind_test11: test11.out
	@valgrind -s --leak-check=full ./test11.out

valgrind_test12: test12.out
	@valgrind -s --leak-check=full ./test12.out

valgrind_test14: test14.out
	@valgrind -s --leak-check=full ./test14.out

valgrind_test16: test16.out
	@valgrind -s --leak-check=full ./test16.out

valgrind_test17: test17.out
	@valgrind -s --leak-check=full ./test17.out
clean: 
	@rm -f *.out

# Feel free to add any additional commands that may make testing easier. Our 
# grading scripts will be using the version of this file that was provided to 
# you when the project was released. 

