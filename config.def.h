/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 12;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *altbarcmd        = "$HOME/.config/polybar/launch.sh"; /* Alternate bar launch command */
static const int vertpad			= 0;		/* vertical padding of bar */
static const int sidepad			= 0;		/* horizontal padding of bar */
static const int startontag			= 1;		/* 0 means no tag active on start */
static const char *fonts[]          = { "Noto Sans CJK JP Bold:style=Regular:size=10", "Noto Sans Nerd Font:style=Regular:size=11", "Font Awesome 6 Brands:style=Regular:size=10" };
static const char dmenufont[]       = "Noto Sans:style=Regular:size=11";
static const char col_nor_bg[]      = "#222222";
static const char col_nor_border[]	= "#444444";
static const char col_nor_fg[]		= "#bbbbbb";
static const char col_sel_fg[]		= "#eeeeee";
static const char col_sel_border[]	= "#ff8800";
static const char *colors[][3]		= {
	/*               fg				bg				border   */
	[SchemeNorm] = { col_nor_fg,	col_nor_bg,		col_nor_border },
	[SchemeSel]  = { col_sel_fg,	col_sel_border,	col_sel_border },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
// static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const unsigned int ulinepad	= 4;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class	instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    	NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "firefox", 	NULL,     NULL,           1 << 2,    0,          0,          -1,        -1 },
	{ "Steam",	 	NULL,     NULL,           1 << 3,    0,          0,          -1,		 0 },
	{ "discord",	NULL,	  NULL,			  1 << 7,	 0,			 0,			 -1,		 1 },
	{ "Spotify", 	NULL,     NULL,           1 << 8,    0,          0,          -1,		 1 },
	{ "Alacritty",	NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      	NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact		= 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster		= 1;    /* number of clients in master area */
static const int resizehints	= 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;	/* 1 will force focus on the fullscreen window */

#include "tatami.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "|+|",      tatami },
//	{ "><>",      NULL },    /* no layout function means floating behavior */
//	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/local/bin/st", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_nor_bg, "-nf", col_nor_fg, "-sb", col_sel_border, "-sf", col_sel_fg, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *logoutcmd[] = { "/mnt/media/dev/sh_projects/prompt", "-r", "-p", "Logout?", "-c", "dm-tool switch-to-greeter", NULL };
static const char *rebootcmd[] = { "/mnt/media/dev/sh_projects/prompt", "-r", "-p", "Reboot?", "-c", "reboot", NULL };
static const char *shutdowncmd[] = { "/mnt/media/dev/sh_projects/prompt", "-r", "-p", "Shutdown?", "-c", "shutdown now", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,						XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,				XK_l,	   spawn,          {.v = logoutcmd } },
	{ MODKEY,						XK_Delete, spawn,          {.v = rebootcmd } },
	{ MODKEY|ShiftMask,				XK_Delete, spawn,	       {.v = shutdowncmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,						XK_x,      killclient,     {0} },
	{ MODKEY,						XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,				XK_t,	   setlayout,	   {.v = &layouts[1]} },
//	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
//	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
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

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

