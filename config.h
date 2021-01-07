/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h> // for XF86 keys

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gaps pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int bar_height         = 35;        /* 0 means that dwm will calculate bar height */
static const char *fonts[]          = { "UbuntuMono Nerd Font:size=18" };
static const char dmenufont[]       = "monospace:size=18";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";

static const char col_bg[]			= "#454545";
static const char col_fg[]			= "#e5e5e5";

static const char col_cyan[]        = "#005577";
static const char col_magenta[]     = "#a47de9";

static const char *colors[][3]      = {
	/*               fg        bg       border   */
	[SchemeNorm] = { col_fg, col_bg, col_gray2 },
	[SchemeSel]  = { col_gray4, col_magenta,  col_cyan  },
	[SchemeTitle]  = { col_fg, col_bg,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Sxiv",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "侀 ",      tile },    /* first entry is default */
	{ "恵 ",      NULL },    /* no layout function means floating behavior */
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

/* Needed in dwm.c */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run", NULL };

/* commands */
static const char *launch_terminal[] = { "st", NULL };
static const char *launch_codium[] = { "codium", NULL };
static const char *launch_browser[] = { "vivaldi-stable", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,			            XK_Return, spawn,          {.v = launch_terminal } },
	{ MODKEY,			            XK_c,	   spawn,          {.v = launch_codium } },
	{ MODKEY,			            XK_m,	   spawn,          {.v = launch_browser } },
	
	{ 0, XF86XK_AudioRaiseVolume,   spawn,      SHCMD("vol up") },
	{ 0, XF86XK_AudioLowerVolume,   spawn,      SHCMD("vol down") },
	{ 0, XF86XK_AudioMute,    		spawn,      SHCMD("vol toggle") },

	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 10") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 10") },

	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} }, // send focused window to big position
	{ MODKEY|ShiftMask,             XK_Tab,    view,           {0} }, // prev tag
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} }, // kill window
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, // tile
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, // floating
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
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
	{ MODKEY|ShiftMask,             XK_Escape, quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = launch_terminal } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};