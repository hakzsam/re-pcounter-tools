#!/bin/bash

echo "Mouting debugfs..."
mount -t debugfs debugfs /sys/kernel/debug

echo "Enabling mmiotrace..."
echo mmiotrace > /sys/kernel/debug/tracing/current_tracer

echo "Start storing the trace..."
cat /sys/kernel/debug/tracing/trace_pipe > /home/hakzsam/mmiotrace-dump.txt &

echo "modprobe nvidia start" > /sys/kernel/debug/tracing/trace_marker
modprobe nvidia
echo "modprobe nvidia end" > /sys/kernel/debug/tracing/trace_marker

echo "vectorAdd start" > /sys/kernel/debug/tracing/trace_marker
cd /opt/cuda/samples/0_Simple/vectorAdd
./vectorAdd
echo "vectorAdd end" > /sys/kernel/debug/tracing/trace_marker

echo "Disabling mmiotrace..."
echo nop > /sys/kernel/debug/tracing/current_tracer
