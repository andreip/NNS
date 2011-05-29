#include <stdlib.h>
#include <math.h>
#include "kdtree.h"

#define DIST_POINT(x,y,a,b)	sqrt ((x-a)*(x-a) + (y-b)*(y-b))
#define DIST_AXIS(x,y,a,b,axis)	( (axis) ? (fabs(y-b)) : (fabs(x-a)) )

KD KDCreate(double x, double y) {
	KD new = calloc (1, sizeof(struct kdtree));
	new->x = x;
	new->y = y;

	return new;
}

void KDDestroy(KD kd) {
	if (kd == NULL)
		return;
	if (kd->left)
		KDDestroy(kd->left);
	if (kd->right)
		KDDestroy(kd->right);
	free(kd);
}

void KDInsert(KD kd, double x, double y) {
	KD new, iter = kd, iter2;
	int depth = 0, axis;

	new = KDCreate(x, y);
	if (kd == NULL) {
		kd = new;
		return;
	}

	/* itereaza pana intr-o frunza */
	while (iter) {
		iter2 = iter;
		axis = depth % 2;

		if (axis == 0) {
			// x axis
			if (x < iter->x)
				iter = iter->left;
			else
				iter = iter->right;
		} else {
			// y axis
			if (y < iter->y)
				iter = iter->left;
			else
				iter = iter->right;
		}
		depth++;
	}

	/* insereaza nodul in pozitia corespunzatoare */
	if (axis == 0) {
		if (x < iter2->x)
			iter2->left = new;
		else
			iter2->right = new;
	} else {
		if (y < iter2->y)
			iter2->left = new;
		else
			iter2->right = new;
	}
}

int ChildNear(KD kd, double x, double y, int axis) {
	if (axis == 0)
		return x < kd->x;
	return y < kd->y;
}

KD KDSearchNN(KD kd, double x, double y, KD best, int depth) {
	int axis;
	KD child;

	if (kd == NULL)
		return best;
	
	if (best == NULL)
		best = kd;
	
	axis = depth % 2;
	if ( DIST_POINT(x,y,kd->x,kd->y) < DIST_POINT(x,y,best->x,best->y) )
		best = kd;

	/* cauta in ramura cea mai apropiata */
	if (ChildNear(kd, x, y, axis))
		child = kd->left;
	else
		child = kd->right;
	best = KDSearchNN(child, x, y, best, depth+1);

	/* cauta si in ramura cealalata, daca cercul de raza
	distanta(best,punct_dat) intersecteaza axa curenta */
	if ( DIST_AXIS(x,y,kd->x,kd->y,axis) < DIST_POINT(x,y,best->x,best->y) ) {
		if (ChildNear(kd, x, y, axis))
			child = kd->right;
		else
			child = kd->left;
		best = KDSearchNN(child, x, y, best, depth+1);
	}
	return best;
}
