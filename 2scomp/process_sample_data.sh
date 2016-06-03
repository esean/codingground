#!/bin/bash
rm -f main
make
cat data.csv | fpget_csv_column.rb -n dec | ./main | awk '{print $2 " " $3}' > data.csv.out
cat data.csv.out | plotit.pl -p
