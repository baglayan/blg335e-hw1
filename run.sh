#!/bin/sh
strategy_tests() {
    echo [Different pivoting strategies] >>time.log
    echo Population 1: >>time.log
    ./QuickSort ./data/population1.csv l 1 ./out/pop1-l.csv >>time.log
    ./test.sh ./out/pop1-l.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population1.csv r 1 ./out/pop1-r.csv >>time.log
    ./test.sh ./out/pop1-r.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population1.csv m 1 ./out/pop1-m.csv >>time.log
    ./test.sh ./out/pop1-m.csv >>time.log
    echo >>time.log
    echo Population 2: >>time.log
    ./QuickSort ./data/population2.csv l 1 ./out/pop2-l.csv >>time.log
    ./test.sh ./out/pop2-l.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population2.csv r 1 ./out/pop2-r.csv >>time.log
    ./test.sh ./out/pop2-r.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population2.csv m 1 ./out/pop2-m.csv >>time.log
    ./test.sh ./out/pop2-m.csv >>time.log
    echo >>time.log
    echo Population 3: >>time.log
    ./QuickSort ./data/population3.csv l 1 ./out/pop3-l.csv >>time.log
    ./test.sh ./out/pop3-l.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population3.csv r 1 ./out/pop3-r.csv >>time.log
    ./test.sh ./out/pop3-r.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population3.csv m 1 ./out/pop3-m.csv >>time.log
    ./test.sh ./out/pop3-m.csv >>time.log
    echo >>time.log
    echo Population 4: >>time.log
    ./QuickSort ./data/population4.csv l 1 ./out/pop4-l.csv >>time.log
    ./test.sh ./out/pop4-l.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population4.csv r 1 ./out/pop4-r.csv >>time.log
    ./test.sh ./out/pop4-r.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population4.csv m 1 ./out/pop4-m.csv >>time.log
    ./test.sh ./out/pop4-m.csv >>time.log
    echo >>time.log
}

hybrid_tests() {
    echo [Hybrid algorithm] >>time.log
    echo Population 1: >>time.log
    ./QuickSort ./data/population1.csv r 1 ./out/pop1-hybrid-r-1.csv >>time.log
    ./test.sh ./out/pop1-hybrid-r-1.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population1.csv r 15 ./out/pop1-hybrid-r-15.csv >>time.log
    ./test.sh ./out/pop1-hybrid-r-15.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population1.csv r 120 ./out/pop1-hybrid-r-120.csv >>time.log
    ./test.sh ./out/pop1-hybrid-r-120.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population1.csv r 2000 ./out/pop1-hybrid-r-2000.csv >>time.log
    ./test.sh ./out/pop1-hybrid-r-2000.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population1.csv r 3600 ./out/pop1-hybrid-r-3600.csv >>time.log
    ./test.sh ./out/pop1-hybrid-r-3600.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population1.csv r 5700 ./out/pop1-hybrid-r-5700.csv >>time.log
    ./test.sh ./out/pop1-hybrid-r-5700.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population1.csv r 7950 ./out/pop1-hybrid-r-7950.csv >>time.log
    ./test.sh ./out/pop1-hybrid-r-7950.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population1.csv r 9900 ./out/pop1-hybrid-r-9900.csv >>time.log
    ./test.sh ./out/pop1-hybrid-r-9900.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population1.csv r 13600 ./out/pop1-hybrid-r-13600.csv >>time.log
    ./test.sh ./out/pop1-hybrid-r-13600.csv >>time.log
    echo >>time.log

    echo Population 2: >>time.log
    ./QuickSort ./data/population2.csv r 1 ./out/pop2-hybrid-r-1.csv >>time.log
    ./test.sh ./out/pop2-hybrid-r-1.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population2.csv r 15 ./out/pop2-hybrid-r-15.csv >>time.log
    ./test.sh ./out/pop2-hybrid-r-15.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population2.csv r 120 ./out/pop2-hybrid-r-120.csv >>time.log
    ./test.sh ./out/pop2-hybrid-r-120.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population2.csv r 2000 ./out/pop2-hybrid-r-2000.csv >>time.log
    ./test.sh ./out/pop2-hybrid-r-2000.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population2.csv r 3600 ./out/pop2-hybrid-r-3600.csv >>time.log
    ./test.sh ./out/pop2-hybrid-r-3600.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population2.csv r 5700 ./out/pop2-hybrid-r-5700.csv >>time.log
    ./test.sh ./out/pop2-hybrid-r-5700.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population2.csv r 7950 ./out/pop2-hybrid-r-7950.csv >>time.log
    ./test.sh ./out/pop2-hybrid-r-7950.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population2.csv r 9900 ./out/pop2-hybrid-r-9900.csv >>time.log
    ./test.sh ./out/pop2-hybrid-r-9900.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population2.csv r 13600 ./out/pop2-hybrid-r-13600.csv >>time.log
    ./test.sh ./out/pop2-hybrid-r-13600.csv >>time.log
    echo >>time.log

    echo Population 3: >>time.log
    ./QuickSort ./data/population3.csv r 1 ./out/pop3-hybrid-r-1.csv >>time.log
    ./test.sh ./out/pop3-hybrid-r-1.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population3.csv r 15 ./out/pop3-hybrid-r-15.csv >>time.log
    ./test.sh ./out/pop3-hybrid-r-15.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population3.csv r 120 ./out/pop3-hybrid-r-120.csv >>time.log
    ./test.sh ./out/pop3-hybrid-r-120.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population3.csv r 2000 ./out/pop3-hybrid-r-2000.csv >>time.log
    ./test.sh ./out/pop3-hybrid-r-2000.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population3.csv r 3600 ./out/pop3-hybrid-r-3600.csv >>time.log
    ./test.sh ./out/pop3-hybrid-r-3600.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population3.csv r 5700 ./out/pop3-hybrid-r-5700.csv >>time.log
    ./test.sh ./out/pop3-hybrid-r-5700.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population3.csv r 7950 ./out/pop3-hybrid-r-7950.csv >>time.log
    ./test.sh ./out/pop3-hybrid-r-7950.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population3.csv r 9900 ./out/pop3-hybrid-r-9900.csv >>time.log
    ./test.sh ./out/pop3-hybrid-r-9900.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population3.csv r 13600 ./out/pop3-hybrid-r-13600.csv >>time.log
    ./test.sh ./out/pop3-hybrid-r-13600.csv >>time.log
    echo >>time.log

    echo Population 4: >>time.log
    ./QuickSort ./data/population4.csv r 1 ./out/pop4-hybrid-r-1.csv >>time.log
    ./test.sh ./out/pop4-hybrid-r-1.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population4.csv r 15 ./out/pop4-hybrid-r-15.csv >>time.log
    ./test.sh ./out/pop4-hybrid-r-15.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population4.csv r 120 ./out/pop4-hybrid-r-120.csv >>time.log
    ./test.sh ./out/pop4-hybrid-r-120.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population4.csv r 2000 ./out/pop4-hybrid-r-2000.csv >>time.log
    ./test.sh ./out/pop4-hybrid-r-2000.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population4.csv r 3600 ./out/pop4-hybrid-r-3600.csv >>time.log
    ./test.sh ./out/pop4-hybrid-r-3600.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population4.csv r 5700 ./out/pop4-hybrid-r-5700.csv >>time.log
    ./test.sh ./out/pop4-hybrid-r-5700.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population4.csv r 7950 ./out/pop4-hybrid-r-7950.csv >>time.log
    ./test.sh ./out/pop4-hybrid-r-7950.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population4.csv r 9900 ./out/pop4-hybrid-r-9900.csv >>time.log
    ./test.sh ./out/pop4-hybrid-r-9900.csv >>time.log
    echo >>time.log
    ./QuickSort ./data/population4.csv r 13600 ./out/pop4-hybrid-r-13600.csv >>time.log
    ./test.sh ./out/pop4-hybrid-r-13600.csv >>time.log
    echo >>time.log
}


touch compile.log
>compile.log
echo [Compile] >>compile.log
/usr/bin/g++ -fdiagnostics-color=always -g /home/ubuntu/hostVolume/hw1/QuickSort.cpp -o /home/ubuntu/hostVolume/hw1/QuickSort >>compile.log
touch time.log
>time.log

if [ "$1" = "-h" ]; then
    hybrid_tests
    # cat time.log
    exit 0
fi

strategy_tests
hybrid_tests

# cat time.log