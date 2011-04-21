#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cube.h"
#include "draw.h"
#include "draw_3d.h"
#include "3d.h"
#include "effect.h"
#include "gameoflife.h"
#include "udp.h"

void *cube_updater (unsigned char rs232_cube[8][8]);

int main (int argc, char **argv)
{

    udp_init();
    //cube_init();

    fill(0x00);
    delay_ms(1);


    //while(1)
    //    rotateplane();
//        stars3d(100000,100);
//        plasma3d(10000,70);


        //delay_ms(1000);

   
        //sidewall_dothemall();
		//effect_rotate_random_pixels(10000,100,60);
		//spinningcube(20000,100);
		//spinningcube2(20000,100);
		//globespin(20000,100);
        //
        //
        //sidewaves(20000,100);
        //fireworks(4,50,1200);
    //    effect_stringfly2("PARTLY CLOUDY");
    


	while (1)
	{
            printf("Testing swirl\n");
            swirl_a_cube(2000,10000);
            
/*
            printf("Effect: gol_play_randnice");
            gol_play_randnice(6);

		printf("Effect: sidewaves\n");
		sidewaves(2000,100);

		printf("Effect: ripples\n");
		ripples(2000,100);

		printf("Effect: linespin\n");
		linespin(2000,100);

		printf("Effect: sinelines\n");
		sinelines(2000,100);

		printf("Effect: spheremove\n");
		spheremove(1500,100);

		printf("Effect: fireworks\n");
		fireworks(7,50,1200);

*/
	}

}

