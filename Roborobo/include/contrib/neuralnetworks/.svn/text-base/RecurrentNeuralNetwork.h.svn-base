/**
 * @file
 * @author Jean-Marc Montanier <montanier.jeanmarc@gmail.com>
 *
 *
 */

#ifndef RECURRENTNEURALNETWORK_H
#define RECURRENTNEURALNETWORK_H

#include <neuralnetworks/NeuralNetwork.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>


namespace Neural {

	/**
	 * Definition of a reservoir neural network
	 * @author Leo Cazenille <leo.cazenille@gmail.com>
	 */
	class RecurrentNeuralNetwork : public NeuralNetwork {

		protected:
		  /** State of the neural network **/
			boost::numeric::ublas::vector<double> _states;
			boost::numeric::ublas::vector<double> _outputs;
			boost::numeric::ublas::vector<double> _externalInputs;

			/** Weights of the neural network **/
			boost::numeric::ublas::matrix<double> _matrixWeights;
			boost::numeric::ublas::matrix<double> _matrixWeightsInputs;

			/** Size of the reservoir, ie of neurons in the reservoir */
			unsigned int _nbHiddenNeurons;
			unsigned int _size;

		public :

			// -+-+-  Constructors/Destructors  -+-+- //

			virtual ~RecurrentNeuralNetwork();

			RecurrentNeuralNetwork(unsigned int nbInputs, unsigned int nbOutputs, unsigned int nbHiddenNeurons);

			RecurrentNeuralNetwork(unsigned int nbInputs, unsigned int nbOutputs, unsigned int nbHiddenNeurons,
					boost::numeric::ublas::matrix<double> matrixWeights, 
					boost::numeric::ublas::matrix<double> matrixWeightsInputs
					);


			/** Deep Copy constructor */
			RecurrentNeuralNetwork(RecurrentNeuralNetwork const& other);


			// -+-+-  Accessors/Mutators  -+-+- //
			virtual void setConnectionWeight(unsigned int from, unsigned int to, double weight);
			virtual double getConnectionWeight(unsigned int from, unsigned int to);

			virtual void setConnectionWeightInput(unsigned int from, unsigned int to, double weight);
			virtual double getConnectionWeightInput(unsigned int from, unsigned int to);

			virtual void setNeuronExternalInput(unsigned int neuron, double value);
			virtual double getNeuronExternalInput(unsigned int neuron);

			virtual void setNeuronState(unsigned int neuron, double value);
			virtual double getNeuronState(unsigned int neuron);

			virtual double getNeuronOutput(unsigned int neuron);



			// -+-+-  Main Methods  -+-+- //

			/**
			 * {@InheritDoc}
			 */
			virtual RecurrentNeuralNetwork* clone() const = 0;

			/**
			 * {@InheritDoc}
			 */
			virtual std::string toString() const;


	};


}

#endif

