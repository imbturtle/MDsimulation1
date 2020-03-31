#!/bin/bash
echo "cal solid"
for i in $(seq 1 9)
do
	./tanasolid.out AveBOPbcc0"$i".dat bcc Tanasolidbcc0"$i".dat 
echo "bcc ok"
	./tanasolid.out AveBOPfcc0"$i".dat fcc Tanasolidfcc0"$i".dat 
echo "fcc ok"
	./tanasolid.out AveBOPhcp0"$i".dat hcp Tanasolidhcp0"$i".dat 
	echo "R"$i" cal ok"
done
for i in $(seq 10 20)
do
	./tanasolid.out AveBOPbcc"$i".dat bcc Tanasolidbcc"$i".dat 
echo "bcc ok"
	./tanasolid.out AveBOPfcc"$i".dat fcc Tanasolidfcc"$i".dat 
echo "fcc ok"
	./tanasolid.out AveBOPhcp"$i".dat hcp Tanasolidhcp"$i".dat 
	echo "R"$i" cal ok"
done
exit 0

