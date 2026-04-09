#!/bin/sh

# --- Environment & Input ---
# Force Alacritty/Rust apps to use X11 backend instead of Wayland
export WINIT_UNIX_BACKEND=x11

# Set keyboard to US layout and map Right Alt as a 'Compose Key' for symbols
setxkbmap -layout us -option compose:ralt &

# --- System Services ---
# Blue light filter: Sets coords (Porto) and color temp (Day:6500K / Night:3500K)
redshift -l 41.1:-8.6 -t 6500:3500 &

# Links the system's X screen saver to the 'slock' screen locker
xss-lock -- /usr/local/bin/slock &

# Idle timer: Locks screen after 300s (5 mins) if not in fullscreen (videos/games)
xidlehook \
  --not-when-fullscreen \
  --timer 300 '/usr/local/bin/slock' '' &

# --- UI & Window Management ---
# Status bar for dwm (CPU, RAM, Time, etc.)
dwmblocks &

# Compositor for transparency, shadows, and fixing screen tearing
picom &

# --- Final Step ---
# Start the window manager script (must be 'exec' and the last line)
exec ~/startdwm.sh
