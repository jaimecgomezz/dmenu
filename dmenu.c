/* See LICENSE file for copyright and license details. */
#include <ctype.h>
#include <locale.h>
// >>>>>>>>>>>>>>>>>>>> fuzzymatch
// ==================== fuzzymatch
// <<<<<<<<<<<<<<<<<<<< fuzzymatch
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#ifdef XINERAMA
#include <X11/extensions/Xinerama.h>
#endif
#include <X11/Xft/Xft.h>
// >>>>>>>>>>>>>>>>>>>> json
// ==================== json
// <<<<<<<<<<<<<<<<<<<< json
// >>>>>>>>>>>>>>>>>>>> xresources
// ==================== xresources
// <<<<<<<<<<<<<<<<<<<< xresources

#include "drw.h"
#include "util.h"

/* macros */
#define INTERSECT(x,y,w,h,r)  (MAX(0, MIN((x)+(w),(r).x_org+(r).width)  - MAX((x),(r).x_org)) \
                             * MAX(0, MIN((y)+(h),(r).y_org+(r).height) - MAX((y),(r).y_org)))
#define LENGTH(X)             (sizeof X / sizeof X[0])
#define TEXTW(X)              (drw_fontset_getwidth(drw, (X)) + lrpad)
// >>>>>>>>>>>>>>>>>>>> numbers
// ==================== numbers
// <<<<<<<<<<<<<<<<<<<< numbers

/* enums */
enum {
  // >>>>>>>>>>>>>>>>>>>> fuzzyhighlight
  // ==================== fuzzyhighlight
  // <<<<<<<<<<<<<<<<<<<< fuzzyhighlight
  // >>>>>>>>>>>>>>>>>>>> more-color
  // ==================== more-color
  // <<<<<<<<<<<<<<<<<<<< more-color
  // >>>>>>>>>>>>>>>>>>>> high-priority
  // ==================== high-priority
  // <<<<<<<<<<<<<<<<<<<< high-priority
  // >>>>>>>>>>>>>>>>>>>> highlight
  // ==================== highlight
  // <<<<<<<<<<<<<<<<<<<< highlight
  SchemeNorm,
  SchemeSel,
  SchemeOut,
  SchemeLast
}; /* color schemes */

struct item {
	char *text;
	struct item *left, *right;
  int out;
  // >>>>>>>>>>>>>>>>>>>> multi-selection
  // ==================== multi-selection
  // <<<<<<<<<<<<<<<<<<<< multi-selection
  // >>>>>>>>>>>>>>>>>>>> fuzzymatch
  // ==================== fuzzymatch
  // <<<<<<<<<<<<<<<<<<<< fuzzymatch
  // >>>>>>>>>>>>>>>>>>>> json
  // ==================== json
  // <<<<<<<<<<<<<<<<<<<< json
  // >>>>>>>>>>>>>>>>>>>> high-priority
  // ==================== high-priority
  // <<<<<<<<<<<<<<<<<<<< high-priority
};

static char text[BUFSIZ] = "";
static char *embed;
static int bh, mw, mh;
// >>>>>>>>>>>>>>>>>>>> password
// ==================== password
static int inputw = 0, promptw;
// <<<<<<<<<<<<<<<<<<<< password
static int lrpad; /* sum of left and right padding */
static size_t cursor;
static struct item *items = NULL;
static struct item *matches, *matchend;
static struct item *prev, *curr, *next, *sel;
static int mon = -1, screen;
// >>>>>>>>>>>>>>>>>>>> xyw
// ==================== xyw
// <<<<<<<<<<<<<<<<<<<< xyw
// >>>>>>>>>>>>>>>>>>>> numbers
// ==================== numbers
// <<<<<<<<<<<<<<<<<<<< numbers
// >>>>>>>>>>>>>>>>>>>> pipeout
// ==================== pipeout
// <<<<<<<<<<<<<<<<<<<< pipeout
// >>>>>>>>>>>>>>>>>>>> json
// ==================== json
// <<<<<<<<<<<<<<<<<<<< json
// >>>>>>>>>>>>>>>>>>>> multi-selection
// ==================== multi-selection
// <<<<<<<<<<<<<<<<<<<< multi-selection
// >>>>>>>>>>>>>>>>>>>> managed
// ==================== managed
// <<<<<<<<<<<<<<<<<<<< managed
// >>>>>>>>>>>>>>>>>>>> reject-no-match
// ==================== reject-no-match
// <<<<<<<<<<<<<<<<<<<< reject-no-match
// >>>>>>>>>>>>>>>>>>>> navhistory
// ==================== navhistory
// <<<<<<<<<<<<<<<<<<<< navhistory
// >>>>>>>>>>>>>>>>>>>> print-input-text
// ==================== print-input-text
// <<<<<<<<<<<<<<<<<<<< print-input-text
// >>>>>>>>>>>>>>>>>>>> xresources
// ==================== xresources
// <<<<<<<<<<<<<<<<<<<< xresources
// >>>>>>>>>>>>>>>>>>>> high-priority
// ==================== high-priority
// <<<<<<<<<<<<<<<<<<<< high-priority

static Atom clip, utf8;
static Display *dpy;
static Window root, parentwin, win;
static XIC xic;

static Drw *drw;
static Clr *scheme[SchemeLast];

#include "config.def.h"

// >>>>>>>>>>>>>>>>>>>> case-insensitive
// ==================== case-insensitive
static int (*fstrncmp)(const char *, const char *, size_t) = strncmp;
static char *(*fstrstr)(const char *, const char *) = strstr;
// <<<<<<<<<<<<<<<<<<<< case-insensitive

// >>>>>>>>>>>>>>>>>>>> json
// ==================== json
// <<<<<<<<<<<<<<<<<<<< json

// >>>>>>>>>>>>>>>>>>>> multi-selection
// ==================== multi-selection
// <<<<<<<<<<<<<<<<<<<< multi-selection

// >>>>>>>>>>>>>>>>>>>> high-priority
// ==================== high-priority
// <<<<<<<<<<<<<<<<<<<< high-priority

static void
appenditem(struct item *item, struct item **list, struct item **last)
{
	if (*last)
		(*last)->right = item;
	else
		*list = item;

	item->left = *last;
	item->right = NULL;
	*last = item;
}

static void
calcoffsets(void)
{
	int i, n;

	if (lines > 0)
    // >>>>>>>>>>>>>>>>>>>> grid
    // ==================== grid
    n = lines * bh;
    // <<<<<<<<<<<<<<<<<<<< grid
	else
    // >>>>>>>>>>>>>>>>>>>> symbols
    // ==================== symbols
		n = mw - (promptw + inputw + TEXTW("<") + TEXTW(">"));
    // <<<<<<<<<<<<<<<<<<<< symbols
	/* calculate which items will begin the next page and previous page */
	for (i = 0, next = curr; next; next = next->right)
		if ((i += (lines > 0) ? bh : MIN(TEXTW(next->text), n)) > n)
			break;
	for (i = 0, prev = curr; prev && prev->left; prev = prev->left)
		if ((i += (lines > 0) ? bh : MIN(TEXTW(prev->left->text), n)) > n)
			break;
}

// >>>>>>>>>>>>>>>>>>>> center
// ==================== center
// <<<<<<<<<<<<<<<<<<<< center

static void
cleanup(void)
{
	size_t i;

	XUngrabKey(dpy, AnyKey, AnyModifier, root);
	for (i = 0; i < SchemeLast; i++)
		free(scheme[i]);
	drw_free(drw);
	XSync(dpy, False);
	XCloseDisplay(dpy);
  // >>>>>>>>>>>>>>>>>>>> multi-selection
  // ==================== multi-selection
  // <<<<<<<<<<<<<<<<<<<< multi-selection
}

static char *
cistrstr(const char *s, const char *sub)
{
	size_t len;

	for (len = strlen(sub); *s; s++)
		if (!strncasecmp(s, sub, len))
			return (char *)s;
	return NULL;
}

// >>>>>>>>>>>>>>>>>>>> fuzzyhighlight
// ==================== fuzzyhighlight
// <<<<<<<<<<<<<<<<<<<< fuzzyhighlight

// >>>>>>>>>>>>>>>>>>>> highlight
// ==================== highlight
// <<<<<<<<<<<<<<<<<<<< highlight

static int
drawitem(struct item *item, int x, int y, int w)
{
  // >>>>>>>>>>>>>>>>>>>> fuzzyhighlight
  // ==================== fuzzyhighlight
  // <<<<<<<<<<<<<<<<<<<< fuzzyhighlight
	if (item == sel)
		drw_setscheme(drw, scheme[SchemeSel]);
  // >>>>>>>>>>>>>>>>>>>> multi-selection
  // ==================== multi-selection
  else if (item->out)
  // <<<<<<<<<<<<<<<<<<<< multi-selection
		drw_setscheme(drw, scheme[SchemeOut]);
  // >>>>>>>>>>>>>>>>>>>> more-color
  // ==================== more-color
  // <<<<<<<<<<<<<<<<<<<< more-color
  // >>>>>>>>>>>>>>>>>>>> high-priority
  // ==================== high-priority
  // <<<<<<<<<<<<<<<<<<<< high-priority
	else
		drw_setscheme(drw, scheme[SchemeNorm]);

  // >>>>>>>>>>>>>>>>>>>> fuzzyhighlight-highlight
  // ==================== fuzzyhighlight-highlight
	return drw_text(drw, x, y, w, bh, lrpad / 2, item->text, 0);
  // <<<<<<<<<<<<<<<<<<<< fuzzyhighlight-highlight
}

// >>>>>>>>>>>>>>>>>>>> numbers
// ==================== numbers
// <<<<<<<<<<<<<<<<<<<< numbers

static void
drawmenu(void)
{
  // >>>>>>>>>>>>>>>>>>>> scroll
  // ==================== scroll
  unsigned int curpos;
  // <<<<<<<<<<<<<<<<<<<< scroll
	struct item *item;
	int x = 0, y = 0, w;
  // >>>>>>>>>>>>>>>>>>>> password
  // ==================== password
  // <<<<<<<<<<<<<<<<<<<< password
  // >>>>>>>>>>>>>>>>>>>> line-height
  // ==================== line-height
  // <<<<<<<<<<<<<<<<<<<< line-height

	drw_setscheme(drw, scheme[SchemeNorm]);
	drw_rect(drw, 0, 0, mw, mh, 1, 1);

	if (prompt && *prompt) {
		drw_setscheme(drw, scheme[SchemeSel]);
		x = drw_text(drw, x, 0, promptw, bh, lrpad / 2, prompt, 0);
	}
	/* draw input field */
	w = (lines > 0 || !matches) ? mw - x : inputw;
  // >>>>>>>>>>>>>>>>>>>> scroll
  // ==================== scroll
  drw_setscheme(drw, scheme[SchemeNorm]);
  // <<<<<<<<<<<<<<<<<<<< scroll
  // >>>>>>>>>>>>>>>>>>>> password-scroll
  // ==================== password-scroll
  drw_text(drw, x, 0, w, bh, lrpad / 2, text, 0);
  // <<<<<<<<<<<<<<<<<<<< password-scroll

  // >>>>>>>>>>>>>>>>>>>> scroll-line-height
  // ==================== scroll-line-height
	curpos = TEXTW(text) - TEXTW(&text[cursor]);
	if ((curpos += lrpad / 2 - 1) < w) {
		drw_setscheme(drw, scheme[SchemeNorm]);
		drw_rect(drw, x + curpos, 2, 2, bh - 4, 1, 0);
	}
  // <<<<<<<<<<<<<<<<<<<< scroll-line-height

  // >>>>>>>>>>>>>>>>>>>> numbers
  // ==================== numbers
  // <<<<<<<<<<<<<<<<<<<< numbers
	if (lines > 0) {
    // >>>>>>>>>>>>>>>>>>>> grid-vertfull
    // ==================== grid-vertfull
		/* draw vertical list */
		for (item = curr; item != next; item = item->right)
			drawitem(item, x, y += bh, mw - x);
    // <<<<<<<<<<<<<<<<<<<< grid-vertfull
	} else if (matches) {
		/* draw horizontal list */
		x += inputw;
    // >>>>>>>>>>>>>>>>>>>> symbols
    // ==================== symbols
		w = TEXTW("<");
    // <<<<<<<<<<<<<<<<<<<< symbols
		if (curr->left) {
			drw_setscheme(drw, scheme[SchemeNorm]);
      // >>>>>>>>>>>>>>>>>>>> symbols
      // ==================== symbols
      w = TEXTW("<");
      drw_text(drw, x, 0, w, bh, lrpad / 2, "<", 0);
      // <<<<<<<<<<<<<<<<<<<< symbols
		}
		x += w;
		for (item = curr; item != next; item = item->right)
      // >>>>>>>>>>>>>>>>>>>> numbers-symbols
      // ==================== numbers-symbols
      x = drawitem(item, x, 0, MIN(TEXTW(item->text), mw - x - TEXTW(">")));
      // <<<<<<<<<<<<<<<<<<<< numbers-symbols
		if (next) {
      // >>>>>>>>>>>>>>>>>>>> symbols
      // ==================== symbols
			w = TEXTW(">");
      // <<<<<<<<<<<<<<<<<<<< symbols
			drw_setscheme(drw, scheme[SchemeNorm]);
      // >>>>>>>>>>>>>>>>>>>> numbers-symbols
      // ==================== numbers-symbols
      drw_text(drw, mw - w, 0, w, bh, lrpad / 2, ">", 0);
      // <<<<<<<<<<<<<<<<<<<< numbers-symbols
		}
	}
  // >>>>>>>>>>>>>>>>>>>> numbers
  // ==================== numbers
  // <<<<<<<<<<<<<<<<<<<< numbers
	drw_map(drw, win, 0, 0, mw, mh);
}

static void
grabfocus(void)
{
	struct timespec ts = { .tv_sec = 0, .tv_nsec = 10000000  };
	Window focuswin;
	int i, revertwin;

	for (i = 0; i < 100; ++i) {
		XGetInputFocus(dpy, &focuswin, &revertwin);
		if (focuswin == win)
			return;
		XSetInputFocus(dpy, win, RevertToParent, CurrentTime);
		nanosleep(&ts, NULL);
	}
	die("cannot grab focus");
}

static void
grabkeyboard(void)
{
	struct timespec ts = { .tv_sec = 0, .tv_nsec = 1000000  };
	int i;

  // >>>>>>>>>>>>>>>>>>>> managed
  // ==================== managed
	if (embed)
  // <<<<<<<<<<<<<<<<<<<< managed
		return;
	/* try to grab keyboard, we may have to wait for another process to ungrab */
	for (i = 0; i < 1000; i++) {
		if (XGrabKeyboard(dpy, DefaultRootWindow(dpy), True, GrabModeAsync,
		                  GrabModeAsync, CurrentTime) == GrabSuccess)
			return;
		nanosleep(&ts, NULL);
	}
	die("cannot grab keyboard");
}

// >>>>>>>>>>>>>>>>>>>> fuzzymatch
// ==================== fuzzymatch
// <<<<<<<<<<<<<<<<<<<< fuzzymatch

// >>>>>>>>>>>>>>>>>>>> dynamic-options
// ==================== dynamic-options
// <<<<<<<<<<<<<<<<<<<< dynamic-options

static void
match(void)
{
  // >>>>>>>>>>>>>>>>>>>> dynamic-options
  // ==================== dynamic-options
  // <<<<<<<<<<<<<<<<<<<< dynamic-options

  // >>>>>>>>>>>>>>>>>>>> fuzzymatch
  // ==================== fuzzymatch
  // <<<<<<<<<<<<<<<<<<<< fuzzymatch

	static char **tokv = NULL;
	static int tokn = 0;

	char buf[sizeof text], *s;
	int i, tokc = 0;
	size_t len, textsize;
	struct item *item, *lprefix, *lsubstr, *prefixend, *substrend;
  // >>>>>>>>>>>>>>>>>>>> high-priority
  // ==================== high-priority
  // <<<<<<<<<<<<<<<<<<<< high-priority

  // >>>>>>>>>>>>>>>>>>>> json
  // ==================== json
  // <<<<<<<<<<<<<<<<<<<< json

	strcpy(buf, text);
	/* separate input text into tokens to be matched individually */
	for (s = strtok(buf, " "); s; tokv[tokc - 1] = s, s = strtok(NULL, " "))
		if (++tokc > tokn && !(tokv = realloc(tokv, ++tokn * sizeof *tokv)))
			die("cannot realloc %u bytes:", tokn * sizeof *tokv);
	len = tokc ? strlen(tokv[0]) : 0;

  // >>>>>>>>>>>>>>>>>>>> prefix-completition-high-priority
  // ==================== prefix-completition-high-priority
	matches = lprefix = lsubstr = matchend = prefixend = substrend = NULL;
	textsize = strlen(text) + 1;
  // <<<<<<<<<<<<<<<<<<<< prefix-completition-high-priority
	for (item = items; item && item->text; item++) {
		for (i = 0; i < tokc; i++)
			if (!fstrstr(item->text, tokv[i]))
				break;
    // >>>>>>>>>>>>>>>>>>>> dynamic-options
    // ==================== dynamic-options
		if (i != tokc) /* not all tokens match */
    // <<<<<<<<<<<<<<<<<<<< dynamic-options
			continue;
    // >>>>>>>>>>>>>>>>>>>> high-priority
    // ==================== high-priority
    /* exact matches go first, then prefixes, then substrings */
    // <<<<<<<<<<<<<<<<<<<< high-priority
		if (!tokc || !fstrncmp(text, item->text, textsize))
			appenditem(item, &matches, &matchend);
    // >>>>>>>>>>>>>>>>>>>> high-priority
    // ==================== high-priority
    // <<<<<<<<<<<<<<<<<<<< high-priority
		else if (!fstrncmp(tokv[0], item->text, len))
			appenditem(item, &lprefix, &prefixend);
    // >>>>>>>>>>>>>>>>>>>> prefix-completition
    // ==================== prefix-completition
    else
    // <<<<<<<<<<<<<<<<<<<< prefix-completition
			appenditem(item, &lsubstr, &substrend);
	}

  // >>>>>>>>>>>>>>>>>>>> high-priority
  // ==================== high-priority
  // <<<<<<<<<<<<<<<<<<<< high-priority

	if (lprefix) {
		if (matches) {
			matchend->right = lprefix;
			lprefix->left = matchend;
		} else
			matches = lprefix;
		matchend = prefixend;
	}
  // >>>>>>>>>>>>>>>>>>>> prefix-completition
  // ==================== prefix-completition
  if (lsubstr) {
  // <<<<<<<<<<<<<<<<<<<< prefix-completition
		if (matches) {
			matchend->right = lsubstr;
			lsubstr->left = matchend;
		} else
			matches = lsubstr;
		matchend = substrend;
	}
	curr = sel = matches;

  // >>>>>>>>>>>>>>>>>>>> instant
  // ==================== instant
  // <<<<<<<<<<<<<<<<<<<< instant

	calcoffsets();
}

static void
insert(const char *str, ssize_t n)
{
	if (strlen(text) + n > sizeof text - 1)
		return;

  // >>>>>>>>>>>>>>>>>>>> reject-no-match
  // ==================== reject-no-match
  // <<<<<<<<<<<<<<<<<<<< reject-no-match

	/* move existing text out of the way, insert new text, and update cursor */
	memmove(&text[cursor + n], &text[cursor], sizeof text - cursor - MAX(n, 0));
	if (n > 0)
		memcpy(&text[cursor], str, n);
	cursor += n;
	match();

  // >>>>>>>>>>>>>>>>>>>> reject-no-match
  // ==================== reject-no-match
  // <<<<<<<<<<<<<<<<<<<< reject-no-match
}

static size_t
nextrune(int inc)
{
	ssize_t n;

	/* return location of next utf8 rune in the given direction (+1 or -1) */
	for (n = cursor + inc; n + inc >= 0 && (text[n] & 0xc0) == 0x80; n += inc)
		;
	return n;
}

static void
movewordedge(int dir)
{
	if (dir < 0) { /* move cursor to the start of the word*/
		while (cursor > 0 && strchr(worddelimiters, text[nextrune(-1)]))
			cursor = nextrune(-1);
		while (cursor > 0 && !strchr(worddelimiters, text[nextrune(-1)]))
			cursor = nextrune(-1);
	} else { /* move cursor to the end of the word */
		while (text[cursor] && strchr(worddelimiters, text[cursor]))
			cursor = nextrune(+1);
		while (text[cursor] && !strchr(worddelimiters, text[cursor]))
			cursor = nextrune(+1);
	}
}

// >>>>>>>>>>>>>>>>>>>> navhistory
// ==================== navhistory
// <<<<<<<<<<<<<<<<<<<< navhistory

static void
keypress(XKeyEvent *ev)
{
	char buf[32];
	int len;
	KeySym ksym;
	Status status;
  // >>>>>>>>>>>>>>>>>>>> prefix-completition
  // ==================== prefix-completition
  // <<<<<<<<<<<<<<<<<<<< prefix-completition
  // >>>>>>>>>>>>>>>>>>>> navhistory
  // ==================== navhistory
  // <<<<<<<<<<<<<<<<<<<< navhistory

	len = XmbLookupString(xic, ev, buf, sizeof buf, &ksym, &status);
	switch (status) {
	default: /* XLookupNone, XBufferOverflow */
		return;
	case XLookupChars:
		goto insert;
	case XLookupKeySym:
	case XLookupBoth:
		break;
	}

	if (ev->state & ControlMask) {
		switch(ksym) {
		case XK_a: ksym = XK_Home;      break;
		case XK_b: ksym = XK_Left;      break;
		case XK_c: ksym = XK_Escape;    break;
		case XK_d: ksym = XK_Delete;    break;
		case XK_e: ksym = XK_End;       break;
		case XK_f: ksym = XK_Right;     break;
		case XK_g: ksym = XK_Escape;    break;
		case XK_h: ksym = XK_BackSpace; break;
		case XK_i: ksym = XK_Tab;       break;
		case XK_j: /* fallthrough */
		case XK_J: /* fallthrough */
		case XK_m: /* fallthrough */
		case XK_M: ksym = XK_Return; ev->state &= ~ControlMask; break;
		case XK_n: ksym = XK_Down;      break;
		case XK_p: ksym = XK_Up;        break;

		case XK_k: /* delete right */
			text[cursor] = '\0';
			match();
			break;
		case XK_u: /* delete left */
			insert(NULL, 0 - cursor);
			break;
		case XK_w: /* delete word */
			while (cursor > 0 && strchr(worddelimiters, text[nextrune(-1)]))
				insert(NULL, nextrune(-1) - cursor);
			while (cursor > 0 && !strchr(worddelimiters, text[nextrune(-1)]))
				insert(NULL, nextrune(-1) - cursor);
			break;
		case XK_y: /* paste selection */
		case XK_Y:
			XConvertSelection(dpy, (ev->state & ShiftMask) ? clip : XA_PRIMARY,
			                  utf8, utf8, win, CurrentTime);
			return;
    // >>>>>>>>>>>>>>>>>>>> navhistory
    // ==================== navhistory
    // <<<<<<<<<<<<<<<<<<<< navhistory
		case XK_Left:
			movewordedge(-1);
			goto draw;
		case XK_Right:
			movewordedge(+1);
			goto draw;
		case XK_Return:
		case XK_KP_Enter:
      // >>>>>>>>>>>>>>>>>>>> multi-selection
      // ==================== multi-selection
      // <<<<<<<<<<<<<<<<<<<< multi-selection
			break;
		case XK_bracketleft:
			cleanup();
			exit(1);
		default:
			return;
		}
	} else if (ev->state & Mod1Mask) {
		switch(ksym) {
		case XK_b:
			movewordedge(-1);
			goto draw;
		case XK_f:
			movewordedge(+1);
			goto draw;
		case XK_g: ksym = XK_Home;  break;
		case XK_G: ksym = XK_End;   break;
		case XK_h: ksym = XK_Up;    break;
		case XK_j: ksym = XK_Next;  break;
		case XK_k: ksym = XK_Prior; break;
		case XK_l: ksym = XK_Down;  break;
    // >>>>>>>>>>>>>>>>>>>> navhistory
    // ==================== navhistory
    // <<<<<<<<<<<<<<<<<<<< navhistory
		default:
			return;
		}
	}

	switch(ksym) {
	default:
insert:
		if (!iscntrl(*buf))
			insert(buf, len);
		break;
	case XK_Delete:
		if (text[cursor] == '\0')
			return;
		cursor = nextrune(+1);
		/* fallthrough */
	case XK_BackSpace:
		if (cursor == 0)
			return;
		insert(NULL, nextrune(-1) - cursor);
		break;
	case XK_End:
		if (text[cursor] != '\0') {
			cursor = strlen(text);
			break;
		}
		if (next) {
			/* jump to end of list and position items in reverse */
			curr = matchend;
			calcoffsets();
			curr = prev;
			calcoffsets();
			while (next && (curr = curr->right))
				calcoffsets();
		}
		sel = matchend;
		break;
	case XK_Escape:
		cleanup();
		exit(1);
	case XK_Home:
		if (sel == matches) {
			cursor = 0;
			break;
		}
		sel = curr = matches;
		calcoffsets();
		break;
	case XK_Left:
		if (cursor > 0 && (!sel || !sel->left || lines > 0)) {
			cursor = nextrune(-1);
			break;
		}
		if (lines > 0)
			return;
		/* fallthrough */
	case XK_Up:
		if (sel && sel->left && (sel = sel->left)->right == curr) {
			curr = prev;
			calcoffsets();
		}
		break;
	case XK_Next:
		if (!next)
			return;
		sel = curr = next;
		calcoffsets();
		break;
	case XK_Prior:
		if (!prev)
			return;
		sel = curr = prev;
		calcoffsets();
		break;
	case XK_Return:
	case XK_KP_Enter:
    // >>>>>>>>>>>>>>>>>>>> pipeout-json-multi-selection-print-input-text
    // ==================== pipeout-json-multi-selection-print-input-text
    puts((sel && !(ev->state & ShiftMask)) ? sel->text : text);
    // <<<<<<<<<<<<<<<<<<<< pipeout-json-multi-selection-print-input-text
		if (!(ev->state & ControlMask)) {
      // >>>>>>>>>>>>>>>>>>>> multi-selection
      // ==================== multi-selection
      // <<<<<<<<<<<<<<<<<<<< multi-selection
      // >>>>>>>>>>>>>>>>>>>> navhistory
      // ==================== navhistory
      // <<<<<<<<<<<<<<<<<<<< navhistory
			cleanup();
			exit(0);
		}
    // >>>>>>>>>>>>>>>>>>>> multi-selection
    // ==================== multi-selection
		if (sel)
			sel->out = 1;
    // <<<<<<<<<<<<<<<<<<<< multi-selection
		break;
	case XK_Right:
		if (text[cursor] != '\0') {
			cursor = nextrune(+1);
			break;
		}
		if (lines > 0)
			return;
		/* fallthrough */
	case XK_Down:
		if (sel && sel->right && (sel = sel->right) == next) {
			curr = next;
			calcoffsets();
		}
		break;
	case XK_Tab:
    // >>>>>>>>>>>>>>>>>>>> prefix-completition
    // ==================== prefix-completition
		if (!sel)
			return;
		strncpy(text, sel->text, sizeof text - 1);
    // <<<<<<<<<<<<<<<<<<<< prefix-completition
		text[sizeof text - 1] = '\0';
    // >>>>>>>>>>>>>>>>>>>> prefix-completition
    // ==================== prefix-completition
		cursor = strlen(text);
		match();
    // <<<<<<<<<<<<<<<<<<<< prefix-completition
		break;
	}

  // >>>>>>>>>>>>>>>>>>>> incremental
  // ==================== incremental
  // <<<<<<<<<<<<<<<<<<<< incremental

draw:
	drawmenu();
}

// >>>>>>>>>>>>>>>>>>>> mouse-support
// ==================== mouse-support
// <<<<<<<<<<<<<<<<<<<< mouse-support

static void
paste(void)
{
	char *p, *q;
	int di;
	unsigned long dl;
	Atom da;

	/* we have been given the current selection, now insert it into input */
	if (XGetWindowProperty(dpy, win, utf8, 0, (sizeof text / 4) + 1, False,
	                   utf8, &da, &di, &dl, &dl, (unsigned char **)&p)
	    == Success && p) {
		insert(p, (q = strchr(p, '\n')) ? q - p : (ssize_t)strlen(p));
		XFree(p);
	}
	drawmenu();
}

// >>>>>>>>>>>>>>>>>>>> json
// ==================== json
// <<<<<<<<<<<<<<<<<<<< json

static void
// >>>>>>>>>>>>>>>>>>>> dynamic-options
// ==================== dynamic-options
readstdin(void)
// <<<<<<<<<<<<<<<<<<<< dynamic-options
{
	char buf[sizeof text], *p;
  // >>>>>>>>>>>>>>>>>>>> json
  // ==================== json
  size_t i, imax = 0, size = 0;
  // <<<<<<<<<<<<<<<<<<<< json
	unsigned int tmpmax = 0;

  // >>>>>>>>>>>>>>>>>>>> password
  // ==================== password
  // <<<<<<<<<<<<<<<<<<<< password

	/* read each line from stdin and add it to the item list */
  // >>>>>>>>>>>>>>>>>>>> dynamic-options
  // ==================== dynamic-options
	for (i = 0; fgets(buf, sizeof buf, stdin); i++) {
  // <<<<<<<<<<<<<<<<<<<< dynamic-options
    // >>>>>>>>>>>>>>>>>>>> json
    // ==================== json
		if (i + 1 >= size / sizeof *items)
			if (!(items = realloc(items, (size += BUFSIZ))))
				die("cannot realloc %u bytes:", size);
    // <<<<<<<<<<<<<<<<<<<< json
		if ((p = strchr(buf, '\n')))
			*p = '\0';
    // >>>>>>>>>>>>>>>>>>>> json
    // ==================== json
    if (!(items[i].text = strdup(buf)))
    // <<<<<<<<<<<<<<<<<<<< json
			die("cannot strdup %u bytes:", strlen(buf) + 1);
    // >>>>>>>>>>>>>>>>>>>> json-multi-selection
    // ==================== json-multi-selection
    items[i].out = 0;
    // <<<<<<<<<<<<<<<<<<<< json-multi-selection
    // >>>>>>>>>>>>>>>>>>>> high-priority
    // ==================== high-priority
    // <<<<<<<<<<<<<<<<<<<< high-priority
		drw_font_getexts(drw->fonts, buf, strlen(buf), &tmpmax, NULL);
		if (tmpmax > inputw) {
			inputw = tmpmax;
      // >>>>>>>>>>>>>>>>>>>> json
      // ==================== json
      imax = i;
      // <<<<<<<<<<<<<<<<<<<< json
		}
	}
	if (items)
    // >>>>>>>>>>>>>>>>>>>> json
    // ==================== json
    items[i].text = NULL;
    // <<<<<<<<<<<<<<<<<<<< json
	inputw = items ? TEXTW(items[imax].text) : 0;
  // >>>>>>>>>>>>>>>>>>>> json
  // ==================== json
  lines = MIN(lines, i);
  // <<<<<<<<<<<<<<<<<<<< json
}

static void
run(void)
{
	XEvent ev;
  // >>>>>>>>>>>>>>>>>>>> preselect
  // ==================== preselect
  // <<<<<<<<<<<<<<<<<<<< preselect

	while (!XNextEvent(dpy, &ev)) {
    // >>>>>>>>>>>>>>>>>>>> preselect
    // ==================== preselect
    // <<<<<<<<<<<<<<<<<<<< preselect
		if (XFilterEvent(&ev, win))
			continue;
		switch(ev.type) {
    // >>>>>>>>>>>>>>>>>>>> mouse-support
    // ==================== mouse-support
    // <<<<<<<<<<<<<<<<<<<< mouse-support
		case DestroyNotify:
			if (ev.xdestroywindow.window != win)
				break;
			cleanup();
			exit(1);
		case Expose:
			if (ev.xexpose.count == 0)
				drw_map(drw, win, 0, 0, mw, mh);
			break;
		case FocusIn:
			/* regrab focus from parent window */
			if (ev.xfocus.window != win)
				grabfocus();
			break;
		case KeyPress:
			keypress(&ev.xkey);
			break;
		case SelectionNotify:
			if (ev.xselection.property == utf8)
				paste();
			break;
		case VisibilityNotify:
			if (ev.xvisibility.state != VisibilityUnobscured)
				XRaiseWindow(dpy, win);
			break;
		}
	}
}

static void
setup(void)
{
	int x, y, i, j;
	unsigned int du;
	XSetWindowAttributes swa;
	XIM xim;
	Window w, dw, *dws;
	XWindowAttributes wa;
	XClassHint ch = {"dmenu", "dmenu"};
#ifdef XINERAMA
	XineramaScreenInfo *info;
	Window pw;
	int a, di, n, area = 0;
#endif
	/* init appearance */
  // >>>>>>>>>>>>>>>>>>>> xresources
  // ==================== xresources
	for (j = 0; j < SchemeLast; j++)
		scheme[j] = drw_scm_create(drw, colors[j], 2);
  // <<<<<<<<<<<<<<<<<<<< xresources

	clip = XInternAtom(dpy, "CLIPBOARD",   False);
	utf8 = XInternAtom(dpy, "UTF8_STRING", False);

	/* calculate menu geometry */
  // >>>>>>>>>>>>>>>>>>>> line-height
  // ==================== line-height
	bh = drw->fonts->h + 2;
  // <<<<<<<<<<<<<<<<<<<< line-height
  // >>>>>>>>>>>>>>>>>>>> dynamic-options
  // ==================== dynamic-options
	lines = MAX(lines, 0);
  // <<<<<<<<<<<<<<<<<<<< dynamic-options
	mh = (lines + 1) * bh;
  // >>>>>>>>>>>>>>>>>>>> center
  // ==================== center
  // <<<<<<<<<<<<<<<<<<<< center
#ifdef XINERAMA
	i = 0;
	if (parentwin == root && (info = XineramaQueryScreens(dpy, &n))) {
		XGetInputFocus(dpy, &w, &di);
		if (mon >= 0 && mon < n)
			i = mon;
		else if (w != root && w != PointerRoot && w != None) {
			/* find top-level window containing current input focus */
			do {
				if (XQueryTree(dpy, (pw = w), &dw, &w, &dws, &du) && dws)
					XFree(dws);
			} while (w != root && w != pw);
			/* find xinerama screen with which the window intersects most */
			if (XGetWindowAttributes(dpy, pw, &wa))
				for (j = 0; j < n; j++)
					if ((a = INTERSECT(wa.x, wa.y, wa.width, wa.height, info[j])) > area) {
						area = a;
						i = j;
					}
		}
		/* no focused window is on screen, so use pointer location instead */
		if (mon < 0 && !area && XQueryPointer(dpy, root, &dw, &dw, &x, &y, &di, &di, &du))
			for (i = 0; i < n; i++)
				if (INTERSECT(x, y, 1, 1, info[i]))
					break;

    // >>>>>>>>>>>>>>>>>>>> center-xyw
    // ==================== center
		x = info[i].x_org;
		y = info[i].y_org + (topbar ? 0 : info[i].height - mh);
		mw = info[i].width;
    // <<<<<<<<<<<<<<<<<<<< center-xyw
		XFree(info);
	} else
#endif
	{
		if (!XGetWindowAttributes(dpy, parentwin, &wa))
			die("could not get embedding window attributes: 0x%lx",
			    parentwin);
    // >>>>>>>>>>>>>>>>>>>> center-xyw
    // ==================== center
		x = 0;
		y = topbar ? 0 : wa.height - mh;
		mw = wa.width;
    // <<<<<<<<<<<<<<<<<<<< center-xyw
	}
  // >>>>>>>>>>>>>>>>>>>> center
  // ==================== center
	promptw = (prompt && *prompt) ? TEXTW(prompt) - lrpad / 4 : 0;
  // <<<<<<<<<<<<<<<<<<<< center
	inputw = MIN(inputw, mw/3);
	match();

	/* create menu window */
  // >>>>>>>>>>>>>>>>>>>> managed
  // ==================== managed
  swa.override_redirect = True;
  // <<<<<<<<<<<<<<<<<<<< managed
	swa.background_pixel = scheme[SchemeNorm][ColBg].pixel;
  // >>>>>>>>>>>>>>>>>>>> mouse-support
  // ==================== mouse-support
  swa.event_mask = ExposureMask | KeyPressMask | VisibilityChangeMask;
  // <<<<<<<<<<<<<<<<<<<< mouse-support

	win = XCreateWindow(
    dpy,
    parentwin,
    x,
    y,
    mw,
    mh,
    // >>>>>>>>>>>>>>>>>>>> border
    0, // ==================== border
    // <<<<<<<<<<<<<<<<<<<< border
    CopyFromParent,
    CopyFromParent,
    CopyFromParent,
    CWOverrideRedirect | CWBackPixel | CWEventMask,
    &swa
  );

  // >>>>>>>>>>>>>>>>>>>> border
  // ==================== border
  // <<<<<<<<<<<<<<<<<<<< border

	XSetClassHint(dpy, win, &ch);


	/* input methods */
	if ((xim = XOpenIM(dpy, NULL, NULL, NULL)) == NULL)
		die("XOpenIM failed: could not open input device");

	xic = XCreateIC(xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
	                XNClientWindow, win, XNFocusWindow, win, NULL);

	XMapRaised(dpy, win);
  // >>>>>>>>>>>>>>>>>>>> managed
  // ==================== managed
  // <<<<<<<<<<<<<<<<<<<< managed
	if (embed) {
		XSelectInput(dpy, parentwin, FocusChangeMask | SubstructureNotifyMask);
		if (XQueryTree(dpy, parentwin, &dw, &w, &dws, &du) && dws) {
			for (i = 0; i < du && dws[i] != win; ++i)
				XSelectInput(dpy, dws[i], FocusChangeMask);
			XFree(dws);
		}
		grabfocus();
	}
	drw_resize(drw, mw, mh);
	drawmenu();
}

static void
usage(void)
{
	fputs(
    "usage: dmenu"
    "\t"
    "[-b]"
    "[-f]"
    "[-i]"
    "[-v]"
    // >>>>>>>>>>>>>>>>>>>> case-insensitive
    // ==================== case-insensitive
    // <<<<<<<<<<<<<<<<<<<< case-insensitive
    // >>>>>>>>>>>>>>>>>>>> center
    // ==================== center
    // <<<<<<<<<<<<<<<<<<<< center
    // >>>>>>>>>>>>>>>>>>>> fuzzymatch
    // ==================== fuzzymatch
    // <<<<<<<<<<<<<<<<<<<< fuzzymatch
    // >>>>>>>>>>>>>>>>>>>> password
    // ==================== password
    // <<<<<<<<<<<<<<<<<<<< password
    // >>>>>>>>>>>>>>>>>>>> incremental
    // ==================== incremental
    // <<<<<<<<<<<<<<<<<<<< incremental
    // >>>>>>>>>>>>>>>>>>>> reject-no-match
    // ==================== reject-no-match
    // <<<<<<<<<<<<<<<<<<<< reject-no-match
    // >>>>>>>>>>>>>>>>>>>> prefix-completition
    // ==================== prefix-completition
    // <<<<<<<<<<<<<<<<<<<< prefix-completition
    // >>>>>>>>>>>>>>>>>>>> instant
    // ==================== instant
    // <<<<<<<<<<<<<<<<<<<< instant
    "\n\t\t"
    "[-m monitor]"
    "[-w windowid]"
    // >>>>>>>>>>>>>>>>>>>> xyw
    // ==================== xyw
    // <<<<<<<<<<<<<<<<<<<< xyw
    "\n\t\t"
    // >>>>>>>>>>>>>>>>>>>> border
    // ==================== border
    // <<<<<<<<<<<<<<<<<<<< border
    "[-l lines]"
    "[-fn font]"
    "[-p prompt]"
    // >>>>>>>>>>>>>>>>>>>> dynamic-options
    // ==================== dynamic-options
    // <<<<<<<<<<<<<<<<<<<< dynamic-options
    // >>>>>>>>>>>>>>>>>>>> grid
    // ==================== grid
    // <<<<<<<<<<<<<<<<<<<< grid
    // >>>>>>>>>>>>>>>>>>>> preselect
    // ==================== preselect
    // <<<<<<<<<<<<<<<<<<<< preselect
    // >>>>>>>>>>>>>>>>>>>> initial-text
    // ==================== initial-text
    // <<<<<<<<<<<<<<<<<<<< initial-text
    // >>>>>>>>>>>>>>>>>>>> json
    // ==================== json
    // <<<<<<<<<<<<<<<<<<<< json
    // >>>>>>>>>>>>>>>>>>>> navhistory
    // ==================== navhistory
    // <<<<<<<<<<<<<<<<<<<< navhistory
    // >>>>>>>>>>>>>>>>>>>> line-height
    // ==================== line-height
    // <<<<<<<<<<<<<<<<<<<< line-height
    // >>>>>>>>>>>>>>>>>>>> high-priority
    // ==================== high-priority
    // <<<<<<<<<<<<<<<<<<<< high-priority
    "\n\t\t"
    "[-nb color]"
    "[-nf color]"
    "[-sb color]"
    "[-sf color]"
    // >>>>>>>>>>>>>>>>>>>> fuzzyhighlight
    // ==================== fuzzyhighlight
    // <<<<<<<<<<<<<<<<<<<< fuzzyhighlight
    "\n",
    stderr
  );
	exit(1);
}

// >>>>>>>>>>>>>>>>>>>> xresources
// ==================== xresources
// <<<<<<<<<<<<<<<<<<<< xresources

int
main(int argc, char *argv[])
{
	XWindowAttributes wa;
	int i, fast = 0;

	for (i = 1; i < argc; i++)
		/* these options take no arguments */
		if (!strcmp(argv[i], "-v")) {      /* prints version information */
			puts("dmenu-"VERSION);
			exit(0);
		} else if (!strcmp(argv[i], "-b")) /* appears at the bottom of the screen */
			topbar = 0;
		else if (!strcmp(argv[i], "-f"))   /* grabs keyboard before reading stdin */
			fast = 1;
    // >>>>>>>>>>>>>>>>>>>> case-insensitive
    // ==================== case-insensitive
    // <<<<<<<<<<<<<<<<<<<< case-insensitive
    // >>>>>>>>>>>>>>>>>>>> center
    // ==================== center
    // <<<<<<<<<<<<<<<<<<<< center
    // >>>>>>>>>>>>>>>>>>>> fuzzymatch
    // ==================== fuzzymatch
    // <<<<<<<<<<<<<<<<<<<< fuzzymatch
    // >>>>>>>>>>>>>>>>>>>> password
    // ==================== password
    // <<<<<<<<<<<<<<<<<<<< password
    // >>>>>>>>>>>>>>>>>>>> incremental
    // ==================== incremental
    // <<<<<<<<<<<<<<<<<<<< incremental
    // >>>>>>>>>>>>>>>>>>>> managed
    // ==================== managed
    // <<<<<<<<<<<<<<<<<<<< managed
    // >>>>>>>>>>>>>>>>>>>> reject-no-match
    // ==================== reject-no-match
    // <<<<<<<<<<<<<<<<<<<< reject-no-match
    // >>>>>>>>>>>>>>>>>>>> prefix-completition
    // ==================== prefix-completition
    // <<<<<<<<<<<<<<<<<<<< prefix-completition
    // >>>>>>>>>>>>>>>>>>>> instant
    // ==================== instant
    // <<<<<<<<<<<<<<<<<<<< instant
    // >>>>>>>>>>>>>>>>>>>> print-input-text
    // ==================== print-input-text
    // <<<<<<<<<<<<<<<<<<<< print-input-text
		else if (!strcmp(argv[i], "-i")) { /* case-insensitive item matching */
			fstrncmp = strncasecmp;
			fstrstr = cistrstr;
		} else if (i + 1 == argc)
			usage();
		/* these options take one argument */
    // >>>>>>>>>>>>>>>>>>>> grid
    // ==================== grid
		else if (!strcmp(argv[i], "-l"))   /* number of lines in vertical list */
			lines = atoi(argv[++i]);
    // <<<<<<<<<<<<<<<<<<<< grid
		else if (!strcmp(argv[i], "-m"))
			mon = atoi(argv[++i]);
		else if (!strcmp(argv[i], "-p"))   /* adds prompt to left of input field */
			prompt = argv[++i];
		else if (!strcmp(argv[i], "-fn"))  /* font or font set */
      // >>>>>>>>>>>>>>>>>>>> xresources
      // ==================== xresources
      fonts[0] = argv[++i];
      // <<<<<<<<<<<<<<<<<<<< xresources
		else if (!strcmp(argv[i], "-nb"))  /* normal background color */
      // >>>>>>>>>>>>>>>>>>>> xresources
      // ==================== xresources
      colors[SchemeNorm][ColBg] = argv[++i];
      // <<<<<<<<<<<<<<<<<<<< xresources
		else if (!strcmp(argv[i], "-nf"))  /* normal foreground color */
      // >>>>>>>>>>>>>>>>>>>> xresources
      // ==================== xresources
      colors[SchemeNorm][ColFg] = argv[++i];
      // <<<<<<<<<<<<<<<<<<<< xresources
		else if (!strcmp(argv[i], "-sb"))  /* selected background color */
      // >>>>>>>>>>>>>>>>>>>> xresources
      // ==================== xresources
			colors[SchemeSel][ColBg] = argv[++i];
      // <<<<<<<<<<<<<<<<<<<< xresources
		else if (!strcmp(argv[i], "-sf"))  /* selected foreground color */
      // >>>>>>>>>>>>>>>>>>>> xresources
      // ==================== xresources
      colors[SchemeSel][ColFg] = argv[++i];
      // <<<<<<<<<<<<<<<<<<<< xresources
		else if (!strcmp(argv[i], "-w"))   /* embedding window id */
			embed = argv[++i];
    // >>>>>>>>>>>>>>>>>>>> border
    // ==================== border
    // <<<<<<<<<<<<<<<<<<<< border
    // >>>>>>>>>>>>>>>>>>>> dynamic-options
    // ==================== dynamic-options
    // <<<<<<<<<<<<<<<<<<<< dynamic-options
    // >>>>>>>>>>>>>>>>>>>> fuzzyhighlight
    // ==================== fuzzyhighlight
    // <<<<<<<<<<<<<<<<<<<< fuzzyhighlight
    // >>>>>>>>>>>>>>>>>>>> grid
    // ==================== grid
    // <<<<<<<<<<<<<<<<<<<< grid
    // >>>>>>>>>>>>>>>>>>>> xyw
    // ==================== xyw
    // <<<<<<<<<<<<<<<<<<<< xyw
    // >>>>>>>>>>>>>>>>>>>> preselect
    // ==================== preselect
    // <<<<<<<<<<<<<<<<<<<< preselect
    // >>>>>>>>>>>>>>>>>>>> initial-text
    // ==================== initial-text
    // <<<<<<<<<<<<<<<<<<<< initial-text
    // >>>>>>>>>>>>>>>>>>>> json
    // ==================== json
    // <<<<<<<<<<<<<<<<<<<< json
    // >>>>>>>>>>>>>>>>>>>> navhistory
    // ==================== navhistory
    // <<<<<<<<<<<<<<<<<<<< navhistory
    // >>>>>>>>>>>>>>>>>>>> line-height
    // ==================== line-height
    // <<<<<<<<<<<<<<<<<<<< line-height
    // >>>>>>>>>>>>>>>>>>>> high-priority
    // ==================== high-priority
    // <<<<<<<<<<<<<<<<<<<< high-priority
		else
			usage();

	if (!setlocale(LC_CTYPE, "") || !XSupportsLocale())
		fputs("warning: no locale support\n", stderr);
	if (!(dpy = XOpenDisplay(NULL)))
		die("cannot open display");
	screen = DefaultScreen(dpy);
	root = RootWindow(dpy, screen);
	if (!embed || !(parentwin = strtol(embed, NULL, 0)))
		parentwin = root;
	if (!XGetWindowAttributes(dpy, parentwin, &wa))
		die("could not get embedding window attributes: 0x%lx",
		    parentwin);
	drw = drw_create(dpy, screen, root, wa.width, wa.height);
  // >>>>>>>>>>>>>>>>>>>> xresources
  // ==================== xresources
  if (!drw_fontset_create(drw, fonts, LENGTH(fonts)))
  // <<<<<<<<<<<<<<<<<<<< xresources
		die("no fonts could be loaded.");

  // >>>>>>>>>>>>>>>>>>>> xresources
  // ==================== xresources
  // <<<<<<<<<<<<<<<<<<<< xresources
	lrpad = drw->fonts->h;

#ifdef __OpenBSD__
	if (pledge("stdio rpath", NULL) == -1)
		die("pledge");
#endif

  // >>>>>>>>>>>>>>>>>>>> navhistory
  // ==================== navhistory
  // <<<<<<<<<<<<<<<<<<<< navhistory

	if (fast && !isatty(0)) {
		grabkeyboard();
    // >>>>>>>>>>>>>>>>>>>> dynamic-options-json
    // ==================== dynamic-options-json
		readstdin();
    // <<<<<<<<<<<<<<<<<<<< dynamic-options-json
	} else {
    // >>>>>>>>>>>>>>>>>>>> dynamic-options-json
    // ==================== dynamic-options-json
		readstdin();
    // <<<<<<<<<<<<<<<<<<<< dynamic-options-json
		grabkeyboard();
	}
	setup();
	run();

	return 1; /* unreachable */
}
