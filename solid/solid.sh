#!/bin/bash
echo "cal solid"
for i in $(seq 1 9)
do
	./solid.out ../bcc0"$i".dat bcc Solidbcc0"$i".dat
echo "bcc ok"
	./solid.out ../fcc0"$i".dat fcc Solidfcc0"$i".dat
echo "fcc ok"
	./solid.out ../hcp0"$i".dat hcp Solidhcp0"$i".dat
	echo "R"$i" cal ok"
done
for i in $(seq 10 20)
do
	./solid.out ../bcc"$i".dat bcc Solidbcc"$i".dat
echo "bcc ok"
	./solid.out ../fcc"$i".dat fcc Solidfcc"$i".dat
echo "fcc ok"
	./solid.out ../hcp"$i".dat hcp Solidhcp"$i".dat
	echo "R"$i" cal ok"
done
exit 0

