#!/bin/sh

# Set the wallpaper in the background
feh --bg-scale ~/Downloads/wallpaper.jpg

while true; do
	# Log stderror to a file
	dwm 2>  ~/.dwm.log
done
