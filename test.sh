#!/bin/bash
for i in `seq 3000 3100`;
do
        ./client $i 10000 >> res10000.csv
done   


