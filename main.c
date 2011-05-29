/*
 * Cerinta: Se dau N puncte pe harta, prin coordonate. Apoi se dau alte M
 * puncte si pentru fiecare dintre ele, se cere cel mai apropiat dintre cele
 * N puncte de pe harta. Complexitate mai mica de O(M*N).
 */

#include <stdio.h>
#include <stdlib.h>
#include "kdtree.h"

void InitFiles(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage <exec> <file_in> <file_out>\n");
		exit(1);
	}
	if ( !freopen(argv[1], "r", stdin) ) {
		fprintf(stderr, "Fisierul %s nu s-a putut deschide\n", argv[1]);
		exit(1);
	}
	freopen(argv[2], "w", stdout);
}

int main(int argc, char *argv[]) {
	int i, N, M;
	double coordX, coordY;
	KD kd, out;

	InitFiles(argc, argv);

	/* formare arbore pentru orase */
	scanf("%d", &N);
	scanf("%lf%lf", &coordX, &coordY);
	kd = KDCreate(coordX, coordY);

	for(i=1; i<N; i++) {
		scanf("%lf%lf", &coordX, &coordY);
		KDInsert(kd, coordX, coordY);
	}

	/* raspundere request-uri */
	scanf("%d", &M);
	for(i=0; i<M; i++) {
		scanf("%lf%lf", &coordX, &coordY);
		out = KDSearchNN(kd, coordX, coordY, NULL, 0);
		printf("%lf %lf\n", out->x, out->y);
	}
	KDDestroy(kd);
	return 0;
}
