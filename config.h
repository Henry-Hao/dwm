/* See LICENSE file for copyright and license details. */

#define TERMINAL         "alacritty"
#define TERMCLASS        "Alacritty"
/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Roboto Mono Nerd Font:size=10","JoyPixels:pixelsize=10:antialias=true:autohint=true" };
static const char dmenufont[]       = "Roboto Mono Nerd Font:size=10";
static const char normbgcolor[]     = "#222222";
static const char normbordercolor[] = "#444444";
static const char normfgcolor[]     = "#bbbbbb";
static const char selfgcolor[]      = "#eeeeee";
static const char selbordercolor[]  = "#770000";
static const char selbgcolor[]      = "#005577";
static const char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor},
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "--title", "vimwiki", "-e", "nvim", "-c", "VimwikiIndex", NULL };
const char *spcmd2[] = {"keepassxc", NULL };
const char *spcmd3[] = {TERMINAL, "--title", "float", "-e", "calc", "-f", "mono:pixelsize=24", NULL };
const char *spcmd4[] = {TERMINAL, "--title", "float", "-e", "htop",  NULL };
const char *spcmd5[] = {TERMINAL, "--title", "float", "-e", "nmtui",  NULL };
const char *spcmd6[] = {TERMINAL, "--title", "float", "-e", "pulsemixer",  NULL };
const char *spcmd7[] = {TERMINAL, "--title", "float", "-e", "calcurse",  NULL };
const char *spcmd8[] = {TERMINAL, "--title", "float", "-e", "pulsemixer", "--toogle-mute", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"vimwiki",       spcmd1},
	{"keepassxc",     spcmd2},
	{"calculator",    spcmd3},
	{"htop",          spcmd4},
	{"nmtui",         spcmd5},
	{"pulsemixer",    spcmd6},
	{"calcurse",      spcmd7},
	{"pulsemixer",    spcmd8},
};


/* tagging */
static const char *tags[] = { "1:💻", "2:🌐", "3:📁", "4", "5", "6", "7", "8", "9:💬" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance      title       tags mask     isfloating  monitor */
	{ NULL,       NULL,         "float",    0,            1,          -1 },
	{ NULL,       NULL,         "main",     1,            0,          -1 },
	{ "firefox",  NULL,         NULL,       1 << 1,       0,          -1 },
	{ "Pcmanfm",  NULL,         NULL,       1 << 2,       1,          -1 },
	{ "Skype",    NULL,         NULL,       1 << 8,       0,          -1 },
	{ NULL,       NULL,         "vimwiki",  SPTAG(0),     1,          -1 },
	{ NULL,       "keepassxc",  NULL,       SPTAG(1),     1,          -1 },

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("firefox") },
	{ NULL,                         XK_Print,  spawn,          SHCMD("flameshot gui") },
	{ MODKEY,                       XK_e,      spawn,          SHCMD(TERMINAL " --title float -e ranger") },
	{ MODKEY,                       XK_c,      togglescratch,  {.ui = 2 } }, // scratchpad for calculator
	{ MODKEY|ShiftMask,             XK_i,      togglescratch,  {.ui = 3 } }, // scratchpad for htop
	{ MODKEY|ShiftMask,             XK_w,      togglescratch,  {.ui = 4 } }, // scratchpad for nmtui
	{ MODKEY|ShiftMask,             XK_v,      togglescratch,  {.ui = 5 } }, // scratchpad for pulsemixer
	{ MODKEY|ShiftMask,             XK_p,      togglescratch,  {.ui = 6 } }, // scratchpad for calcurse
	{ MODKEY|ShiftMask,             XK_m,      togglescratch,  {.ui = 7 } }, // scratchpad for pulsemixer-mute
	{ MODKEY|ShiftMask,             XK_c,      spawn,          SHCMD(TERMINAL " --title float -e camtoggle &") },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("pcmanfm &") },
	{ MODKEY,                       XK_r,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	// { MODKEY,                       XK_F1,      spawn,         {.i = -1 } },
	// { MODKEY,                       XK_F2,      spawn,         {.i = -1 } },
	// { MODKEY,                       XK_F3,      spawn,         {.i = -1 } },
	// { MODKEY,                       XK_F4,      spawn,         {.i = -1 } },
	// { MODKEY,                       XK_F5,      spawn,         {.i = -1 } },
	{ MODKEY,                       XK_F6,     spawn,          SHCMD(TERMINAL " --title float -e qbittorrent") },
	// { MODKEY,                       XK_F7,      spawn,         {.i = -1 } },
	// { MODKEY,                       XK_F8,      spawn,         {.i = -1 } },
	// { MODKEY,                       XK_F9,      spawn,         {.i = -1 } },
	// { MODKEY,                       XK_F10      spawn,         {.i = -1 } },
	// { MODKEY,                       XK_F11      spawn,         {.i = -1 } },
	// { MODKEY,                       XK_F12      spawn,         {.i = -1 } },
	// { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	// { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ NULL,                         XK_F9,     view,           {.ui = 1 << 8} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +5 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -5 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +5 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -5 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +5 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -5 } },
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
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
	{ MODKEY,                       XK_p,      togglescratch,  {.ui = 0 } }, // scratchpad for vimwiki
	{ MODKEY,                       XK_x,      togglescratch,  {.ui = 1 } }, // scratchpad for keepassxc
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
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

