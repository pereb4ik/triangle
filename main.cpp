#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glx.h>

Display *display;
Window root;
GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
XVisualInfo *vi;
XSetWindowAttributes swa;
Window window;
GLXContext glc;
XWindowAttributes gwa;
XEvent ev;

float width = 600, height = 600;
int done = 0;

GLfloat x = 0.0;
GLfloat y = 0.0;

GLfloat BC[] = {37.0 / 255.0, 133.0 / 255.0, 75.0 / 255.0};

void DrawTriangle() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(BC[0], BC[1], BC[2], 1.0);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(x, -y);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(x - 1.0, 1.0 - y);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(x, 1.0 - y);
    glEnd();
    glXSwapBuffers(display, window);
}

int main() {
    display = XOpenDisplay(NULL);

    if (display == NULL) {
        printf("\n\tcannot connect to X server\n\n");
        return 0;
    }

    root = DefaultRootWindow(display);

    vi = glXChooseVisual(display, 0, att);

    if (vi == NULL) {
        printf("\n\tno appropriate visual found\n\n");
        return 0;
    }

    swa.colormap = XCreateColormap(display, root, vi->visual, AllocNone);
    swa.event_mask =
            ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | DestroyNotify;

    window = XCreateWindow(display, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual,
                           CWColormap | CWEventMask,
                           &swa);

    Atom wmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(display, window, &wmDeleteWindow, 1);

    XStoreName(display, window, "test");

    glc = glXCreateContext(display, vi, NULL, GL_TRUE);
    glXMakeCurrent(display, window, glc);

    glEnable(GL_DEPTH_TEST);

    XMapWindow(display, window);

    bool hasTriangle = false;

    while (!done) {
        XNextEvent(display, &ev);

        switch (ev.type) {
            case Expose: {
                XGetWindowAttributes(display, window, &gwa);
                width = gwa.width;
                height = gwa.height;
                glViewport(0, 0, width, height);
                if (hasTriangle) {
                    DrawTriangle();
                } else {
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    glClearColor(BC[0], BC[1], BC[2], 1.0);
                    glXSwapBuffers(display, window);
                }
                break;
            }
            case ClientMessage: {
                if (ev.xclient.data.l[0] == wmDeleteWindow) {
                    printf("%lu %s", window, "destroy\n");
                    glXMakeCurrent(display, None, NULL);
                    glXDestroyContext(display, glc);
                    XDestroyWindow(display, window);
                    XCloseDisplay(display);
                    done = 1;
                }
                break;
            }
            case ButtonPress: {
                if (ev.xbutton.button == Button1) {
                    hasTriangle = true;
                    while (ev.type != ButtonRelease) {
                        x = (GLfloat) (ev.xbutton.x * 2.0 / width);
                        y = (GLfloat) (ev.xbutton.y * 2.0 / height);
                        DrawTriangle();
                        XNextEvent(display, &ev);
                    }
                }
                break;
            }
        }
    }
    return 0;
}