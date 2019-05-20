#!/bin/bash
cd ../
ls
make clean
make 
if [ $2 == 1 ];then
	clear
	clear
fi
cd bin 
./tp2 "../entradas/cidades$1.txt"
