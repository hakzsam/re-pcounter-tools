#!/bin/bash

filename=$1
echo -n "" > $filename

echo "<dump 0x13b000 4000>" >> $filename
nvapeek 0x13b000 4000 >> $filename


exit 0
# PGRAPH.CPG[0].TPC[0].XXX (except MP)
echo "<dump 500000 8000>" >> $filename
nvapeek 500000 8000 >> $filename


# PGRAPH.CPG[0].TPC[0].XXX (except MP)
echo "<dump 504000 600>" >> $filename
nvapeek 504000 600 >> $filename

# PBFB[0]
echo "<dump 110000 1000>" >> $filename
nvapeek 110000 1000 >> $filename

# PGRAPH.DISPATCH
echo "<dump 404000 400>" >> $filename
nvapeek 404000 400 >> $filename

# PGRAPH.MACRO
echo "<dump 404400 100>" >> $filename
nvapeek 404400 100 >> $filename

# PGRAPH.M2MF
echo "<dump 404600 200>" >> $filename
nvapeek 404600 200 >> $filename

# PGRAPH.DDATA
echo "<dump 404800 800>" >> $filename
nvapeek 404800 800 >> $filename

# PGRAPH.UNK5800
echo "<dump 405800 100>" >> $filename
nvapeek 405800 100 >> $filename

# PGRAPH.UNK5900
echo "<dump 405980 100>" >> $filename
nvapeek 405980 100 >> $filename

# PGRAPH.UNK5A00
echo "<dump 405a00 100>" >> $filename
nvapeek 405a00 100 >> $filename

# PGRAPH.UNK5B00
echo "<dump 405b00 100>" >> $filename
nvapeek 405b00 100 >> $filename

# PGRAPH.UNK6000
echo "<dump 406000 800>" >> $filename
nvapeek 406000 800 >> $filename

# PGRAPH.UNK6800
echo "<dump 406800 400>" >> $filename
nvapeek 406800 400 >> $filename

# PGRAPH.SKED
echo "<dump 407000 400>" >> $filename
nvapeek 407000 400 >> $filename

# PGRAPH.TPBUS
echo "<dump 407800 800>" >> $filename
nvapeek 407800 800 >> $filename

# PGRAPH.CCACHE
echo "<dump 408000 800>" >> $filename
nvapeek 408000 800 >> $filename


