#ifndef _kdtree_h_
#define _kdtree_h_

typedef struct kdtree {
	struct kdtree *left, *right;
	double x, y;
} *KD;

KD KDCreate(double x, double y);
void KDDestroy(KD kd);
void KDInsert(KD kd, double x, double y);
KD KDSearchNN(KD kd, double x, double y, KD best, int depth);

#endif
