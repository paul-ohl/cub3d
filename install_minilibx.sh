#!/bin/sh
# Installs minilibX on your linux machine in /usr/local/lib and /usr/local/include

git clone https://github.com/42Paris/minilibx-linux.git to_delete
cd to_delete || exit
./configure
sudo mv libmlx.a /usr/local/lib/
sudo mv libmlx_Linux.a /usr/local/lib/
sudo mv mlx.h /usr/local/include/
cd .. || exit
rm -rf to_delete
echo "Minilibx installed!"

