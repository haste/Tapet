#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include <Imlib2.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	Display *dpy = XOpenDisplay(NULL);
	int screen = DefaultScreen(dpy);
	Window root = RootWindow(dpy, screen);
	Visual *vis = DefaultVisual(dpy, screen);

	int screenDepth = DefaultDepth(dpy, screen);
	int screenWidth = DisplayWidth(dpy, screen);
	int screenHeight = DisplayHeight(dpy, screen);

	unsigned int offsetX = 0;
	unsigned int offsetY = 0;

	unsigned int i;
	for(i = 1; i < argc; i++) {
		int c = argv[i][1];

		switch(c) {
			case 'x':
				if(++i < argc)
					offsetX = -atoi(argv[i]);
				break;

			case 'y':
				if(++i < argc)
					offsetY = -atoi(argv[i]);
				break;
		}
	}

	Imlib_Image image = imlib_load_image(argv[argc - 1]);
	if(image)
	{
		Pixmap bg = XCreatePixmap(dpy, root, screenWidth, screenHeight, screenDepth);

		imlib_context_set_image(image);
		imlib_context_set_display(dpy);
		imlib_context_set_visual(vis);
		imlib_context_set_drawable(bg);

		imlib_render_image_on_drawable(offsetX, offsetY);

		// Ripped out of xsetroot.
		Atom atomRoot = XInternAtom(dpy, "_XROOTPMAP_ID", False);
		XChangeProperty(
			dpy, root, atomRoot,
			XA_PIXMAP, 32, PropModeReplace,
			(unsigned char *) &bg, 1
		);

		XKillClient(dpy, AllTemporary);
		XSetCloseDownMode(dpy, RetainPermanent);

		XSetWindowBackgroundPixmap(dpy, root, bg);
		XClearWindow(dpy, root);

		XFlush(dpy);
		XSync(dpy, False);

		imlib_free_image();
	}

	return 0;
}
