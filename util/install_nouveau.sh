#!/bin/sh

# Uninstall NVidia's driver.
pacman -Rdds nvidia-304xx-utils nvidia-304xx

# Install nouveau's driver.
pacman -S xf86-video-nouveau
