#!/bin/sh
touch time.log
> time.log
echo [Different pivoting strategies] >> time.log
echo Population 1: >> time.log
./QuickSort population1.csv l 1 output.csv >> time.log
./QuickSort population1.csv r 1 output.csv >> time.log
./QuickSort population1.csv m 1 output.csv >> time.log
echo Population 2: >> time.log
./QuickSort population2.csv l 1 output.csv >> time.log
./QuickSort population2.csv r 1 output.csv >> time.log
./QuickSort population2.csv m 1 output.csv >> time.log
echo Population 3: >> time.log
./QuickSort population3.csv l 1 output.csv >> time.log
./QuickSort population3.csv r 1 output.csv >> time.log
./QuickSort population3.csv m 1 output.csv >> time.log
echo Population 4: >> time.log
./QuickSort population4.csv l 1 output.csv >> time.log
./QuickSort population4.csv r 1 output.csv >> time.log
./QuickSort population4.csv m 1 output.csv >> time.log
echo [Hybrid algorithm] >> time.log
./QuickSort population4.csv r 1 output.csv >> time.log
./QuickSort population4.csv r 15 output.csv >> time.log
./QuickSort population4.csv r 120 output.csv >> time.log
./QuickSort population4.csv r 2000 output.csv >> time.log
./QuickSort population4.csv r 3600 output.csv >> time.log
./QuickSort population4.csv r 5700 output.csv >> time.log
./QuickSort population4.csv r 7950 output.csv >> time.log
./QuickSort population4.csv r 9900 output.csv >> time.log
./QuickSort population4.csv r 13600 output.csv >> time.log
cat time.log