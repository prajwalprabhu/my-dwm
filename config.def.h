/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int smartgaps          = 0;       /* 1 means no outer gap when there is only one window */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e","vifmrun" , NULL };
const char *spcmd3[] = {"st", "-n", "spcam", "-g", "144x41","-e","bc", NULL };
const char *spcmd4[] = {"st", "-n", "spmus", "-g"  "120x34","-e","mocp",NULL};
static Sp scratchpads[] = {
	/* name          cmd  */
{"spterm",      spcmd1},
	{"spvifm",    spcmd2},
	{"cam",   spcmd3},
	{"mocp",spcmd4},
};

static const char *const autostart[] = {
   NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "xdman-Main",NULL,      NULL,       0,            1,           -1},
	{ "Brave-browser",NULL,   NULL,       2,            0,           -1 },
	{ "St",       NULL,       "gtop",     4,            0,           -1},
	{ NULL,       NULL,           "Save File",0,            1,           -1 },
	{ NULL,		  "spterm",		NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "spfm",		NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		  "spcam",	    NULL,		SPTAG(2),		1,			 -1 },
	{ NULL,       "spmus",     NULL,       SPTAG(3),       1,           -1 },
	{ "mpv",      "gl",        "video0 - mpv",0,             1,            -1},
	{  NULL,       NULL,        "Open Folder",0,             1,            -1},
     { NULL,       NULL,        "Open File", 0,             1,            -1}

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "vanitygaps.c"
#include "movestack.c"
#include "shiftview.c"
#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "|M|",      centeredmaster },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[]=",      tile },
	{ ">M>",      centeredfloatingmaster },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
	{  "HHH",      grid },
	{  "[D]",     deck },
	{   "[B]",    bstack },
	{NULL,NULL},

};

/* key definitions */
#define MODKEY Mod4Mask
#define Alt Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
/* static const char scratchpadname[] = {"scratchpad"}; */
/* static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL }; */

static const char *layoutmenu_cmd = "layoutmenu.sh";
#include<X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ Alt,       			              XK_Return, togglescratch,  {.ui = 0}},
	{ Alt|ShiftMask,                XK_Return, togglescratch,  {.ui = 1} },
	{ Alt|ShiftMask,                XK_c,      togglescratch,  {.ui = 2} },
	{ Alt,                          XK_m,      togglescratch,  {.ui = 3}},
	{ MODKEY|ShiftMask,		          XK_Return, spawn,          SHCMD("thunar")},
	{ Alt,                          XK_f,      spawn,          SHCMD("st -e ~/.config/vifm/scripts/vifmrun")},
	{ Alt,                          XK_Escape, spawn,          SHCMD("st -e gtop")},
	{ Alt,                          XK_v,      spawn,          SHCMD("code")},
	{ Alt|ShiftMask,				                  XK_e,	   spawn,	           SHCMD("dmenuunicode")},
	{ Alt,				                  XK_c,	   spawn,          SHCMD("clipmenu")},
	{ Alt,				                  XK_b,	   spawn,          SHCMD("brave")},
	{ Alt,				                  XK_n,	   spawn,          SHCMD("st -e nmtui")},
	{ Alt,                          XK_w,    spawn,          SHCMD("pkill -f /dev/video0 ||mpv /dev/video0") },
  { Alt,                          XK_e,    spawn,          SHCMD("emacsclient -c") },

	{ MODKEY,			                  XK_z,	   incrgaps,       {.i=+3}},
	{ MODKEY|ShiftMask,		          XK_z,	   incrgaps,	   {.i=-3}},
	{ MODKEY|ControlMask,           XK_z,    defaultgaps,   {.i=0 }},
	{ MODKEY,			                  XK_a,      togglegaps,	   {0}},
	{ MODKEY,                       XK_Print,  spawn,          SHCMD("gnome-screenshot") } ,
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1} },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1} },
	{ MODKEY,                       XK_equal,   incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,   incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
//	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_c,      killunsel,       {0}},
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_i,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_p,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_bracketleft,setlayout,  {.v = &layouts[7]} },
	{ MODKEY,                       XK_bracketright,setlayout, {.v = &layouts[8]} },
	{ MODKEY,                       XK_r,      setlayout,       {.v=&layouts[9]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	{ MODKEY,			                  XK_Page_Up,shiftview,      {.i=+1}},
	{ MODKEY,			                  XK_Page_Down,shiftview,     {.i=-1}},
	{ MODKEY,                       XK_g,        shiftview,      {.i=-1} },
	{ MODKEY,                       XK_semicolon,shiftview,      {.i=+1} },
	{ 0,                            XF86XK_AudioPrev,spawn,    SHCMD("mocp --previous && notify-send 'MOCP'$(mocp -Q %title)")},
	{ 0,                            XF86XK_AudioNext,spawn,    SHCMD("mocp --next && notify-send 'MOCP'$(mocp -Q %title)") },
	{ 0,                            XF86XK_AudioPlay,spawn,    SHCMD("playerctl play-pause || mocp --toggle-pause && notify-send 'MOCP'$(mocp -Q %title)") },
	{ 0,                            XF86XK_MonBrightnessUp, spawn, SHCMD("xbacklight +5")},
	{ 0,                            XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -5")},
	{ MODKEY,                            XK_F1,          spawn,    SHCMD("man -T pdf dwm | zathura -") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,             XK_x,      spawn,         SHCMD("sysact") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        layoutmenu,     {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      movemouse,      {.i = 1} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button3,      resizemouse,    {.i = 1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

