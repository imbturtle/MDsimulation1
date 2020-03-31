#!/bin/bash
echo "cal gofr"
for i in $(seq 1 9)
do
	./gofr.out ../bcc0"$i".dat bcc gofrbcc0"$i".dat
	echo "bcc ok"
	./gofr.out ../fcc0"$i".dat fcc gofrfcc0"$i".dat
	echo "fcc ok"
	./gofr.out ../hcp0"$i".dat hcp gofrhcp0"$i".dat
	echo "R"$i" cal ok"
done
for i in $(seq 10 20)
do
	./gofr.out ../bcc"$i".dat bcc gofrbcc"$i".dat
	echo "bcc ok"
	./gofr.out ../fcc"$i".dat fcc gofrfcc"$i".dat
	echo "fcc ok"
	./gofr.out ../hcp"$i".dat hcp gofrhcp"$i".dat
	echo "R"$i" cal ok"
done
exit 0

