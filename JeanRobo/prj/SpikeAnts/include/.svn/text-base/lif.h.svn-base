/*! \file 
 *  \brief Leaky integrate-and-fire neurons 
 *  
 *  Structures and functions for handling leaky integrate-and-fire (LIF) 
 *  neurons. The update fonction is specific of instantaneous synaptic
 *  interaction. The membrane potential differential equation is
 *  \f[ \dot{V} = \tau V + w \sum_j \delta(t - \hat{t}_j) \f]
 */
#ifndef _LIF_H
#define _LIF_H
#ifdef __cplusplus
extern "C" {
#endif
#include "SpikeAnts/include/globals.h"


/*! The LIF neuron typedef struct
 */
typedef struct lif {
  double pot;        /*!< LIF current membrane potential value */
  double tau;        /*!< LIF leak conductance (for 0.1 ms timestep)*/
  double rest;       /*!< LIF rest potential */
  double thres;      /*!< LIF threshold potential */
  double reset;      /*!< LIF reset potential*/
  double dt;         /*!< LIF time interval */
#ifdef PTRACE
  float* potlog;     /*!< LIF membrane potential log table */
  long curlog;      /*!< LIF membrane potential log iterator */
#endif
} lif;

/*!
 * Initialize LIF constants and create a log file for membrane potential values.
 */
void init_lif (lif* n, double pot, double tau, double rest, double thres,
					double reset, double dt, long total_runtime);

void add_input_lif (lif* n, double w);

/*!
 * \brief Update LIF membrane potential
 * Update the LIF membrane potential after the integration of a PSP.
 * PSP are treated as an instantaneous potential rise.
 * @param n the LIF neuron
 * @param t the current simulated time
 * @return true if LIF spiked, else false
 * @see lif
 */
int update_lif (lif* n, double t);

#ifdef PTRACE
/*! 
 * Free memory and write in a file f_name the succesive potential value
 */
void destroy_lif (lif* n, char *f_name, long total_runtime);
#endif

/* testing */
int patapouet (int a, int b);
					  
#ifdef __cplusplus
}
#endif
#endif
