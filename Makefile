GCC = g++

SRCS = data.cpp memory.cpp interpreter.cpp
OBJS = $(SRCS:%.c=%.o)

test: $(OBJS)
	$(GCC) $(OBJS) -o test

.c.o:
	$(GCC) -c $*.cpp

testall: test1 test2 test3 test4 test5 test6 test7 test8

test1: test
	./test testcase/36_jmp_test.smp > result/36_jmp_test_result.txt
	
test2: test
	./test testcase/40_jmpc_test.smp > result/40_jmpc_test_result.txt

test3: test
	./test testcase/75_pushvf_test.smp > result/75_pushvf_test_result.txt

test4: test
	./test testcase/100_add_test.smp > result/100_add_test_result.txt

test5: test
	./test testcase/108_mul_test.smp > result/108_mul_test_result.txt

test6: test
	./test testcase/112_div_test.smp > result/112_div_test_result.txt

test7: test
	./test testcase/136_cmplt_test.smp > result/136_cmplt_test_result.txt

test8: test
	./test testcase/140_cmpgt_test.smp > result/140_cmpgt_test_result.txt

test9: test
	./test testcase/interpreter_input.smp > result/interpreter_input_result.txt

clean: # remove all machine generated files
	rm -f test *.o 
