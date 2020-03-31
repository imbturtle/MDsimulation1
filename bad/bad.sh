#!/bin/bash
echo "cal bad"
for i in $(seq 1 9)
do
	./bad.out ../bcc0"$i".dat bcc BADbcc0"$i".dat
	echo "bcc ok"
	./bad.out ../fcc0"$i".dat fcc BADfcc0"$i".dat
	echo "fcc ok"
	./bad.out ../hcp0"$i".dat hcp BADhcp0"$i".dat
	echo "R"$i" cal ok"
done
for i in $(seq 10 20)
do
	./bad.out ../bcc"$i".dat bcc BADbcc"$i".dat
	echo "bcc ok"
	./bad.out ../fcc"$i".dat fcc BADfcc"$i".dat
	echo "fcc ok"
	./bad.out ../hcp"$i".dat hcp BADhcp"$i".dat
	echo "R"$i" cal ok"
done
exit 0

