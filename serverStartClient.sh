#!/bin/bash
for i in `seq 8000 8100`;
do
        ./server2 $i 10 &
done   
