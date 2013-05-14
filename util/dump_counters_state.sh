#!/bin/bash

filename=$1
echo -n "" > $filename

echo "<dump a000 0800>" >> $filename
nvapeek a000 0800 >> $filename
