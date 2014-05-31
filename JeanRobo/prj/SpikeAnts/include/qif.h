/*! \file 
 *  \brief Quadratic integrate-and-fire neurons (QIF).
 *
 *  Structures and functions to handle Quadratic Integrate-and-Fire neurons 
 *  (QIF). The differential equation is
 *  \f[ \dot{V} = \tau(V - V_{\mathrm{rest}})(V - V_{\mathrm{th}}) + \sum_j w \delta(t - \hat{t}_j) \f]
 *  The update function is optimized for instantaneous synaptic interactions 
 *  and a timestep of 0.1ms: it will work only in this conditions.
 */
#ifndef _GLOBALS_H
#define _GLOBALS_H
#ifdef __cplusplus
extern "C" {
#endif

#include "SpikeAnts/include/globals.h"

/*! The QIF neuron typedef struct
 */
typedef struct qif {
  double pot;   /*!< QIF current potential value */
  double tau;   /*!< QIF leak conductance */
  double rest;  /*!< QIF rest potential */
  double thres; /*!< QIF threshold potential */
  double vth;   /*!< QIF internal threshold potential*/
  double reset; /*!< QIF reset potential */
  double dt;    /*!< QIF timestep */
#ifdef PTRACE
/* char* f_name; */ /*!< QIF membrane potential log file*/
  float* potlog; /*!< QIF membrane potential log table */
  long curlog;   /*!< QIF membrane potential log iterator */
#endif
  /*  int firing; */  /*!< QIF current timestep spiking flag */
} qif;

/*! Initialize function */
void init_qif (qif* n, double pot, double tau, double rest, double dt, 
					double thres, double vth, double reset, long time);

/*! Return the current membrane potential value */
double get_pot_qif (qif* n);

/*! Set the current membrane potential value */
void set_pot_qif (qif* n, double p);

/*! Change internal threshold value */
void change_reset (qif* n, double reset);

/*! Add a PSP input for the current time step */
void add_input (qif* n, double w); 

/*! Send a continuous input current. The resting potential is modified 
 * to \c c 
 */
void add_input_current (qif* n, double c);

/*! For a time step \c t and when all PSP had been added, an optimized 
 *  approximation of the current value of membrane potential is computed.
 *  Work only with a 0.1ms timestep. For a more generic update rule,
 *  see \c update_rk4.
 *  @see add_input()
 *  @see update_rk4()
 */
int update_qif (qif* n, double t);

/*! 
 * Same update function as \c update_qif with a more generic approximation
 * method (4th order Runge-Kutta). Slower than \c update_qif
 * @see update_qif
 */
int update_rk4 (qif* n, double t);

/*! Internal function triggered when a spike is emitted */
void fire_qif (qif* n, double t);

#ifdef PTRACE
/*! Free used memory and save potentials in f_name file */
void destroy_qif (qif* n, char* f_name, long time);
#endif

#ifdef __cplusplus
}
#endif
#endif
