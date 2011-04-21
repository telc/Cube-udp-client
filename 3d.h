#ifndef EFFECT3D_H
#define EFFECT3D_H


void effect_rotate_random_pixels (int iterations, int delay, int pixels);

void linespin (int iterations, int delay);

void ripples (int iterations, int delay);
float distance2d (float x1, float y1, float x2, float y2);
float distance3d (float x1, float y1, float z1, float x2, float y2, float z2);


void sidewall_update_rotation (intvertex *rotation, int x, int y, int z);
void sidewall_swipe (intvertex *rotation);

void swirl_a_cube(int iterations, int delay);

//typedef struct {float x; float y; float z;} vertex;

#endif
