
cube: main.c cube.c draw.c effect.c font.c 3d.c draw_3d.c gameoflife.c udp.c
	gcc -lpthread -lm -o cube main.c cube.c draw.c effect.c font.c 3d.c draw_3d.c gameoflife.c udp.c

clean:
	rm  cube
