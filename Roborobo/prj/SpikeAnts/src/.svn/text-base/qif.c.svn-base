#ifdef __cplusplus
extern "C" {
#endif

#include "SpikeAnts/include/qif.h"

void init_qif (qif* n, double pot, double tau, double rest, double dt, 
			  double thres, double vth, double reset, long time) {

  n->pot = pot;
  n->tau = tau;
  n->rest = rest;
  n->dt = dt;
  n->thres = thres;
  n->vth = vth;
  n->reset = reset;
#ifdef PTRACE
  n->curlog = 0;
  if ((n->potlog = calloc (time + 1, sizeof (float))) == NULL) {
	 printf ("erreur malloc\n");
	 exit (1);
  }
#endif
}

double get_pot_qif (qif* n) {
  return n->pot;
}

void set_pot_qif (qif* n, double p) {
  n->pot = p;
}

void change_reset (qif* n, double reset) {
  n->reset = reset;
}
void add_input (qif* n, double w) {
  n->pot = n->pot + w;
} 

void add_input_current (qif* n, double c) {
  n->rest = c;
}

int update_qif (qif* n, double t) {
#ifdef PTRACE
  const float peak = 1.5;
#endif
  const double pot = n->pot;

  /* n->pot = pot + n->tau * (pot - n->rest) * (pot - n->vth); */
  /* Comme rest = 0 */
  n->pot = pot + n->tau * pot * (pot - n->vth);
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
		printf ("QIF::potlog[%ld] @ %g = %g <- %g)\n", n->curlog, t, 
				  n->potlog[n->curlog], (float)n->pot);
	 }
  #endif
	 n->potlog[n->curlog] = (float)n->pot;
	 n->curlog++;
#endif
	 return 0;
  }
}

int update_rk4 (qif* n, double t) {
#ifdef PTRACE
  const float peak = 1.5;
#endif
  const double a = (1.0 / 6.0)*n->dt;
  const double tau = n->tau;
  const double dt = n->dt;
  const double pr = n->pot - n->rest;
  const double pv = n->pot - n->vth;
  const double k1 = tau * pr * pv;
  const double k2 = tau * (pr + (.5*dt*k1)) * (pv + (.5*dt*k1)); 
  const double k3 = tau * (pr + (.5*dt*k2)) * (pv + (.5*dt*k2));
  const double k4 = tau * (pr + (dt*k3)) * (pv + (dt*k3));

  n->pot = n->pot + a*(k1+2*k2+2*k3+k4);

  if (n->pot > n->thres) {
#ifdef PTRACE
	 n->potlog[n->curlog++] = peak;
#endif
	 n->pot = n->reset;
	 return 1;
  }
  else {
#ifdef PTRACE
	 n->potlog[n->curlog++] = (float)n->pot;
#endif
	 return 0;
  }
}

#ifdef PTRACE
void destroy_qif (qif* n, char* f_name, long time) {
  FILE* f_rec;
  long i;
  double t = 0.0;
  float wtmp = -1.0;
  const double dt = n->dt;
  
  if ((f_rec = fopen (f_name, "w")) == NULL) {
  	 fprintf (stderr, "impossible de creer le fichier %s\n", f_name);
  	 exit (1);
  }
  for (i=0; i<time; i++) {
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

#ifdef __cplusplus
}
#endif
