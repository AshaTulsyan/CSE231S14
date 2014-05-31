#include "StaticAnalysis.h"


#ifndef STATIC_ANALYSIS
#define STATIC_ANALYSIS
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "Flow.h"
#include "DomainElement.h"
#include <map>
#include <vector>
#include <cstdlib>
#include <queue>
#include <sstream>
#include <set>

using namespace llvm;
using namespace std;

class ConstProp : public StaticAnalysis
{

public:

	~ConstProp();
	ConstProp();
	ConstProp(int t_base,/*put arguments here*/);

protected:

	/**
		 * This method is called by the run worklist algorithm.
		 * It has the responsability to figure out what kind of instruction is being used and how to generate the output flow from the input flow for
		 * that instruction.
		 * It is expected this function will call other functions created by the subclasses to deal with each type of instruction.
		 *
		 * WARNING : the output might not be empty to begin with. If it is not, then the output must be joined with the result of the processing
		 * of the input.
		 */
	void executeFlowFunction(Flow &in, Instruction &inst, Flow &out);
};


#endif
