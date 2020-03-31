#!/bin/bash
echo "ana gofr"
for i in $(seq 1 9)
do
	./anagofr.out ./gofrbcc0"$i".dat bcc"$i" anagofr.dat
done
for i in $(seq 10 20)
do
	./anagofr.out ./gofrbcc"$i".dat bcc"$i" anagofr.dat
done

for i in $(seq 1 9)
do
	./anagofr.out ./gofrfcc0"$i".dat fcc"$i" anagofr.dat
done
for i in $(seq 10 20)
do
	./anagofr.out ./gofrfcc"$i".dat fcc"$i" anagofr.dat
done
for i in $(seq 1 9)
do
	./anagofr.out ./gofrhcp0"$i".dat hcp"$i" anagofr.dat
done
for i in $(seq 10 20)
do
	./anagofr.out ./gofrhcp"$i".dat hcp"$i" anagofr.dat
done
exit 0
