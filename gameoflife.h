#ifndef GOL_H
#define GOL_H

void gol_play_randnice (int iterations);
void gol_play (int iterations, int delay);
unsigned char gol_count_neighbors (int x, int y, int z);
void gol_nextgen (void);
int gol_count_changes (void);

#endif
