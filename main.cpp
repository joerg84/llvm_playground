//#include "llvm/IR/Module.h"
//#include "llvm/IR/Function.h"
//#include "llvm/IR/PassManager.h"
//#include "llvm/IR/CallingConv.h"
//#include "llvm/IR/IRBuilder.h"
//#include "llvm/Support/raw_ostream.h"
//#include "llvm/IR/LLVMContext.h"
//#include "llvm/IR/IRPrintingPasses.h"
//
//using namespace llvm;
//
//
//
//Module* makeLLVMModule();
//
//
////int main()
////{
////    llvm::LLVMContext& context = llvm::;
////    llvm::Module* module = new llvm::Module("top", context);
////    llvm::IRBuilder<> builder(context);
////
////    module->dump( );
////}
//
//int main(int argc, char**argv) {
//    Module* Mod = makeLLVMModule();
//
//    // verifyModule(*Mod, PrintMessageAction);
//
//    PassManager PM;
//    PM.add(createPrintModulePass(&outs()));
//    PM.run(*Mod);
//
//    delete Mod;
//    return 0;
//}

#include <cstdio>
#include <fstream>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Function.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/GlobalAlias.h"


using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);

std::unique_ptr<Module> buildModule()
{
    std::unique_ptr<Module> module = llvm::make_unique<Module>("top", TheContext);


    /* Create main function */
    //FunctionType *funcType = FunctionType::get(Builder.getInt32Ty(), false);
    FunctionType *funcType = FunctionType::get(Builder.getVoidTy(), false);
    Function *mainFunc = Function::Create(funcType, Function::ExternalLinkage, "main", module.get());

    /* Create Basic */
    BasicBlock *entry = BasicBlock::Create(TheContext, "entrypoint", mainFunc);
    Builder.SetInsertPoint(entry);

    /* Hello World String constant */
    Value *helloWorldStr = Builder.CreateGlobalStringPtr("hello world!\n");

    /* Create "puts" function */
    std::vector<Type *> putsArgs;
    putsArgs.push_back(Builder.getInt8Ty()->getPointerTo());
    ArrayRef<Type*> argsRef(putsArgs);
    FunctionType *putsType = FunctionType::get(Builder.getInt32Ty(), argsRef, false);
    //Constant *putsFunc = module->getOrInsertFunction("puts", putsType);
    Function *putsFunc = Function::Create(putsType, Function::ExternalLinkage, "puts", module.get());

////      cast<Function>(module->getOrInsertFunction("puts", putsType));
    /* Invoke it */
    Builder.CreateCall(putsFunc, helloWorldStr);

    /* Return zero */
    Builder.CreateRetVoid();
    // Call matching the int main() signature
    //Builder.CreateRet(ConstantInt::get(TheContext, APInt(32, 0)));

    return module;
}

void writeModuleToFile(Module *module)
{
    std::ofstream std_file_stream("program.ll");
    raw_os_ostream file_stream(std_file_stream);
    module->print(file_stream, nullptr);
}

int main()
{
    std::unique_ptr<Module> module = buildModule();
//module->dump();
    writeModuleToFile(module.get());
    return 0;
}