#!/bin/bash
strategy_tests() {
    echo [Different pivoting strategies] >> time.log
    for i in 1 2 3 4; do
        echo "Population $i:" >> time.log
        for strategy in l r m; do
            ./QuickSort "./data/population$i.csv" $strategy 1 "./out/pop$i-$strategy.csv" >> time.log
            ./test.sh "./out/pop$i-$strategy.csv" >> time.log
            check_test_failure $?
            echo >> time.log
        done
    done
}

hybrid_tests() {
    echo [Hybrid algorithm] >> time.log
    thresholds=(1 15 120 2000 3600 5700 7950 9900 13600)
    for i in 1 2 3 4; do
        echo "Population $i:" >> time.log
        for threshold in "${thresholds[@]}"; do
            ./QuickSort "./data/population$i.csv" r $threshold "./out/pop$i-hybrid-r-$threshold.csv" >> time.log
            ./test.sh "./out/pop$i-hybrid-r-$threshold.csv" >> time.log
            check_test_failure $?
            echo >> time.log
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