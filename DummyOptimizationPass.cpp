//
//  DummyOptimizationPass.cpp
//  
//
//  Created by Jules Testard on 22/05/2014.
//
//
#include "llvm/Pass.h"
#include "Variable.h"
#include "StaticAnalysis.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"
#include <string>
#include <vector>

using namespace llvm;
using namespace std;

/**
 * BUGS FOUND AND FIXED :
 * 	-	Avoid static members for the passes. This generates a linking error when making the shared object.
 * 	-	raw_ostream& object does not like to be fed a std::endl symbol. Prefer to user "\n".
 *
 */
namespace {
  struct DummyOptimizationPass : public FunctionPass {
    static char ID;
    vector<StaticAnalysis *>staticAnalyses;
    DummyOptimizationPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
    	//initialize analysis
    	staticAnalyses.push_back(new StaticAnalysis(F));
    	return false;
    }

    //The dummy optimization does not modify the code, but performs various analyses and outputs their result here
    void print(raw_ostream &OS, const Module*) const {

    	// ========== TESTING ==============
    	//Test that variable class is properly linked (test can be removed later).
    	string example = "example";
    	Variable v(example);
    	OS << "VARIABLE test : ";
    	OS << "I created a new variable with name : " << v.GetName() << "\n";

    	//The pure static analysis. Functional testing
    	OS << "STATIC ANALYSES test : \n";
    	for (unsigned int i = 0 ; i < staticAnalyses.size() ; i++){
        	OS << "Function Name : " << staticAnalyses[i]->getFunctionName() << "\n";
        	OS << "First Instruction Name : " << staticAnalyses[i]->getCFG()->succs[0]->inst->getName().str() << "\n";
        	OS << "Print CFG : " << "\n";

        	//Check graph once. Everything flow should be empty.
        	staticAnalyses[i]->JSONCFG(OS);
        	//Run worklist algorithm
        	staticAnalyses.back()->runWorklist();
        	//Check graph again. Everything flow should say top.
        	staticAnalyses[i]->JSONCFG(OS);
    	}

  	}
  };
}

char DummyOptimizationPass::ID = 0;
static RegisterPass<DummyOptimizationPass> X("dummyOptimization", "Dummy Optimization Pass", false, false);
