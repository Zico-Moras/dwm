#!/bin/sh

# Set the wallpaper in the background
feh --bg-scale ~/dwm/wallpapers/day/wallpaper_fallen_angel_close.jpg

# Rotate/check wallpaper every 5 minutes
#(
#  while true; do
#    ~/scripts/set_wallpaper.sh
#    sleep 300
#  done
#) &

while true; do
	# Log stderror to a file
	dwm 2>  ~/.dwm.log
done
