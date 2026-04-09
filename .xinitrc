export WINIT_UNIX_BACKEND=x11
setxkbmap -layout us -option compose:ralt &

redshift -l 41.1:-8.6 -t 6500:3500 &
xss-lock -- /usr/local/bin/slock &

xidlehook \
  --not-when-fullscreen \
  --timer 300 '/usr/local/bin/slock' '' &

dwmblocks &
picom &
exec ~/startdwm.sh
