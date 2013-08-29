#!/bin/bash
# nvidia -> nouveau

set -e

# check if root
if [[ $EUID -ne 0 ]]; then
    echo "You must be root to run this script. Aborting...";
    exit 1;
fi

sed -i 's/#*MODULES="nouveau"/MODULES="nouveau"/' /etc/mkinitcpio.conf

#pacman -Rdds --noconfirm nvidia nvidia-utils nvidia-libgl #lib32-nvidia-libgl
pacman -Rdds --noconfirm nvidia-304xx nvidia-304xx-utils #lib32-nvidia-libgl
pacman -S --noconfirm nouveau-dri xf86-video-nouveau #lib32-nouveau-dri

mkinitcpio -p linux
