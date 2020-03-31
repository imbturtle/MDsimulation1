#!/bin/bash
echo "cal nd"
for i in $(seq 1 9)
do
	./nd.out ../bcc0"$i".dat bcc NDbcc0"$i".dat
	echo "bcc ok"
	./nd.out ../fcc0"$i".dat fcc NDfcc0"$i".dat
	echo "fcc ok"
	./nd.out ../hcp0"$i".dat hcp NDhcp0"$i".dat
	echo "R"$i" cal ok"
done
for i in $(seq 10 20)
do
	./nd.out ../bcc"$i".dat bcc NDbcc"$i".dat
	echo "bcc ok"
	./nd.out ../fcc"$i".dat fcc NDfcc"$i".dat
	echo "fcc ok"
	./nd.out ../hcp"$i".dat hcp NDhcp"$i".dat
	echo "R"$i" cal ok"
done
exit 0

