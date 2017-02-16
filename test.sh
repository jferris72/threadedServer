#!/bin/bash
for i in `seq 8000 8100`;
do
        ./client $i 10 >> res10_2.csv
done   


