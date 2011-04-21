#include "draw_3d.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

vertex point_rotate_around_point (vertex point, vertex center, float rotation_x, float rotation_y, float rotation_z)
{
	float x, y, z;
	float sx,cx, sy,cy, sz,cz;
	float xy,xz, yx,yz, zx,zy;
	vertex newpoint;

	// Center all the points around 0,0,0
	x = point.x - center.x;
	y = point.y - center.y;
	z = point.z - center.z;

	// Precalculate sinus and cosinus for each axis rotation
	sx = sin(rotation_x);
	cx = cos(rotation_x);

	sy = sin(rotation_y);
	cy = cos(rotation_y);

	sz = sin(rotation_z);
	cz = cos(rotation_z);


	// Rotation around x
	xy = cx*y - sx*z;
	xz = sx*y + cx*z;
	
	// Rotation around y
	yz = cy*xz - sy*x;
	yx = sy*xz + cy*x;
	
	// Rotation around z
	zx = cz*yx - sz*xy;
	zy = sz*yx + cz*xy;

	newpoint.x = zx + center.x;
	newpoint.y = zy + center.y;
	newpoint.z = yz + center.z;


	return newpoint;
}

void get_cube(vertex * voxels, int * size)
{
    int x,y,z,n=0;
    //vertex *voxels = (vertex*)malloc(sizeof(vertex)*512);
    for(x=0; x<8; x++)
    {
        for(y=0; y<8; y++)
        {
            for(z=0; z<8; z++)
            {
                if(getvoxel(x, y, z) == 0x01)
                {
                    voxels[n].x = (float)x;
                    voxels[n].y = (float)y;
                    voxels[n++].z = (float)z;
                }

            }
        }
    }
    *size = n;
    //return voxels;
}

void swirl_cube_contents()
{
    int i,n;
    float a,b,c,u,v,x,y,ang;
    vertex * voxels = malloc(sizeof(vertex)*512);
    get_cube(voxels, &n);

    // Swirl center
    c = 3.5;

    printf("FOO %d:\n",n);
    fill(0x00);
    for(i=0;i<n;i++)
    {
        // Set center of swirl
        x = voxels[i].x - c;
        y = voxels[i].y - c;

        // Set size and effect
        a = 7 - voxels[i].z;
        b = voxels[i].z;

        ang = a * exp(-(x*x+y*y)/(b*b));
        u = cos(ang)*x + sin(ang)*y;
        v = -sin(ang)*x + cos(ang)*y;

        // Set center of swirl
        u += c;
        v += c;

        printf("x: %f y: %f z: %f\n", u, v, voxels[i].z);

        setvoxel(lroundf(u), lroundf(v), lroundf(voxels[i++].z));
    }
    printf("\n\n");
    free(voxels);
}

void rotate_cube_contents(float rx, float ry, float rz)
{
    // get voxels
    int x,y,z,i,n;
    i=0;
    vertex voxels[64];

    for (x=0; x<8; x++)
    {
        for (y=0; y<8; y++)
        {
            for (z=0; z<8; z++)
            {
                if (getvoxel(x, y, z) == 0x01)
                {
                    voxels[i].x = (float)x;
                    voxels[i].y = (float)y;
                    voxels[i].z = (float)z;
                    i++;
                }
            }
        }
    }
    fill(0x00);

    //printf("ballekanon\n");

    //printf("rot %f %f %f\n", rx, ry, rz);

    vertex center = {3.5, 3.5, 3.5};
    vertex voxel;

    for (n=0; n<i; n++)
    {
        voxel = point_rotate_around_point(voxels[n], center, rx, ry, rz);

        setvoxel(lroundf(voxel.x), lroundf(voxel.y), lroundf(voxel.z));
    }

}

// Calculate all 8 corners of a cube.
void calculate_cube_corners (vertex pnt[8], vertex center, float size)
{

	// Distance from center on any axis.
	float dist = size/2;

	// Points
	// X				Y				Z

	pnt[0].x = center.x+dist;	pnt[0].y = center.y+dist;	pnt[0].z = center.z+dist;	// 0 right, front, upper
	pnt[1].x = center.x-dist;	pnt[1].y = center.y+dist;	pnt[1].z = center.z+dist;	// 1 left, front, upper
	pnt[2].x = center.x+dist;	pnt[2].y = center.y-dist;	pnt[2].z = center.z+dist;	// 2 right, back, upper
	pnt[3].x = center.x-dist;	pnt[3].y = center.y-dist;	pnt[3].z = center.z+dist;	// 3 left, back, uppper
	pnt[4].x = center.x+dist;	pnt[4].y = center.y+dist;	pnt[4].z = center.z-dist;	// 4 right, front, lower
	pnt[5].x = center.x-dist;	pnt[5].y = center.y+dist;	pnt[5].z = center.z-dist;	// 5 left, front, lower
	pnt[6].x = center.x+dist;	pnt[6].y = center.y-dist;	pnt[6].z = center.z-dist;	// 6 right, back, lower
	pnt[7].x = center.x-dist;	pnt[7].y = center.y-dist;	pnt[7].z = center.z-dist;	// 7 left, bakc, lower


}

void draw_cube_wireframe (vertex pnt[8])
{
	int i;
	
	// upper "lid"
	line_3d ((int)pnt[0].x,(int)pnt[0].y,(int)pnt[0].z,(int)pnt[1].x,(int)pnt[1].y,(int)pnt[1].z);
	line_3d ((int)pnt[2].x,(int)pnt[2].y,(int)pnt[2].z,(int)pnt[3].x,(int)pnt[3].y,(int)pnt[3].z);
	line_3d ((int)pnt[1].x,(int)pnt[1].y,(int)pnt[1].z,(int)pnt[3].x,(int)pnt[3].y,(int)pnt[3].z);
	line_3d ((int)pnt[2].x,(int)pnt[2].y,(int)pnt[2].z,(int)pnt[0].x,(int)pnt[0].y,(int)pnt[0].z);

	// lower "lid"
	line_3d ((int)pnt[4].x,(int)pnt[4].y,(int)pnt[4].z,(int)pnt[5].x,(int)pnt[5].y,(int)pnt[5].z);
	line_3d ((int)pnt[6].x,(int)pnt[6].y,(int)pnt[6].z,(int)pnt[7].x,(int)pnt[7].y,(int)pnt[7].z);
	line_3d ((int)pnt[5].x,(int)pnt[5].y,(int)pnt[5].z,(int)pnt[7].x,(int)pnt[7].y,(int)pnt[7].z);
	line_3d ((int)pnt[6].x,(int)pnt[6].y,(int)pnt[6].z,(int)pnt[4].x,(int)pnt[4].y,(int)pnt[4].z);

	// side walls
	line_3d ((int)pnt[0].x,(int)pnt[0].y,(int)pnt[0].z,(int)pnt[4].x,(int)pnt[4].y,(int)pnt[4].z);
	line_3d ((int)pnt[1].x,(int)pnt[1].y,(int)pnt[1].z,(int)pnt[5].x,(int)pnt[5].y,(int)pnt[5].z);
	line_3d ((int)pnt[2].x,(int)pnt[2].y,(int)pnt[2].z,(int)pnt[6].x,(int)pnt[6].y,(int)pnt[6].z);
	line_3d ((int)pnt[3].x,(int)pnt[3].y,(int)pnt[3].z,(int)pnt[7].x,(int)pnt[7].y,(int)pnt[7].z);

}

/*
void calculate_tetrahedron_corners (vertex *pnt, int *cnt, vertex center, float radius)
{
	int start = ++cnt;

	float pi = 3.141592653589793238462643383279502884197;
	float phiaa = -19.471220333;

	float phia = pi*phiaa/180.0;
	float the120 = pi*120.0/180.0;

	pnt[cnt].x = 0;
	pnt[cnt].y = 0;
	pnt[cnt++].z = r;

	float the = 0;
	int i;
	for (i=0; i<3; i++)
	{
		pnt[cnt].x = r*cos(the)*cos(phia);
		pnt[cnt].y = r*sin(the)*cos(phia);
		pnt[cnt].z = r*sin(phia);
		the += the120;

		if (i<2)
			cnt++;
	}

	

}
*/


