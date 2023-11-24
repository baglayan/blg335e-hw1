#!/bin/bash
strategy_tests() {
    echo [Different pivoting strategies] >> /home/ubuntu/hostVolume/hw1/time.log
    for i in 1 2 3 4; do
        echo "Population $i:" >> /home/ubuntu/hostVolume/hw1/time.log
        for strategy in l r m; do
            /home/ubuntu/hostVolume/hw1/QuickSort "/home/ubuntu/hostVolume/hw1/data/population$i.csv" $strategy 1 "/home/ubuntu/hostVolume/hw1/out/pop$i-$strategy.csv" >> /home/ubuntu/hostVolume/hw1/time.log
            /home/ubuntu/hostVolume/hw1/test.sh "/home/ubuntu/hostVolume/hw1/out/pop$i-$strategy.csv" >> /home/ubuntu/hostVolume/hw1/time.log
            check_test_failure $?
            echo >> /home/ubuntu/hostVolume/hw1/time.log
        done
    done
}

hybrid_tests() {
    echo [Hybrid algorithm] >> /home/ubuntu/hostVolume/hw1/time.log
    thresholds=(1 15 120 2000 3600 5700 7950 9900 13600)
    for i in 1 2 3 4; do
        echo "Population $i:" >> /home/ubuntu/hostVolume/hw1/time.log
        for threshold in "${thresholds[@]}"; do
            /home/ubuntu/hostVolume/hw1/QuickSort "/home/ubuntu/hostVolume/hw1/data/population$i.csv" r $threshold "/home/ubuntu/hostVolume/hw1/out/pop$i-hybrid-r-$threshold.csv" >> /home/ubuntu/hostVolume/hw1/time.log
            /home/ubuntu/hostVolume/hw1/test.sh "/home/ubuntu/hostVolume/hw1/out/pop$i-hybrid-r-$threshold.csv" >> /home/ubuntu/hostVolume/hw1/time.log
            check_test_failure $?
            echo >> /home/ubuntu/hostVolume/hw1/time.log
        done
    done
}


touch compile.log
>compile.log
echo [Compile] >>compile.log
/usr/bin/g++ -fdiagnostics-color=always -g /home/ubuntu/hostVolume/hw1/QuickSort.cpp -o /home/ubuntu/hostVolume/hw1/QuickSort >>compile.log
touch time.log
>time.log

check_test_failure() {
    if [ "$1" -ne 0 ]; then
        echo "Test failed with unsorted output."
        exit 1
    fi
}

if [ "$1" = "-h" ]; then
    hybrid_tests
    # cat time.log
    exit 0
fi

strategy_tests
hybrid_tests

# cat time.log