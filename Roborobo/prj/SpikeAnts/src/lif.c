#ifdef __cplusplus
extern "C" {
#endif

#include "SpikeAnts/include/lif.h"

void init_lif (lif* n, double pot, double tau, double rest, double thres, 
					double reset, double dt, long total_runtime) {

  n->pot = pot;
  n->tau = tau;
  n->rest = rest;
  n->thres = thres;
  n->reset = reset;
  n->dt = dt;
#ifdef PTRACE
  if ((n->potlog = calloc (total_runtime + (long)2, sizeof (float))) == NULL) {
	 printf ("erreur malloc\n");
	 exit (1);
  }
  n->curlog = 0;
#endif
}

/*! TODO
 * regarder si synchro est un byproduct du sous echantillonage a 0.1
 * pour connaitre le moyen nombre de spike synchro a 1 pdt:
 * `wc -l pot_lif.txt` - `cut -d " " -f 1 | uniq | wc -l` / total_time
 */
void add_input_lif (lif* n, double w) {
  n->pot += w;
}

int update_lif (lif* n, double t) {
  const double decay = n->tau * n->dt;
  #ifdef PTRACE
  const float peak = 1.5;
  #endif

  n->pot = n->pot * exp(decay);

  if (n->pot > n->thres) {
  #ifdef PTRACE
	 n->potlog[n->curlog] = peak;
	 n->curlog++;
  #endif
	 n->pot = n->reset;
	 return 1;
  }
  else {
  #ifdef PTRACE
    #if DEBUG_LEVEL >= 2
	 if (abs(t - (double)(n->curlog+1)/10.0) > 0.001) {
		printf ("LIF::potlog[%ld] @ %lf (%lf %lf) = %g <- %g)\n", n->curlog, t, 
				  (double)(n->curlog+1), (double)(n->curlog+1)/10.0,
				  n->potlog[n->curlog], (float)n->pot);
	 }
    #endif
	 n->potlog[n->curlog] = (float)n->pot;
	 n->curlog++;

  #endif
  return 0;
  }
}

#ifdef PTRACE
void destroy_lif (lif* n, char *f_name, long total_runtime) {
  FILE* f_rec;
  long i;
  double t = 0.0;
  float wtmp = -1.0;
  const double dt = n->dt;

  if ((f_rec = fopen (f_name, "w")) == NULL) {
  	 fprintf (stderr, "impossible de creer le fichier %s\n", f_name);
  	 exit (1);
  }
  for (i=0; i<total_runtime; i++) {
	 if (wtmp != n->potlog[i]) {
		wtmp = n->potlog[i];
		fprintf (f_rec, "%g %g\n", t, wtmp);
	 }
	 t += dt;
  }
  fclose (f_rec);
  free (n->potlog);
}
#endif

int patapouet (int a, int b) {
  if (a > b) return a;
  else return b;
}

#ifdef __cplusplus
}
#endif
