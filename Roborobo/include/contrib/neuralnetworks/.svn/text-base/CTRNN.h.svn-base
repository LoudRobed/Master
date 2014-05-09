/**
 * @file
 * @author Jean-Marc Montanier <montanier.jeanmarc@gmail.com>
 *
 *
 */

#ifndef CTRNN_H
#define CTRNN_H 

#include <neuralnetworks/RecurrentNeuralNetwork.h>


namespace Neural {

	/**
	 * A support for CTRNN neural networks
	 * @author Jean-Marc Montanier <montanier.jeanmarc@gmail.com>
	 */
	class CTRNN : public RecurrentNeuralNetwork {

		protected:
					
			double _stepSize;
			unsigned int _nbStep;

			boost::numeric::ublas::vector<double> _biases;
			boost::numeric::ublas::vector<double> _gains;
			boost::numeric::ublas::vector<double> _taus;
			boost::numeric::ublas::vector<double> _Rtaus;


			double sigmoid(double x);
			double inverseSigmoid(double y);
			void eulerStep();

			/**
			 * {@InheritDoc}
			 */
			virtual unsigned int computeRequiredNumberOfWeights();

		public:

			// -+-+-  Constructors/Destructors  -+-+- //

			CTRNN(unsigned int nbInputs, unsigned int nbOutputs, unsigned int nbHiddenNeurons,
					double stepSize,
					unsigned int nbStep,
					boost::numeric::ublas::matrix<double> matrixWeights, 
					boost::numeric::ublas::matrix<double> matrixWeightsInputs,
					boost::numeric::ublas::vector<double> biases,
					boost::numeric::ublas::vector<double> gains,
					boost::numeric::ublas::vector<double> taus,
					boost::numeric::ublas::vector<double> Rtaus
					);

			CTRNN(unsigned int nbInputs, unsigned int nbOutputs, unsigned int nbHiddenNeurons,
					double stepSize,
					unsigned int nbStep,
					boost::numeric::ublas::matrix<double> matrixWeights, 
					boost::numeric::ublas::matrix<double> matrixWeightsInputs
					);

			CTRNN(unsigned int nbInputs, unsigned int nbOutputs, unsigned int nbHiddenNeurons,
					double _stepSize,
					unsigned int _nbStep
					);


			/** Deep Copy constructor */
			CTRNN(CTRNN const& other);

			virtual ~CTRNN();


			// -+-+-  Accessors/Mutators  -+-+- //
			void setNeuronBias(unsigned int neuron, double value);
			double getNeuronBias(unsigned int neuron);

			void setNeuronGain(unsigned int neuron, double value);
			double getNeuronGain(unsigned int neuron);

			void setNeuronTimeConstant(unsigned int neuron, double value);
			double getNeuronTimeConstant(unsigned int neuron);

			void setStepSize(double stepSize);
			double getStepSize();

			void setNbStep(unsigned int nbStep);
			double getNbStep();

			void setNeuronOutput(unsigned int neuron, double value);

			void setNeuronParameters(std::vector<double> parameters);


			// -+-+-  Main Methods  -+-+- //

			/**
			 * {@InheritDoc}
			 */
			virtual CTRNN* clone() const;

			/**
			 * {@InheritDoc}
			 */
			virtual std::string toString() const;

			/**
			 * {@InheritDoc}
			 */
			virtual void step();

			/**
			 * Return a string identifying this class
			 */
			static std::string getNNTypeName();

			/**
			 * Return the number of parameter needed for the setParameter function
			 */
			int getNbParameters();

			/**
			 * set all the parameters of all the neurons from a vector
			 * n being the number of neurons
			 * m being the number of inputs
			 * w the matrix of weights between neurons
			 * wi the matrix of wieghts between input and neurons
			 * w_01, .. ,  w_0n, w_n0 , .., w_nn, 
			 * wi_01, ... wi_0n, wi_m0, ... ,wi_mn,
			 * Bias_0, ... , Bias_n,
			 * gain_0,  ... , gain_n 
			 * tau_0,  ... , tau_n
			 */
			 void setParameters(std::vector<double> parameters);

	};

}


#endif

