#!/bin/bash

#
# Reload local Nouveau kernel module.
#

# Unbind fbcon before removing Nouveau kernel module.
echo 0 > /sys/class/vtconsole/vtcon0/bind
echo 0 > /sys/class/vtconsole/vtcon1/bind
sleep 0.5

# Remove kernel modules related to Nouveau.
rmmod nouveau || exit 1
rmmod drm_kms_helper
rmmod ttm
rmmod drm

# Reload required kernel modules for Nouveau.
modprobe drm_kms_helper
modprobe i2c_algo_bit
modprobe ttm
modprobe drm rnodes=1

# Load local Nouveau kernel module.
sleep 1
insmod nouveau.ko debug=debug

dmesg
