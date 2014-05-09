/* gcc -Wall -pedantic -ansi -march=native -O2 -pipe -fomit-frame-pointer -finline-functions -finline-functions-called-once -fno-strict-aliasing -lm -lnetpbm -o constructActivityMap constructActivityMap.c */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main (int argc, char* argv[]) {

  int** activityMapObs, **activityMapFor, **activityMapSleep, **activityMapGroom;
  int width, height, iter, tmp;
  int i, j=0, id, it, status, maxFor=0, maxObs=0, maxSleep=0, maxGroom=0, maxG=0;
  double x, y;
  const int depth = 255;
  FILE* fin, *fout;

  if (argc != 4) {
	 fprintf (stderr, "usage: %s width height lines\n", argv[0]);
	 exit (1);
  }
  width = atoi (argv[1]);
  height = atoi (argv[2]);
  iter = atoi (argv[3]);

  if (((activityMapObs = (int**) calloc (width, sizeof(int*))) == NULL) ||
  		((activityMapFor = (int**) calloc (width, sizeof(int*))) == NULL) ||
  		((activityMapSleep = (int**) calloc (width, sizeof(int*)))== NULL) ||
  		((activityMapGroom = (int**) calloc (width, sizeof(int*)))== NULL)) {
  	 fprintf (stderr, "error calloc\n");
  	 exit (1);
  }
  for (i = 0; i < width; i++) {
  	 if (((activityMapObs[i]=(int*)calloc (height, sizeof(int))) == NULL) ||
  		  ((activityMapFor[i]=(int*)calloc (height, sizeof(int))) == NULL) ||
  		  ((activityMapSleep[i]=(int*)calloc(height, sizeof(int)))== NULL) ||
  		  ((activityMapGroom[i]=(int*)calloc(height, sizeof(int)))== NULL)) {
  		fprintf (stderr, "error calloc\n");
  		exit (1);
  	 }
  }
  
  for (i=0; i<width; i++) {
	 for (j=0; j<height; j++) {
		activityMapFor[i][j]=0;
		activityMapSleep[i][j]=0;
		activityMapGroom[i][j]=0;
		activityMapObs[i][j]=0;
	 }
  }
  if ((fin = fopen ("ants_stat.txt", "r")) == NULL) {
	 fprintf (stderr, "error opening file ants_stat.txt\n");
	 exit (0);
  }
  for (i=0; i<iter; i++) {
	 tmp = fscanf (fin, "%d %d %d %lf %lf ", &id, &it, &status, &x, &y);
	 switch (status) {
	 case 0: activityMapFor[(int)floor (x)][(int)floor (y)]++; break;
	 case 1: activityMapSleep[(int)floor (x)][(int)floor (y)]++; break;
	 case 2: activityMapGroom[(int)floor (x)][(int)floor (y)]++; break;
	 case 3: activityMapObs[(int)floor (x)][(int)floor (y)]++; break;
	 }
  }
  fclose (fin);
  
  for (i=0; i<width; i++) {
	 for (j=0; j<height; j++) {
		if (activityMapFor[i][j] > maxFor) maxFor = activityMapFor[i][j];
		if (activityMapSleep[i][j] > maxSleep) maxSleep = activityMapSleep[i][j];
		if (activityMapGroom[i][j] > maxGroom) maxGroom = activityMapGroom[i][j];
		if (activityMapObs[i][j] > maxObs) maxObs = activityMapObs[i][j];
		if (activityMapFor[i][j]+activityMapSleep[i][j]+activityMapGroom[i][j]+activityMapObs[i][j] > maxG) maxG = activityMapFor[i][j]+activityMapSleep[i][j]+activityMapGroom[i][j]+activityMapObs[i][j];
	 }
  }
  
  printf ("maxF = %d; maxO = %d; maxS = %d; maxG = %d max = %d\n", maxFor, maxObs, maxSleep, maxGroom, maxG);

  
  if ((fout = fopen ("activityMapFor.pgm", "w")) == NULL) {
	 fprintf (stderr, "error opening file activityMapFor.pgm\n");
	 exit (0);
  }

  fprintf (fout, "P2\n%d\n%d\n%d\n", width, height, depth);
  for (j=0; j<height; j++) {
  	 for (i=0; i<width; i++) {
		if (activityMapFor[i][j] == 0) fprintf (fout, "%d ", depth);
		else
		  fprintf (fout, "%d ", depth - (int)((double)activityMapFor[i][j]/((double)maxFor)*255.0));
  	 }
  	 fprintf (fout, "\n");
  }
  fclose (fout);

  if ((fout = fopen ("activityMapObs.pgm", "w")) == NULL) {
  	 fprintf (stderr, "error opening file activityMapObs.pgm\n");
  	 exit (0);
  }
  fprintf (fout, "P2 %d %d %d\n", width, height, depth);
  for (j=0; j<height; j++) {
  	 for (i=0; i<width; i++) {
		if (activityMapObs[i][j] == 0) fprintf (fout, "%d ", depth);
		else
		  fprintf (fout, "%d ", depth - (int)((double)activityMapObs[i][j]/((double)maxObs)*255.0));
  	 }
  	 fprintf (fout, "\n");
  }
  fclose (fout);

  if ((fout = fopen ("activityMapSleep.pgm", "w")) == NULL) {
  	 fprintf (stderr, "error opening file activityMapSleep.pgm\n");
  	 exit (0);
  }
  fprintf (fout, "P2 %d %d %d\n", width, height, depth);
  for (j=0; j<height; j++) {
  	 for (i=0; i<width; i++) {
		if (activityMapSleep[i][j] == 0) fprintf (fout, "%d ", depth);
		else
		  fprintf (fout, "%d ", depth - (int)((double)activityMapSleep[i][j]/((double)maxSleep)*255.0));
  	 }
  	 fprintf (fout, "\n");
  }
  fclose (fout);

  if ((fout = fopen ("activityMapGroom.pgm", "w")) == NULL) {
  	 fprintf (stderr, "error opening file activityMapGroom.pgm\n");
  	 exit (0);
  }
  fprintf (fout, "P2 %d %d %d\n", width, height, depth);
  for (j=0; j<height; j++) {
  	 for (i=0; i<width; i++) {
		if (activityMapGroom[i][j] == 0) fprintf (fout, "%d ", depth);
		else
		  fprintf (fout, "%d ", depth - (int)((double)activityMapGroom[i][j]/((double)maxGroom)*255.0));
  	 }
  	 fprintf (fout, "\n");
  }
  fclose (fout);

  if ((fout = fopen ("activityMapGlob.pgm", "w")) == NULL) {
  	 fprintf (stderr, "error opening file activityMapGlob.pgm\n");
  	 exit (0);
  }
  fprintf (fout, "P2 %d %d %d\n", width, height, depth);
  for (j=0; j<height; j++) {
  	 for (i=0; i<width; i++) {
		if (activityMapGroom[i][j]+activityMapSleep[i][j]+activityMapObs[i][j]+activityMapFor[i][j] == 0) fprintf (fout, "%d ", depth);
		else
		  fprintf (fout, "%d ", depth - (int)((double)(activityMapGroom[i][j]+activityMapSleep[i][j]+activityMapObs[i][j]+activityMapFor[i][j])/((double)maxG)*255.0));
  	 }
  	 fprintf (fout, "\n");
  }
  fclose (fout);

  return 0;
}
