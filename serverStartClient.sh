#!/bin/bash
for i in `seq 3000 3100`;
do
        ./server $i 10000 &
done   
