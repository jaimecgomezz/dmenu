/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"monospace:size=9"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#d2d4de", "#161821" },
	[SchemeSel] = { "#000000", "#a89984" },
	[SchemeOut] = { "#000000", "#95c4ce" },
  // >>>>>>>>>>>>>>>>>>>> fuzzyhighlight
  // ==================== fuzzyhighlight
  // <<<<<<<<<<<<<<<<<<<< fuzzyhighlight
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";

// >>>>>>>>>>>>>>>>>>>> border
// ==================== border
// <<<<<<<<<<<<<<<<<<<< border

// >>>>>>>>>>>>>>>>>>>> center
// ==================== center
// <<<<<<<<<<<<<<<<<<<< center

// >>>>>>>>>>>>>>>>>>>> dynamic-options
// ==================== dynamic-options
// <<<<<<<<<<<<<<<<<<<< dynamic-options

// >>>>>>>>>>>>>>>>>>>> fuzzymatch
// ==================== fuzzymatch
// <<<<<<<<<<<<<<<<<<<< fuzzymatch

// >>>>>>>>>>>>>>>>>>>> grid
// ==================== grid
// <<<<<<<<<<<<<<<<<<<< grid

// >>>>>>>>>>>>>>>>>>>> incremental
// ==================== incremental
// <<<<<<<<<<<<<<<<<<<< incremental

// >>>>>>>>>>>>>>>>>>>> preselect
// ==================== preselect
// <<<<<<<<<<<<<<<<<<<< preselect
