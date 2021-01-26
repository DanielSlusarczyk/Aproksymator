#include "points.h"
#include <stdlib.h>

#define MEMORY_BLOCK 20
double*
realloc_pts_failed (points_t * pts, int size)
{
  pts->x=realloc (pts->x, size * sizeof *pts->x);
  pts->y=realloc (pts->y, size * sizeof *pts->y);
  if(pts->x==NULL||pts->y==NULL)
	  return NULL;
  return pts->x;
}

int
read_pts_failed (FILE * inf, points_t * pts)
{
  int size;
  double x, y;

  if (pts->n == 0) {
    pts->x = malloc (MEMORY_BLOCK * sizeof *pts->x);
    if (pts->x == NULL)
      return 1;
    pts->y = malloc (MEMORY_BLOCK * sizeof *pts->y);
    if (pts->y == NULL) {
      free (pts->x);
      return 1;
    }
    size = MEMORY_BLOCK;
  }
  else
    size = pts->n;

  while (fscanf (inf, "%lf %lf", &x, &y) == 2) {
    pts->x[pts->n] = x;
    pts->y[pts->n] = y;
    pts->n++;
    if (!feof (inf) && pts->n == size) {
      if (realloc_pts_failed (pts, size+MEMORY_BLOCK)==NULL)
        return 1;
      else
        size +=MEMORY_BLOCK;
    }
  }

  if (pts->n != size)
    if (realloc_pts_failed (pts, pts->n)==NULL)
      return 1;

  return 0;
}
