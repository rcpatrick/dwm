/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
/* solarized colors */
static const char col_sol_red[]     = "#dc322f";
static const char col_sol_orange[]  = "#cb4b16";
static const char col_sol_yellow[]  = "#b58900";
static const char col_sol_green[]   = "#859900";
static const char col_sol_blue[]    = "#268bd2";
static const char col_sol_cyan[]    = "#2aa198";
static const char col_sol_violet[]  = "#6c71c4";
static const char col_sol_magenta[] = "#d33682";
static const char *colors[][3]      = {
	/*               fg         bg            border   */
	[SchemeNorm] = { col_gray3, col_gray1,    col_gray2 },
	[SchemeSel]  = { col_gray4, col_sol_cyan, col_sol_orange },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	/*{ MODKEY,                       XK_Tab,    view,           {0} },*/
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	/* My custom bindings */
        { MODKEY,                       XK_b,      spawn,          SHCMD("$BROWSER") },
        { MODKEY|ShiftMask,             XK_f,      spawn,          SHCMD("st lf") },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("exec ~/.local/bin/scripts/desktopbg.sh") },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("st ~/.local/bin/scripts/weather.sh") },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("exec radar $(cat ~/.local/bin/scripts/radar.txt)") },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("exec ~/.local/bin/scripts/changelocation.sh") },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("st newsboat") },
	{ MODKEY|ShiftMask,             XK_z,      spawn,          SHCMD("st ~/.local/bin/scripts/startmutt.sh") },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("st ncmpcpp") },
	{ MODKEY|ShiftMask,             XK_j,      spawn,          SHCMD("exec ~/.local/bin/scripts/dmenuunicode.sh") },
	{ MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("st lf /media/usb/") },
	{ MODKEY|ShiftMask,             XK_i,      spawn,          SHCMD("st lf /mnt/win/Users/Ray/") },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("st lf ~/doc/lib/") },
        { 0,               XF86XK_Calculator,      spawn,          SHCMD("st bc -lq") },
	{ 0,                     XF86XK_Mail,      spawn,          SHCMD("st ~/.local/bin/scripts/startmutt.sh") },
	{ 0,                XF86XK_Favorites,      spawn,          SHCMD("st ~/.local/bin/scripts/dictionary.sh") },
	{ 0|ShiftMask,      XF86XK_Favorites,      spawn,          SHCMD("st ~/.local/bin/scripts/bible.sh") },

	{ MODKEY|ShiftMask,             XK_F5,     spawn,          SHCMD("st ~/.local/bin/scripts/clearcache.sh") },

	/* Volume controls */
	{ 0, XF86XK_AudioMute,           spawn,     SHCMD("amixer -q sset Master toggle && kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,    spawn,     SHCMD("amixer -q sset Master 5%+ && kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,    spawn,     SHCMD("amixer -q sset Master 5%- && kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_MonBrightnessDown,   spawn,     SHCMD("xbacklight -dec 10") },
	{ 0, XF86XK_MonBrightnessUp,     spawn,     SHCMD("xbacklight -inc 10") },

	/* Screenshot */
	{ 0, 		XK_Print,	spawn,	SHCMD("~/.local/bin/scripts/screenshot.sh") },
	{ 0|ShiftMask,	XK_Print,	spawn,	SHCMD("~/.local/bin/scripts/screenshot.sh s") },
	
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
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

