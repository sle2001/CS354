

all:
	@gcc -m64 -o a.out -Iinc/ drivers/verify.c src/functions.c

test: a.out 
	@./a.out < public_tests/inputs/t$(num).txt > myo$(num) 
	@diff myo$(num) public_tests/outputs/o$(num).txt  | tee  diff_output.txt > /dev/null
	@python3 drivers/file_check.py
	@rm -f diff_output.txt

clean: 
	@rm -f *.o *.out diff_output.txt
	@rm -f myo1
	@rm -f myo2
	@rm -f myo3
	@rm -f myo4
	@rm -f myo5
	@rm -f myo6
	@rm -f myo7
	@rm -f myo8
	@rm -f myo9
	@rm -f myo10
	@rm -f myo11
	@rm -f myo12
	@rm -f myo13
	@rm -f myo14
	@rm -f myo15
	@rm -f myo16
	@rm -f myo17
	@rm -f myo18
	@rm -f myo19
	@rm -f myo20
	@rm -f myo21
	@rm -f myo22
	@rm -f myo23
	@rm -f myo24
	@rm -f myo25
	@rm -f myo26
	@rm -f myo27
	@rm -f myo28
	@rm -f myo29
	@rm -f myo30
	@rm -f myo31
	@rm -f myo32
	@rm -f myo33
