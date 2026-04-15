#!/bin/sh

# Set the wallpaper in the background
feh --bg-scale ~/dwm/wallpaper_2.png

while true; do
	# Log stderror to a file
	dwm 2>  ~/.dwm.log
done
