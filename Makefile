CalcInterest : main.o deposit.o common.o
	gcc -o CalcInterest main.o deposit.o common.o
main.o : main.c deposit.h common.h
	gcc -c main.c
deposit.o : deposit.c deposit.h common.h
	gcc -c deposit.c
common.o : common.c common.h deposit.h
	gcc -c common.c
clean:
	rm -rf CalcInterest main.o deposit.o common.o
