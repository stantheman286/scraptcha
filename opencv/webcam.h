#ifndef WEBCAM_H
#define WEBCAM_H

// Definitions and Prototypes
#define CAPTURE 0
#define LIVE 1

#define TRASH 0
#define RECYCLING 1
#define COMPOST 2

int takePicture(char *, int);
int detectScrap(char *);

#endif
