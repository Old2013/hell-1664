#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <stdbool.h>


// Window lib on X11.
// for connect paste:
// #include "winlib.h"
// Winlib should be in the same dir with your code.

Display *d;
int s, w, h;
Window win;
XImage *img;
unsigned char *pixels;

void winit(int W, int H) {
    d = XOpenDisplay(NULL);
    s = DefaultScreen(d);
    w = W;
    h = H;

    win = XCreateSimpleWindow(d, RootWindow(d, s), 0, 0, w, h, 1, 0, 0xFFFFFF);

    pixels = (unsigned char*)malloc(w * h * 4);
    img = XCreateImage(d, DefaultVisual(d, s), DefaultDepth(d, s), ZPixmap, 0, (char*)pixels, w, h, 32, w * 4);

    XSelectInput(d, win, ExposureMask | KeyPressMask);
    XMapWindow(d, win);
}


void wclose() {
    XDestroyImage(img);
    XCloseDisplay(d);
}

bool wupdate()
{
    XEvent e;
    if (XPending(d))
    {
        XNextEvent(d, &e);
        if (e.type == KeyPress) return true;
    }
    XPutImage(d, win, DefaultGC(d, s), img, 0, 0, 0, 0, w, h);
    return false;
};
