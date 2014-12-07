#!/bin/sh

if [ -z "$1" ]
then
    echo "No filename supplied"
    exit 0
fi

echo "Killing X..."
killall X

echo "Mouting debugfs..."
mount -t debugfs debugfs /sys/kernel/debug

echo "Enabling mmiotrace..."
echo mmiotrace > /sys/kernel/debug/tracing/current_tracer

echo "Start storing the trace..."
cat /sys/kernel/debug/tracing/trace_pipe > $1 &

echo "Launching X..."
X -config /home/hakzsam/xorg-nouveau.conf :1 &

echo "Marking X has been launched..."
echo "X is up" > /sys/kernel/debug/tracing/trace_marker
