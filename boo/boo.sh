#!/bin/bash
echo "cal solid"
for i in $(seq 1 9)
do
	./boo.out ../bcc0"$i".dat bcc LocBOPbcc0"$i".dat AveBOPbcc0"$i".dat
echo "bcc ok"
	./boo.out ../fcc0"$i".dat fcc LocBOPfcc0"$i".dat AveBOPfcc0"$i".dat
echo "fcc ok"
	./boo.out ../hcp0"$i".dat hcp LocBOPhcp0"$i".dat AveBOPhcp0"$i".dat
	echo "R"$i" cal ok"
done
for i in $(seq 10 20)
do
	./boo.out ../bcc"$i".dat bcc LocBOPbcc"$i".dat AveBOPbcc"$i".dat
echo "bcc ok"
	./boo.out ../fcc"$i".dat fcc LocBOPfcc"$i".dat AveBOPfcc"$i".dat
echo "fcc ok"
	./boo.out ../hcp"$i".dat hcp LocBOPhcp"$i".dat AveBOPhcp"$i".dat
	echo "R"$i" cal ok"
done
exit 0

