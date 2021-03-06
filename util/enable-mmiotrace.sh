#!/bin/bash

export LD_LIBRARY_PATH=/opt/cuda/extras/CUPTI/lib64/


echo "Removing NVidia module..."
rmmod nvidia

echo "Mouting debugfs..."
mount -t debugfs debugfs /sys/kernel/debug

echo "Enabling mmiotrace..."
echo mmiotrace > /sys/kernel/debug/tracing/current_tracer

echo "Start storing the trace..."
cat /sys/kernel/debug/tracing/trace_pipe > /home/hakzsam/mmiotrace-dump.txt &

modprobe nvidia

echo "Launching X..."
X -config /home/hakzsam/xorg-nvidia-pci1.conf  &

echo "Marking X has been launched..."
echo "X is up" > /sys/kernel/debug/tracing/trace_marker

echo "cupti start" > /sys/kernel/debug/tracing/trace_marker
/opt/cuda/extras/CUPTI/sample/callback_event/callback_event 1 sm_cta_launched
echo "cupti end" > /sys/kernel/debug/tracing/trace_marker

echo nop > /sys/kernel/debug/tracing/current_tracer

#cd /home/hakzsam/programming/re-pcounter-tools/src
#./cupti_trace --trace NV86 --event gld_coherent &> /home/hakzsam/cupti_trace_gld_coherent.trace

#cd /home/hakzsam
#xz -9 mmiotrace-dump.txt
#tar -czvf nv86-full-report-pcounter.tgz mmiotrace-dump.txt.xz valgrind_mmt.trace cupti_trace_gld_coherent.trace
