/*!***************************************//**
 * \file 
 * \brief global includes and defines
 ********************************************/

/********************************************
 * Global include                         
 ********************************************/
#ifndef _GLOBALS
#define _GLOBALS
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

/********************************************/
/* Global constants                         */
/********************************************/
/* Deprecated */
/* #define NB_ANT 1000 */
/* #define TOTAL_RUNTIME 15000 */

/*! \def DEBUG_LEVEL
 * Various debug information 
 * there is 3 level of debugging : each one enable 
 * a more verbose output 
 */
#define DEBUG_LEVEL 0

/*! \def TIMESTEP
 * The current value of dt.
 */
#define TIMESTEP 0.1

/*! \def AMD64 \def X86
 * architecture type for affinity propagtion binary library.
 */
#define AMD64
#ifndef AMD64
  #define X86
#endif
/********************************************
 * \b Operating \b modes                          
 ********************************************/

/*! \def RANDOM_INITIAL_CONDITIONS
 * if define, rand seed is initialized with time.
 * Otherwise, seed must be given in parameter
 */
/* #define RANDOM_INITIAL_CONDITIONS */

/*! \def RANDOM_CONNECTIVITY
 * Connectivity is drawn from a rng with variable seed.
 * If not defined, seed is always 0.
 */
/* #define RANDOM_CONNECTIVITY */

/*! \def FIXEDCONNECTION
 * Use a fixed number of connection for each ant
 * rather than a connection percentage probability
 */
/* #define FIXEDCONNECTION */

/*! \def VARIABLE_WORKTIME
 * Worktime is defined in param_ant + exponential law
 */
/* #define VARIABLE_WORKTIME */

/*! \def AUTOCATALYSIS
 * If defined workers incite observers to get working.
 * Otherwise, it is as in NIPS paper
 */
/* #define AUTOCATALYSIS */

/*! \def PTRACE 
 * PTRACE allows to record all membrane 
 * potential values for lif and qif neurons 
 * Saved in pot_lifX.txt and pot_qifX.txt 
 * with X the ant identifier 
 */
/* #define PTRACE */

/*! \def ATRACE
 * ATRACE allows to record global ant status 
 * that is number of ants in each class 
 * for each time step and saves additionnal 
 * information about the number of each status
 * taken during a run, the mean observation time
 * and the number of spike processed. 
 * Saved in \c nest_stat.txt and \c nest_addstat.txt 
 */
#define ATRACE

/*! \def STRACE
 * Record ant status for each ant, with the timing of status change
 * Saved in ant_stat_global.dat and ant_morestat_global.dat
 */
#define STRACE

/*! \def SP_THRES
 * Save proba_spike.dat, where each decision (going to groom [1] 
 * or not [0]) is associated with the number of spike received.
 */
#ifdef STRACE
/*  #define SP_THRES */
#endif

/*! \def W_THRES
 * Measure the mean number of workers influencing the decision of a
 * given observer on the whole population and the whole simulation
 */
#ifdef STRACE
  #define W_THRES
#endif

/*! \def SPIKZ
 * Record only the total number of fired spike in the
 * whole population.
 */
/* #define SPIKZ */

/*! \def RTRACE
 * Record spike raster data, saved in raster-{active,passive}.dat
 */
/* #define RTRACE */

/*! \def SPIKE_METRIC_CLUSTERS
 * Determine an similarity measure based on activity
 * using a spike metric of Victor & Purpura, Dspike.
 * Save a network file, netnest_spikemetric.gexf
 */
#ifdef RTRACE
  #define SPIKE_METRIC_CLUSTERS
  #ifdef SPIKE_METRIC_CLUSTERS
    #define SHIFT_COST 1

/*! \def SMDIST
 * Record spike metric distribution in metricspike-distribution.dat
 */
    #define SMDIST
    #ifdef SMDIST
      #define SMDSIZE 20
    #endif
  #endif
#endif

/*! \def STDP_MODE
 * activate STDP: connection weight between any 2 neurons varies
 * depending on the causal impact of each fired spike.
 */
/* #define STDP_MODE */

/*! \def WTRACE
 * Record evolution of synaptic weight with STDP.
 * Saved in stdp-weight-{active,passive}.dat
 * With WTRACE_PERIODIC, all weight are saved every WTRACE_PERIOD timesteps.
 * With WTRACE_ONCHANGE, each weight is saved at each change (big file)
 */
#ifdef STDP_MODE
/* #define WTRACE */

  #ifdef WTRACE
    #define WTRACE_PERIODIC
    #ifdef WTRACE_PERIODIC
      #define WTRACE_PERIOD 10000
    #endif

    #ifndef WTRACE_PERIODIC
      #define WTRACE_ONCHANGE
    #endif
  #endif

  /*! \def WDTRACE
   * Record weight distribution in weight-{init,final}-{active,passive}.dat
   */
  /* #define WDTRACE */
  #ifdef WDTRACE
    #define WDSIZE 20
  #endif
#endif

/*! \def NTRACE
 * Save network structure in pajeck or GEXF style both at
 * the begining and the end of the run. Files are named
 * netnest-{init,final}-{active,passive}.{net,gexf}
 */
/* #define NTRACE */

/*! \def GEXF_EXPORT
 * Save network file with gexf xml syntax. Otherwise, use pajek net file
 */
#ifdef NTRACE
 #define GEXF_EXPORT
#endif

/********************************************
 * Post population analysis mode
 ********************************************/
/*! \def AUTOCORRELATION
 * If defined, computed the autocorrelations rk
 * to produce a lag/autocorellation plot (a correlogram)
 * \b WARNING: \b time consuming computations!
 */
/* #define AUTOCORRELATION */

/*! \def LAGPLOT
 * Save lagplot.dat, a lag-1 plot of the working ants
 * and compute the mean packet size, sum of intraclass variance, etc
 * saved in workpacket.dat
 */
#define LAGPLOT

#ifdef LAGPLOT
/*! \def PHASESPACE
 * save lagplot-preproc.dat and phasespace.dat to plot 
 * the phase space without transitive state between plateau
 */
/*  #define PHASESPACE */

/*! \def ENTROPY
 * Use epsilon clustering to cluster all work(t) and compute 
 * associated entropy (printed on stderr)
 */
 #define ENTROPY
#endif

/*! \def EPSILONCLUSTERING
 * use epsilon clustering to measure emergence
 */
/* #define EPSILONCLUSTERING */

/*! \def AFFINITYPROPAGATION
 * use affinity propagation to measure emergence
 */
/* #define AFFINITYPROPAGATION */

/*! \def FFTANALYSIS
 * COmpute a fft analysis of the signal and the autocorrelagram
 * if defined.
 */
/* #define FFTANALYSIS */

/********************************************
 * Efficiency mode
 ********************************************/
/*! \def QDEP
 * If define, the Qrapp is calculated as
 * the product of percentage of working ant, 
 * a constant delta and Qdispo.
 * Otherwise it is the product of the number
 * of working ant and delta times Qdispo, delta
 * being a fraction of the available food picked
 * up by a working ant. To avoid Qdispo being negative
 * Qrapp is computed as MIN (w*delta*Qdispo, Qdispo) 
 */
#define QDEP

/*! \def ALTEFF
 * Alternative method to compute Qdispo:
 * \f[ \dot{Q_{dispo}} = - \lambda (Q_{dispo}(t) - Q_{new}) - Q_{rapp} \f]
 * And efficincy is Eff = Qrapp/Qconso
 * On the right way but it does not work. I must change  Qrapp formula:
 * Small Qdispo increase, need time to restore
 * High Qrapp for small numbers of workers, decreases to a saturation when
 * to many workers at the same time.
 * I can set Qo (observe) to a lower value
 */
#define ALTEFF

#ifdef __cplusplus
}
#endif
#endif
