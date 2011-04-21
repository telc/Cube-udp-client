#include "draw.h"
#include "draw_3d.h"
#include "3d.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


void rotateplane()
{
    int i,it;
    int iterations = 100000;
    int delay = 100;
    vertex voxels[64];
    vertex rotated;
    vertex center = {3.5, 3.5, 3.5};
    float rx = 0, ry = 0, rz = 0;
    float z,y;

    for (i=0; i<8; i++)
    {
        z = 3.5+sin((float)i/8)*3;
        y = 3.5+cos((float)i/8)*3;

        voxels[i].x = (float)i;
        voxels[i].y = (float)i;
        voxels[i].z = (float)i;

        printf("Vertex: %f %f \n", z, y);
    }

    for (it=0; it<iterations; it++)
    {

/*        for (i=0; i<64; i++)
        {
            z = 4+sin((float)i/8)*(2.5+sin((float)it/300));
            y = 4+cos((float)i/8)*(2.5+cos((float)it/300));

            voxels[i].x = 3.5;
            voxels[i].y = y;
            voxels[i].z = z;
        }*/

        rx = sin((float)it/50)*2;
        ry = cos((float)it/113)*3;
        rz = sin((float)it/50);

//        rx = (float)it/100;
//        ry = (float)it/100;
        rz = (float)it/75;

        for (i=0; i<64; i++)
        {
            rotated = point_rotate_around_point(voxels[i], center, rx, ry, rz);
            setvoxel(lroundf(rotated.x), lroundf(rotated.y), lroundf(rotated.z));
        }
        delay_ms(delay);
        fill(0x00);
    }
}

void stars3d (int iterations, int delay)
{
    int nstars = 10;
    int i,ii;
    float rx = 0;
    float ry = 0;
    float rz = 0;

    vertex stars[nstars];
    vertex star_rotated;
    vertex center = {3.5, 3.5, 3.5};

    for (i=0; i<nstars; i++)
    {
        stars[i].x = 8 + (float)(rand()%80)/10.0;
        stars[i].y = (float)(rand()%100)/10.0-1.0;
        stars[i].z = (float)(rand()%100)/10.0-1.0;

        printf("Star: %f %f %f\n", stars[i].x, stars[i].y, stars[i].z);
    }

    for (i=0; i<iterations; i++)
    {
//        rx = sin((float)i/500)/2;
//        ry = sin((float)i/700)/2;
//        rz = sin((float)i/300)/2;

        fill(0x00);
        for (ii=0; ii<nstars; ii++)
        {
            stars[ii].x -= 0.2;

            //printf("X = %f\n", stars[ii].x);

            //setvoxel(lroundf(stars[ii].x),lroundf(stars[ii].y),lroundf(stars[ii].z));

            if (stars[ii].x < 1.0)
            {
                stars[ii].x = 8 + (float)(rand()%80)/10.0;
                stars[ii].y = (float)(rand()%100)/10.0-1.0;
                stars[ii].z = (float)(rand()%100)/10.0-1.0;
            }

            star_rotated = point_rotate_around_point(stars[ii], center, rx, ry, rz);

            setvoxel(lroundf(star_rotated.x),lroundf(star_rotated.y),lroundf(star_rotated.z));
        }

        delay_ms(delay);
    }

}

void plasma3d (int iterations, int delay)
{
    int i,x,y,z,zz;
    float f_wave, f_wave2, f_wave3;
    float f_z;
    int z1,z2;
    for (i=0; i<iterations; i++)
    {
        fill(0x00);
        for (x=0; x<8; x++)
        {
            f_wave = 4+(sin((float)i/60.0+(float)x/3)*4);


            for (y=0; y<8; y++)
            {

                f_wave2 = 4+sin((float)i/50.0+(float)y/4+(float)x/4)*4;

                f_wave3 = 4+sin(distance2d(sin((float)i/300)*4,cos((float)i/200)*4,x,y)/3+(float)i/60)*4;

                f_z = (f_wave+f_wave2+f_wave3)/3;
                z = (int)f_z;

                setvoxel(x,y,z);
            }
        }

        delay_ms(delay);
    }
}



void sidewall_dothemall(void)
{
    intvertex rotation = {0,0,0};

    sidewall_swipe(&rotation);
}

void sidewall_swipe (intvertex *rotation)
{
    float i;

    float y,z,fx;

    int step,a,x;

    for (step=0; step<150;step++)
    {
        fill(0x00);

        i = (float)step/100;
        z = sin(i);
        y = cos(i);
        
        for (a=0; a<15; a++)
        {
            z = sin(i)*((float)a/15*8);
            y = cos(i)*((float)a/15*8);

            for (x=0; x<8; x++)
            {
                setvoxel(x,lroundf(y),lroundf(z));
            }


       }

       //sidewall_do_rotation(rotation);

       delay_ms(75);
    }

//    sidewall_update_rotation();

}

void sidewall_update_rotation (intvertex *rotation, int x, int y, int z)
{
    if (x == 1)
    {
        rotation->x ^= 0x01; // flip bit 0.
    }
    if (y == 1)
    {
        rotation->y ^= 0x01; // flip bit 0.
    }
    if (z == 1)
    {
        rotation->z ^= 0x01; // flip bit 0.
    }
}

void sidewall_do_rotation(intvertex *rotation)
{
    if (rotation->x == 1)
    {
        mirror_x();
    }

    if (rotation->y == 1)
    {
        mirror_y();
    }

    if (rotation->z == 1)
    {
        mirror_z();
    }

}

void spinningcube (int iterations, int delay)
{
	fill(0x00);

	float cube_size, sin_base;
	float rot_x, rot_y, rot_z;

	vertex cube_corners[8];
	int i,c;
	int x,y,z;

	vertex cube_center = {3.5, 3.5, 3.5};
	//vertex cube_center = {4, 4, 4};
	cube_size = 4;


	for (i=0; i<iterations; i++)
	{
		//printf("i = %d\n",i);

		rot_x = 0;
		rot_y = 0;
		rot_z = 0;

		rot_x = (float)i/100;
		rot_y = (float)i/1000;
		rot_z = (float)i/1000;

		//cube_size = (sin((float)i/500)+1)*2+1;
		cube_size = 4;

		/*rot_x = sin((float)i/1000)*2;
		rot_y = cos((float)i/1000)*2;
		rot_z = sin((float)i/1000)*2;
		*/
		// Animate!
		//rot_y = cos((float)i/150);
		//rot_z = sin((float)i/200);

		// Calculate cube corners
		calculate_cube_corners (cube_corners, cube_center, cube_size);

		for (c=0; c<8; c++)
		{
			cube_corners[c] = point_rotate_around_point(cube_corners[c], cube_center, rot_x, rot_y, rot_z);

			//printf("Point %d: X %f \t Y %f \t Z %f\n",c,cube_corners[c].x,cube_corners[c].y,cube_corners[c].z);
		}


		fill(0x00);
		for (c=0; c<8; c++)
		{
			x = lroundf(cube_corners[c].x);
			y = lroundf(cube_corners[c].y);
			z = lroundf(cube_corners[c].z);

			//printf("Point INT %d: X %d \t Y %d \t Z %d\n",c,x,y,z);

			setvoxel(x,y,z);
			draw_cube_wireframe(cube_corners);
		}
		delay_ms(100);

	}


}

void spinningcube2 (int iterations, int delay)
{
	int linepoints = 20;
	int sumpoints = (linepoints-1)*8+(linepoints-2)*4;
	vertex points[sumpoints];
	vertex rotated[sumpoints];

	int i;
	int p = 0;

	vertex center = {3.5, 3.5, 3.5};
	float size = 4;

	for (i=1; i<linepoints; i++)
	{
		// Upper lid
		points[p].x = center.x-(size/2) + size/(float)linepoints*(float)i;
		points[p].y = center.y-(size/2);
		points[p++].z = center.z-(size/2);

		points[p].x = center.x+(size/2) - size/(float)linepoints*(float)i;
		points[p].y = center.y+(size/2);
		points[p++].z = center.z-(size/2);

		points[p].x = center.x-(size/2);
		points[p].y = center.y-(size/2) + size/(float)linepoints*(float)i;
		points[p++].z = center.z-(size/2);

		points[p].x = center.x+(size/2);
		points[p].y = center.y+(size/2) - size/(float)linepoints*(float)i;
		points[p++].z = center.z-(size/2);

		// Lower lid
		points[p].x = center.x-(size/2) + size/(float)linepoints*(float)i;
		points[p].y = center.y-(size/2);
		points[p++].z = center.z+(size/2);

		points[p].x = center.x+(size/2) - size/(float)linepoints*(float)i;
		points[p].y = center.y+(size/2);
		points[p++].z = center.z+(size/2);

		points[p].x = center.x-(size/2);
		points[p].y = center.y-(size/2) + size/(float)linepoints*(float)i;
		points[p++].z = center.z+(size/2);

		points[p].x = center.x+(size/2);
		points[p].y = center.y+(size/2) - size/(float)linepoints*(float)i;
		points[p++].z = center.z+(size/2);
	}

	/*for (i=1; i<(linepoints-1); i++)
	{	
		points[p].x = center.x+(size/2);
		points[p].y = center.y+(size/2);
		points[p++].z = center.z-(size/2) + size/(float)linepoints*(float)i;

		points[p].x = center.x-(size/2);
		points[p].y = center.y+(size/2);
		points[p++].z = center.z-(size/2) + size/(float)linepoints*(float)i;

		points[p].x = center.x+(size/2);
		points[p].y = center.y-(size/2);
		points[p++].z = center.z-(size/2) + size/(float)linepoints*(float)i;

		points[p].x = center.x-(size/2);
		points[p].y = center.y-(size/2);
		points[p++].z = center.z-(size/2) + size/(float)linepoints*(float)i;

	}*/

	fill(0x00);

	int ii;
	float rot_x = 0;
	float rot_y = 0;
	float rot_z = 0;

	for (ii=0; ii<iterations; ii++)
	{

		printf("iteration: %i \n",ii);
		
		rot_x = (float)ii/116;
		rot_y = (float)ii/212;
		rot_z = (float)ii/150;

		for (i=0; i<p; i++)
		{
			rotated[i] = point_rotate_around_point(points[i], center, rot_x, rot_y, rot_z);
		}

		fill(0x00);
		for (i=0; i<p; i++)
		{
			//printf("Setting point %i: %f %f %f \n", i, points[i].x, points[i].y, points[i].z);
			setvoxel(lroundf(rotated[i].x), lroundf(rotated[i].y), lroundf(rotated[i].z));
		}

		delay_ms(delay);
	}

	delay_ms(1000000);
}

void globespin (int iterations, int delay)
{
	
	vertex *points;
	float diameter = 6;
	float radius = diameter/2;
	vertex center = {3.5, 3.5, 3.5};

	float longitude = 4;
	float latitude = 3;
	int circ_points = 64;
	float steps;

	float x,y,z;
	int i,ii;


	fill(0x00);
	for (i=0; i<(int)latitude; i++)
	{
		z = diameter/latitude*((float)i+1);
		//z -= center.z/2;

		steps = 1/(float)circ_points*4;
		
		printf("stepping: %f\n",steps);

		for (ii=0; ii<circ_points; ii++)
		{
			float x = sin(steps*(float)ii)*radius + center.x/2;
			float y = cos(steps*(float)ii)*radius + center.y/2;

			printf("Point %i: %f %f %f \n", ii, x, y, z);

			setvoxel(lroundf(x), lroundf(y), lroundf(z));
		}

	}

	delay_ms(100000);


/*	for (ii=0; ii<iterations; ii++)
	{

		printf("iteration: %i \n",ii);
		
		rot_x = (float)ii/116;
		rot_y = (float)ii/212;
		rot_z = (float)ii/150;

		for (i=0; i<p; i++)
		{
			rotated[i] = point_rotate_around_point(points[i], center, rot_x, rot_y, rot_z);
		}

		fill(0x00);
		for (i=0; i<p; i++)
		{
			//printf("Setting point %i: %f %f %f \n", i, points[i].x, points[i].y, points[i].z);
			setvoxel(lroundf(rotated[i].x), lroundf(rotated[i].y), lroundf(rotated[i].z));
		}

		delay_ms(delay);
	}*/
}

void linespin (int iterations, int delay)
{
	float top_x, top_y, top_z, bot_x, bot_y, bot_z, sin_base;
	float center_x, center_y;

	center_x = 4;
	center_y = 4;

	int i, z;
	for (i=0;i<iterations;i++)
	{

		//printf("Sin base %f \n",sin_base);

		for (z = 0; z < 8; z++)
		{

		sin_base = (float)i/50 + (float)z/(10+(7*sin((float)i/200)));

		top_x = center_x + sin(sin_base)*5;
		top_y = center_x + cos(sin_base)*5;
		//top_z = center_x + cos(sin_base/100)*2.5;

		bot_x = center_x + sin(sin_base+3.14)*10;
		bot_y = center_x + cos(sin_base+3.14)*10;
		//bot_z = 7-top_z;
		
		bot_z = z;
		top_z = z;

		//setvoxel(lroundf( top_x), lroundf( top_y), 7);
		//setvoxel(lroundf( bot_x), lroundf( bot_y), 0);

		//printf("P1: %i %i %i P2: %i %i %i \n", lroundf( top_x), lroundf( top_y), 7, lroundf( bot_x), lroundf( bot_y), 0);

		//line_3d(lroundf( top_x), lroundf( top_y), lroundf( top_z), lroundf( bot_x), lroundf( bot_y), lroundf( bot_z));
		line_3d(lroundf( top_z), lroundf( top_x), lroundf( top_y), lroundf( bot_z), lroundf( bot_x), lroundf( bot_y));
		}

		delay_ms(120);
		fill(0x00);
	}

}

void sinelines (int iterations, int delay)
{
	int i,x;

	float left, right, sine_base, x_dividor,ripple_height;

	for (i=0; i<iterations; i++)
	{
		for (x=0; x<8 ;x++)
		{
			x_dividor = 2 + sin((float)i/100)+1;
			ripple_height = 3 + (sin((float)i/200)+1)*6;

			sine_base = (float) i/40 + (float) x/x_dividor;

			left = 4 + sin(sine_base)*ripple_height;
			right = 4 + cos(sine_base)*ripple_height;
			right = 7-left;

			//printf("%i %i \n", lroundf( left), lroundf( right));

			line_3d(0-3, x, lroundf( left), 7+3, x, lroundf( right));
			//line_3d(lroundf( right), 7, x);
		}
	
	delay_ms(delay);
	fill(0x00);
	}
}

// Display a sine wave running out from the center of the cube.
void ripples (int iterations, int delay)
{
	float origin_x, origin_y, distance, height, ripple_interval;
	int x,y,i;

	fill(0x00);

	for (i=0;i<iterations;i++)
	{
		for (x=0;x<8;x++)
		{
			for (y=0;y<8;y++)
			{
				distance = distance2d(3.5,3.5,x,y)/9.899495*8;
				//distance = distance2d(3.5,3.5,x,y);
				ripple_interval =1.3;
				height = 4+sin(distance/ripple_interval+(float) i/50)*4;

				setvoxel(x,y,lroundf( height));	
			}
		}
		delay_ms(delay);
		fill(0x00);
	}
}

void sidewaves (int iterations, int delay)
{
	float origin_x, origin_y, distance, height, ripple_interval;
	int x,y,i;

	fill(0x00);

	for (i=0;i<iterations;i++)
	{

		origin_x = 3.5+sin((float)i/500)*4;
		origin_y = 3.5+cos((float)i/500)*4;
		
		for (x=0;x<8;x++)
		{
			for (y=0;y<8;y++)
			{
				distance = distance2d(origin_x,origin_y,x,y)/9.899495*8;
				ripple_interval =2;
				height = 4+sin(distance/ripple_interval+(float) i/50)*3.6;

				setvoxel(x,y,lroundf( height));
				setvoxel(x,y,lroundf( height));
					
			}
		}

		delay_ms(delay);
		fill(0x00);
	}
}

void spheremove (int iterations, int delay)
{
	
	fill(0x00);

	float origin_x, origin_y, origin_z, distance, diameter;

	origin_x = 0;
	origin_y = 3.5;
	origin_z = 3.5;

	diameter = 3;

	int x, y, z, i;

	for (i=0; i<iterations; i++)
	{
		origin_x = 3.5+sin((float)i/50)*2.5;
		origin_y = 3.5+cos((float)i/50)*2.5;
		origin_z = 3.5+cos((float)i/30)*2;

		diameter = 2+sin((float)i/150);

		for (x=0; x<8; x++)
		{
			for (y=0; y<8; y++)
			{
				for (z=0; z<8; z++)
				{
					distance = distance3d(x,y,z, origin_x, origin_y, origin_z);
					//printf("Distance: %f \n", distance);

					if (distance>diameter && distance<diameter+1)
					{
						setvoxel(x,y,z);
					}
				}
			}
		}

		delay_ms(delay);
		fill(0x00);
	}

}

void fireworks (int iterations, int n, int delay)
{
	fill(0x00);

	int i,f,e;

	float origin_x = 3;
	float origin_y = 3;
	float origin_z = 3;

	int rand_y, rand_x, rand_z;

	float slowrate, gravity;

	// Particles and their position, x,y,z and their movement, dx, dy, dz
	float particles[n][6];

	for (i=0; i<iterations; i++)
	{

		origin_x = rand()%4;
		origin_y = rand()%4;
		origin_z = rand()%2;
		origin_z +=5;
        origin_x +=2;
        origin_y +=2;

		// shoot a particle up in the air
		for (e=0;e<origin_z;e++)
		{
			setvoxel(origin_x,origin_y,e);
			delay_ms(600+500*e);
			fill(0x00);
		}

		// Fill particle array
		for (f=0; f<n; f++)
		{
			// Position
			particles[f][0] = origin_x;
			particles[f][1] = origin_y;
			particles[f][2] = origin_z;
			
			rand_x = rand()%200;
			rand_y = rand()%200;
			rand_z = rand()%200;

			// Movement
			particles[f][3] = 1-(float)rand_x/100; // dx
			particles[f][4] = 1-(float)rand_y/100; // dy
			particles[f][5] = 1-(float)rand_z/100; // dz
		}

		// explode
		for (e=0; e<25; e++)
		{
			slowrate = 1+tan((e+0.1)/20)*10;
			
			gravity = tan((e+0.1)/20)/2;

			for (f=0; f<n; f++)
			{
				particles[f][0] += particles[f][3]/slowrate;
				particles[f][1] += particles[f][4]/slowrate;
				particles[f][2] += particles[f][5]/slowrate;
				particles[f][2] -= gravity;

				setvoxel(particles[f][0],particles[f][1],particles[f][2]);


			}

			delay_ms(delay);
			fill(0x00);
		}

	}

}

void swirl_a_cube(int iterations, int delay)
{
    int i;
    fill(0x00);
    box_walls(1,1,1,6,6,6);
    delay_ms(2000);
    for (i=0; i<iterations; i++)
    {
        swirl_cube_contents();
        delay_ms(delay);
    }
}

void effect_rotate_random_pixels (int iterations, int delay, int pixels)
{
	vertex points[pixels];
	vertex rotated[pixels];

	float fy, fx, fz;
	int x,y,z;
	int i,p;

	float rot_x = 0;
	float rot_y = 0;
	float rot_z = 0;
	vertex cube_center = {3.5, 3.5, 3.5};

	for (i=0; i<pixels; i++)
	{
		x = rand()%1200-200;	
		y = rand()%1200-200;	
		z = rand()%1200-200;
		fx = (float)x/100;
		fy = (float)y/100;
		fz = (float)z/100;

		points[i].x = fx;
		points[i].y = fy;
		points[i].z = fz;

		setvoxel(lroundf(points[i].x), lroundf(points[i].y), lroundf(points[i].z));
		delay_ms(100);
	}
	delay_ms(10000);

	for (i=0; i<iterations; i++)
	{
		rot_x = (float)i/75;
		rot_y = (float)i/150;
		rot_z = (float)i/200;

		for (p=0; p<pixels; p++)
		{
			rotated[p] = point_rotate_around_point (points[p], cube_center, rot_x, rot_y, rot_z);
		}

		fill(0x00);
		for (p=0; p<pixels; p++)
		{
			setvoxel(lroundf(rotated[p].x), lroundf(rotated[p].y), lroundf(rotated[p].z));
		}

		delay_ms(delay);
	}

	fill(0x00);
}


float distance2d (float x1, float y1, float x2, float y2)
{	
	float dist;
	dist = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));

	return dist;
}

float distance3d (float x1, float y1, float z1, float x2, float y2, float z2)
{	
	float dist;
	dist = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));

	return dist;
}




