#!/bin/bash
echo "ana solid"
for i in $(seq 1 9)
do
	./catecrystal.out Solidbcc0"$i".dat bcc Crystalbcc0"$i".dat Anasolidbcc.dat 0.0"$i"
	./catecrystal.out Solidfcc0"$i".dat fcc Crystalfcc0"$i".dat Anasolidfcc.dat 0.0"$i"
	./catecrystal.out Solidhcp0"$i".dat hcp Crystalhcp0"$i".dat Anasolidhcp.dat 0.0"$i"
	echo "solid "$i" cal ok"
done
for i in $(seq 10 20)
do
	./catecrystal.out Solidbcc"$i".dat bcc Crystalbcc"$i".dat Anasolidbcc.dat 0."$i"
	./catecrystal.out Solidfcc"$i".dat fcc Crystalfcc"$i".dat Anasolidfcc.dat 0."$i"
	./catecrystal.out Solidhcp"$i".dat hcp Crystalhcp"$i".dat Anasolidhcp.dat 0."$i"
	echo "solid "$i" cal ok"
done
exit 0

