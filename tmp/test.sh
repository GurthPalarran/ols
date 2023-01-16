#!/bin/bash

for ((i=42; i<=1000; i++))
do
    echo "Order $i"
    echo "Order $i" >> ./log
    ./ols -i $i -c ./test.cnf \
-s ./glucose \
-o ./test.out \
-m ./test.log \
-a ./answers/$i.answer \
>> ./log
done
