/* See LICENSE file for copyright and license details. */

#define SESSION_FILE "/tmp/dwm-session"

/* alt-tab configuration */
static const unsigned int tabMod1Key 		= 71;	/* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `*/
static const unsigned int tabMod2Key 		= 72;	/* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `*/
static const unsigned int tabCycleKey 		= 39;	/* if this key is hit the alt-tab program moves one position forward in clients stack. This key must be the same as key that is used to active functin altTabStart */
static const unsigned int tabPosY 			= 1;	/* tab position on Y axis, 0 = bottom, 1 = center, 2 = top */
static const unsigned int tabPosX 			= 1;	/* tab position on X axis, 0 = left, 1 = center, 2 = right */
static const unsigned int maxWTab 			= 600;	/* tab menu width */
static const unsigned int maxHTab 			= 200;	/* tab menu height */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;       /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int rmaster            = 1;        /* 1 means master-area is initially on the right */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=7" };
static const char dmenufont[]       = "monospace:size=7";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  "#aa0000"  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor      notallowed*/
	{ "Gimp",     NULL,       NULL,       0,            1,           -1,          0 },
   { "st-256color","st-256color","emerge",0,            0,           -1,          1 },
//	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1,          0 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "tatami.c"
#include "fibonacci.c"
#include "movestack.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "|+|",      tatami },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
	{ "[D]",      deck },
	{ "DD",       doubledeck },
   { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define MODKEY2 ControlMask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *browsercmd[]  = { "falkon", NULL };
static const char *audiolower[]  = { "amixer", "set", "Master", "5%-" };
static const char *audiohigher[]  = { "amixer", "set", "Master", "5%+" };

static Keychord *keychords[] = {
/*
 * Alt+u - focus by num
 * Alt+e - view tag
 * Alt+o - spawn
 * Alt+a - switch layout
 * Alt+i - layout control
 * Alt+p - focus by num
 * Alt+. - view tag
 * Alt+, - tag
 * Alt+;
 * Alt+y
 * Alt+k
 * Alt+j
 * Alt+q
 * Alt+'
 * Alt+x
 */
   // focus by num
   &((Keychord){2, {{MODKEY,           XK_u},                  { 0,           XK_h}},        focusbynum,       {.i = 0} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { 0,           XK_t}},        focusbynum,       {.i = 1} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { 0,           XK_n}},        focusbynum,       {.i = 2} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { 0,           XK_s}},        focusbynum,       {.i = 3} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { 0,           XK_g}},        focusbynum,       {.i = 4} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { 0,           XK_c}},        focusbynum,       {.i = 5} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { 0,           XK_r}},        focusbynum,       {.i = 6} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { 0,           XK_l}},        focusbynum,       {.i = 7} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { 0,           XK_m}},        focusbynum,       {.i = 8} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { 0,           XK_w}},        focusbynum,       {.i = 9} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { 0,           XK_v}},        focusbynum,       {.i = 10} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { 0,           XK_z}},        focusbynum,       {.i = 11} }),

   // view
   &((Keychord){2, {{ MODKEY,          XK_e},                  { 0,           XK_h}},        view,             {.ui = 1 << 0 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { 0,           XK_t}},        view,             {.ui = 1 << 1 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { 0,           XK_n}},        view,             {.ui = 1 << 2 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { 0,           XK_s}},        view,             {.ui = 1 << 3 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { 0,           XK_g}},        view,             {.ui = 1 << 4 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { 0,           XK_c}},        view,             {.ui = 1 << 5 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { 0,           XK_r}},        view,             {.ui = 1 << 6 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { 0,           XK_l}},        view,             {.ui = 1 << 7 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { 0,           XK_f}},        view,             {.ui = 1 << 8 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { 0,           XK_d}},        view,             {.ui = 1 << 9 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { 0,           XK_z}},        view,             {0} }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { 0,           XK_v}},        view,             {.ui = ~0 } }),

	// toggle view
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { 0,           XK_h}},        toggleview,       {.ui = 1 << 0 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { 0,           XK_t}},        toggleview,       {.ui = 1 << 1 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { 0,           XK_n}},        toggleview,       {.ui = 1 << 2 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { 0,           XK_s}},        toggleview,       {.ui = 1 << 3 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { 0,           XK_g}},        toggleview,       {.ui = 1 << 4 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { 0,           XK_c}},        toggleview,       {.ui = 1 << 5 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { 0,           XK_r}},        toggleview,       {.ui = 1 << 6 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { 0,           XK_l}},        toggleview,       {.ui = 1 << 7 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { 0,           XK_f}},        toggleview,       {.ui = 1 << 8 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { 0,           XK_d}},        toggleview,       {.ui = 1 << 9 } }),

   // spawn
   &((Keychord){2, {{ MODKEY,          XK_o},                  { 0,           XK_s}},        spawn,            {.v = dmenucmd } }),
   &((Keychord){2, {{ MODKEY,          XK_o},                  { 0,           XK_h}},        spawn,            {.v = termcmd } }),
   &((Keychord){2, {{ MODKEY,          XK_o},                  { 0,           XK_t}},        spawn,            {.v = browsercmd } }),
   
   // setlayout
   &((Keychord){2, {{MODKEY,           XK_a},                  { 0,           XK_h}},        setlayout,        {.v = &layouts[0]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { 0,           XK_t}},        setlayout,        {.v = &layouts[1]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { 0,           XK_n}},        setlayout,        {.v = &layouts[2]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { 0,           XK_s}},        setlayout,        {.v = &layouts[3]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { 0,           XK_g}},        setlayout,        {.v = &layouts[4]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { 0,           XK_c}},        setlayout,        {.v = &layouts[5]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { 0,           XK_r}},        setlayout,        {.v = &layouts[6]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { 0,           XK_l}},        setlayout,        {.v = &layouts[7]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { 0,           XK_d}},        setlayout,        {.v = &layouts[8]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { 0,           XK_f}},        setlayout,        {.v = &layouts[9]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { 0,           XK_slash}},    setlayout,        {0} }),

   // layout control
   &((Keychord){2, {{ MODKEY,          XK_i},                  { 0,           XK_h}},        incnmaster,       {.i = -1 } }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { 0,           XK_t}},        incnmaster,       {.i = +1 } }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { 0,           XK_n}},        setmfact,         {.f = -0.05} }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { 0,           XK_s}},        setmfact,         {.f = +0.05} }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { 0,           XK_g}},        togglermaster,    {0} }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { 0,           XK_c}},        togglefullscr,    {0} }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { 0,           XK_d}},        setcfact,         {.f = -0.25 } }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { 0,           XK_f}},        setcfact,         {.f = +0.25 } }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { 0,           XK_b}},        setcfact,         {.f =  0.00 } }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { 0,           XK_l}},        togglefloating,   {0} }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { 0,           XK_r}},        transfer,         {0} }),

   // tag
   &((Keychord){2, {{ MODKEY,          XK_comma},              { 0,           XK_h}},        tag,              {.ui = 1 << 0 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { 0,           XK_t}},        tag,              {.ui = 1 << 1 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { 0,           XK_n}},        tag,              {.ui = 1 << 2 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { 0,           XK_s}},        tag,              {.ui = 1 << 3 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { 0,           XK_g}},        tag,              {.ui = 1 << 4 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { 0,           XK_c}},        tag,              {.ui = 1 << 5 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { 0,           XK_r}},        tag,              {.ui = 1 << 6 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { 0,           XK_l}},        tag,              {.ui = 1 << 7 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { 0,           XK_f}},        tag,              {.ui = 1 << 8 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { 0,           XK_d}},        tag,              {.ui = 1 << 9 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { 0,           XK_z}},        tag,              {.ui = ~0 } }),

   // toggle tag
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { 0,           XK_h}},        toggletag,        {.ui = 1 << 0 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { 0,           XK_t}},        toggletag,        {.ui = 1 << 1 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { 0,           XK_n}},        toggletag,        {.ui = 1 << 2 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { 0,           XK_s}},        toggletag,        {.ui = 1 << 3 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { 0,           XK_g}},        toggletag,        {.ui = 1 << 4 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { 0,           XK_c}},        toggletag,        {.ui = 1 << 5 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { 0,           XK_r}},        toggletag,        {.ui = 1 << 6 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { 0,           XK_l}},        toggletag,        {.ui = 1 << 7 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { 0,           XK_f}},        toggletag,        {.ui = 1 << 8 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { 0,           XK_d}},        toggletag,        {.ui = 1 << 9 } }),

   // system
   &((Keychord){2, {{ MODKEY,          XK_semicolon},          { 0,           XK_h}},        togglebar,        {0} }),
   &((Keychord){2, {{ MODKEY,          XK_semicolon},          { 0,           XK_t}},        zoom,             {0} }),
   &((Keychord){2, {{ MODKEY,          XK_semicolon},          { 0,           XK_n}},        quit,             {1} }),
   &((Keychord){2, {{ MODKEY,          XK_semicolon},          { 0,           XK_s}},        quit,             {0} }),

   // quick access
   &((Keychord){1, {{ MODKEY,          XK_g}},                                               focusstack,       {.i = -1 } }),
   &((Keychord){1, {{ MODKEY,          XK_h}},                                               focusstack,       {.i = +1 } }),
   &((Keychord){1, {{ MODKEY,          XK_c}},                                               spawn,            {.v = audiohigher } }),
   &((Keychord){1, {{ MODKEY,          XK_t}},                                               spawn,            {.v = audiolower } }),
   &((Keychord){1, {{ MODKEY,          XK_r}},                                               cyclelayout,      {.i = +1} }),
   &((Keychord){1, {{ MODKEY,          XK_n}},                                               cyclelayout,      {.i = -1} }),
   &((Keychord){1, {{ MODKEY,          XK_m}},                                               setmfact,         {.f = -0.05} }),
   &((Keychord){1, {{ MODKEY,          XK_w}},                                               setmfact,         {.f = +0.05} }),
   &((Keychord){1, {{ MODKEY,          XK_v}},                                               setcfact,         {.f = -0.25 } }),
   &((Keychord){1, {{ MODKEY,          XK_z}},                                               setcfact,         {.f = +0.25 } }),
   &((Keychord){1, {{ MODKEY,          XK_s}},                                               altTabStart,      {0} }),
   &((Keychord){1, {{ MODKEY,          XK_slash}},                                           killclient,       {0} }),
   &((Keychord){1, {{ MODKEY,          XK_d}},                                               togglescratch,    {.v = scratchpadcmd } }),
   &((Keychord){1, {{ MODKEY,          XK_l}},                                               togglefullscr,    {0} }),
   &((Keychord){1, {{ MODKEY,          XK_apostrophe}},                                      inplacerotate,    {.i = +1} }),
   &((Keychord){1, {{ MODKEY,          XK_q}},                                               inplacerotate,    {.i = -1} }),
   &((Keychord){1, {{ MODKEY,          XK_j}},                                               inplacerotate,    {.i = +2} }),
   &((Keychord){1, {{ MODKEY,          XK_k}},                                               inplacerotate,    {.i = -2} }),
   &((Keychord){1, {{ MODKEY,          XK_period}},                                          movestack,        {.i = +1} }),
   &((Keychord){1, {{ MODKEY,          XK_p}},                                               movestack,        {.i = -1} }),
   &((Keychord){1, {{ MODKEY,          XK_minus}},                                           switchcol,        {0} }),

   // with second modkey
   // focus by num
   &((Keychord){2, {{MODKEY,           XK_u},                  { MODKEY,      XK_h}},        focusbynum,       {.i = 0} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { MODKEY,      XK_t}},        focusbynum,       {.i = 1} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { MODKEY,      XK_n}},        focusbynum,       {.i = 2} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { MODKEY,      XK_s}},        focusbynum,       {.i = 3} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { MODKEY,      XK_g}},        focusbynum,       {.i = 4} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { MODKEY,      XK_c}},        focusbynum,       {.i = 5} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { MODKEY,      XK_r}},        focusbynum,       {.i = 6} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { MODKEY,      XK_l}},        focusbynum,       {.i = 7} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { MODKEY,      XK_m}},        focusbynum,       {.i = 8} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { MODKEY,      XK_w}},        focusbynum,       {.i = 9} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { MODKEY,      XK_v}},        focusbynum,       {.i = 10} }),
   &((Keychord){2, {{MODKEY,           XK_u},                  { MODKEY,      XK_z}},        focusbynum,       {.i = 11} }),

   // view
   &((Keychord){2, {{ MODKEY,          XK_e},                  { MODKEY,      XK_h}},        view,             {.ui = 1 << 0 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { MODKEY,      XK_t}},        view,             {.ui = 1 << 1 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { MODKEY,      XK_n}},        view,             {.ui = 1 << 2 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { MODKEY,      XK_s}},        view,             {.ui = 1 << 3 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { MODKEY,      XK_g}},        view,             {.ui = 1 << 4 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { MODKEY,      XK_c}},        view,             {.ui = 1 << 5 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { MODKEY,      XK_r}},        view,             {.ui = 1 << 6 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { MODKEY,      XK_l}},        view,             {.ui = 1 << 7 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { MODKEY,      XK_f}},        view,             {.ui = 1 << 8 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { MODKEY,      XK_d}},        view,             {.ui = 1 << 9 } }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { MODKEY,      XK_z}},        view,             {0} }),
   &((Keychord){2, {{ MODKEY,          XK_e},                  { MODKEY,      XK_v}},        view,             {.ui = ~0 } }),

	// toggle view
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { MODKEY,      XK_h}},        toggleview,       {.ui = 1 << 0 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { MODKEY,      XK_t}},        toggleview,       {.ui = 1 << 1 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { MODKEY,      XK_n}},        toggleview,       {.ui = 1 << 2 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { MODKEY,      XK_s}},        toggleview,       {.ui = 1 << 3 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { MODKEY,      XK_g}},        toggleview,       {.ui = 1 << 4 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { MODKEY,      XK_c}},        toggleview,       {.ui = 1 << 5 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { MODKEY,      XK_r}},        toggleview,       {.ui = 1 << 6 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { MODKEY,      XK_l}},        toggleview,       {.ui = 1 << 7 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { MODKEY,      XK_f}},        toggleview,       {.ui = 1 << 8 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_e},                  { MODKEY,      XK_d}},        toggleview,       {.ui = 1 << 9 } }),

   // spawn
   &((Keychord){2, {{ MODKEY,          XK_o},                  { MODKEY,      XK_s}},        spawn,            {.v = dmenucmd } }),
   &((Keychord){2, {{ MODKEY,          XK_o},                  { MODKEY,      XK_h}},        spawn,            {.v = termcmd } }),
   &((Keychord){2, {{ MODKEY,          XK_o},                  { MODKEY,      XK_t}},        spawn,            {.v = browsercmd } }),
   
   // setlayout
   &((Keychord){2, {{MODKEY,           XK_a},                  { MODKEY,      XK_h}},        setlayout,        {.v = &layouts[0]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { MODKEY,      XK_t}},        setlayout,        {.v = &layouts[1]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { MODKEY,      XK_n}},        setlayout,        {.v = &layouts[2]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { MODKEY,      XK_s}},        setlayout,        {.v = &layouts[3]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { MODKEY,      XK_g}},        setlayout,        {.v = &layouts[4]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { MODKEY,      XK_c}},        setlayout,        {.v = &layouts[5]} }),
   &((Keychord){2, {{MODKEY,           XK_a},                  { MODKEY,      XK_slash}},    setlayout,        {0} }),

   // layout control
   &((Keychord){2, {{ MODKEY,          XK_i},                  { MODKEY,      XK_h}},        incnmaster,       {.i = -1 } }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { MODKEY,      XK_t}},        incnmaster,       {.i = +1 } }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { MODKEY,      XK_n}},        setmfact,         {.f = -0.05} }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { MODKEY,      XK_s}},        setmfact,         {.f = +0.05} }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { MODKEY,      XK_g}},        togglermaster,    {0} }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { MODKEY,      XK_c}},        togglefullscr,    {0} }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { MODKEY,      XK_d}},        setcfact,         {.f = -0.25 } }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { MODKEY,      XK_f}},        setcfact,         {.f = +0.25 } }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { MODKEY,      XK_b}},        setcfact,         {.f =  0.00 } }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { MODKEY,      XK_l}},        togglefloating,   {0} }),
   &((Keychord){2, {{ MODKEY,          XK_i},                  { MODKEY,      XK_r}},        transfer,         {0} }),

   // tag
   &((Keychord){2, {{ MODKEY,          XK_comma},              { MODKEY,      XK_h}},        tag,              {.ui = 1 << 0 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { MODKEY,      XK_t}},        tag,              {.ui = 1 << 1 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { MODKEY,      XK_n}},        tag,              {.ui = 1 << 2 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { MODKEY,      XK_s}},        tag,              {.ui = 1 << 3 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { MODKEY,      XK_g}},        tag,              {.ui = 1 << 4 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { MODKEY,      XK_c}},        tag,              {.ui = 1 << 5 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { MODKEY,      XK_r}},        tag,              {.ui = 1 << 6 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { MODKEY,      XK_l}},        tag,              {.ui = 1 << 7 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { MODKEY,      XK_f}},        tag,              {.ui = 1 << 8 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { MODKEY,      XK_d}},        tag,              {.ui = 1 << 9 } }),
   &((Keychord){2, {{ MODKEY,          XK_comma},              { MODKEY,      XK_z}},        tag,              {.ui = ~0 } }),

   // toggle tag
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { MODKEY,      XK_h}},        toggletag,        {.ui = 1 << 0 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { MODKEY,      XK_t}},        toggletag,        {.ui = 1 << 1 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { MODKEY,      XK_n}},        toggletag,        {.ui = 1 << 2 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { MODKEY,      XK_s}},        toggletag,        {.ui = 1 << 3 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { MODKEY,      XK_g}},        toggletag,        {.ui = 1 << 4 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { MODKEY,      XK_c}},        toggletag,        {.ui = 1 << 5 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { MODKEY,      XK_r}},        toggletag,        {.ui = 1 << 6 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { MODKEY,      XK_l}},        toggletag,        {.ui = 1 << 7 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { MODKEY,      XK_f}},        toggletag,        {.ui = 1 << 8 } }),
   &((Keychord){2, {{ MODKEY|MODKEY2,  XK_comma},              { MODKEY,      XK_d}},        toggletag,        {.ui = 1 << 9 } }),

   // system
   &((Keychord){2, {{ MODKEY,          XK_semicolon},          { MODKEY,      XK_h}},        togglebar,        {0} }),
   &((Keychord){2, {{ MODKEY,          XK_semicolon},          { MODKEY,      XK_t}},        zoom,             {0} }),
   &((Keychord){2, {{ MODKEY,          XK_semicolon},          { MODKEY,      XK_n}},        quit,             {1} }),
   &((Keychord){2, {{ MODKEY,          XK_semicolon},          { MODKEY,      XK_s}},        quit,             {0} }),

   // comboviews
   &((Keychord){1, {{ MODKEY|MODKEY2,  XK_h}},                                               comboview,        {.ui = 1 << 0 } }),
   &((Keychord){1, {{ MODKEY|MODKEY2,  XK_t}},                                               comboview,        {.ui = 1 << 1 } }),
   &((Keychord){1, {{ MODKEY|MODKEY2,  XK_n}},                                               comboview,        {.ui = 1 << 2 } }),
   &((Keychord){1, {{ MODKEY|MODKEY2,  XK_s}},                                               comboview,        {.ui = 1 << 3 } }),
   &((Keychord){1, {{ MODKEY|MODKEY2,  XK_g}},                                               comboview,        {.ui = 1 << 4 } }),
   &((Keychord){1, {{ MODKEY|MODKEY2,  XK_c}},                                               comboview,        {.ui = 1 << 5 } }),
   &((Keychord){1, {{ MODKEY|MODKEY2,  XK_r}},                                               comboview,        {.ui = 1 << 6 } }),
   &((Keychord){1, {{ MODKEY|MODKEY2,  XK_l}},                                               comboview,        {.ui = 1 << 7 } }),
   &((Keychord){1, {{ MODKEY|MODKEY2,  XK_m}},                                               comboview,        {.ui = 1 << 8 } }),
   &((Keychord){1, {{ MODKEY|MODKEY2,  XK_w}},                                               comboview,        {.ui = 1 << 9 } }),
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

