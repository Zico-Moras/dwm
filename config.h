/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = {
    "JetBrainsMono Nerd Font:size=13",
    "monospace:size=13",
    "Noto Color Emoji:size=13"
};
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=15";
static const char col_gray1[]       = "#282828"; // Gruvbox Dark Background
static const char col_gray2[]       = "#504945"; // Gruvbox Selection/Gray
static const char col_gray3[]       = "#bdae93"; // Gruvbox Foreground (Muted)
static const char col_gray4[]       = "#ebdbb2"; // Gruvbox Foreground (Bright)
static const char col_cyan[]        = "#d65d0e"; // Gruvbox Orange (Accent)
static const char *colors[][3]      = {
    /* fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           0,           -1 },
	{ "wifi-float", NULL,      NULL,       0,           1,           1,           -1 },
	{ "bt-float",  NULL,      NULL,       0,            1,           1,           -1 },
	{ "audio-float",  NULL,      NULL,       0,         1,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *upvol[]   = { "/bin/sh", "-c", "wpctl set-volume @DEFAULT_AUDIO_SINK@ 2%+; pkill -RTMIN+10 dwmblocks", NULL };
static const char *downvol[] = { "/bin/sh", "-c", "wpctl set-volume @DEFAULT_AUDIO_SINK@ 2%-; pkill -RTMIN+10 dwmblocks", NULL };
static const char *mutevol[] = { "/bin/sh", "-c", "wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; pkill -RTMIN+10 dwmblocks", NULL };
static const char *light_up[]   = { "/usr/bin/brightnessctl", "s", "2%+", NULL };
static const char *light_down[] = { "/usr/bin/brightnessctl", "s", "2%-", NULL };
static const char *flameshot[] = { "flameshot", "gui", NULL };
static const char *lockcmd[] = { "slock", NULL };
static const char *wificmd[] = { "alacritty", "--class", "wifi-float", "-e", "impala", NULL };
static const char *btcmd[]   = { "alacritty", "--class", "bt-float", "-e", "bluetui", NULL };

#include "movestack.c"
#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },       { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },       { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0,                            XF86XK_AudioLowerVolume,  spawn, {.v = downvol } },
	{ 0,                            XF86XK_AudioMute,         spawn, {.v = mutevol } },
	{ 0,                            XF86XK_AudioRaiseVolume,  spawn, {.v = upvol   } },
	{ 0,                            XF86XK_MonBrightnessUp,   spawn, {.v = light_up } },
	{ 0,                            XF86XK_MonBrightnessDown, spawn, {.v = light_down } },
	{ 0,                            XK_Print,                 spawn, {.v = flameshot } },
	{ MODKEY|ShiftMask,             XK_l,                     spawn, {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_n,                     spawn, {.v = wificmd } },
	{ MODKEY|ShiftMask,             XK_b,                     spawn, {.v = btcmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkStatusText,        0,              6,              sigstatusbar,   {.i = 6} },
	{ ClkStatusText,        0,              7,              sigstatusbar,   {.i = 7} },
	{ ClkStatusText,        0,              8,              sigstatusbar,   {.i = 8} },
	{ ClkStatusText,        0,              9,              sigstatusbar,   {.i = 9} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

