#!/bin/bash

filename=$1
echo -n "" > $filename

echo "<dump 400000 10000>" >> $filename
nvapeek 400000 10000 >> $filename
