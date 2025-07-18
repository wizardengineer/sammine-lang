//
// Created by Jasmine Tang on 3/27/24.
//

#pragma once
#include "TypeConverter.h"
#include "ast/Ast.h"
#include "codegen/LLVMRes.h"
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
namespace sammine_lang::AST {
class CgVisitor : public ScopedASTVisitor {

private:
  std::shared_ptr<sammine_lang::LLVMRes> resPtr;
  std::stack<std::map<std::string, llvm::AllocaInst *>> allocaValues;

  llvm::Function *current_func;
  llvm::Function *getCurrentFunction();
  void setCurrentFunction(std::shared_ptr<PrototypeAST>);

  TypeConverter type_converter;

public:
  CgVisitor(std::shared_ptr<sammine_lang::LLVMRes> resPtr)
      : resPtr(resPtr), type_converter(resPtr->Context.get()) {
    assert(this->resPtr);
  }
  llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction,
                                           const std::string &VarName,
                                           llvm::Type *);

  void enter_new_scope() override;
  void exit_new_scope() override;

  virtual void visit(FuncDefAST *) override;
  virtual void visit(IfExprAST *ast) override {
    ast->walk_with_preorder(this);
    ast->walk_with_postorder(this);
  }
  // visit
  // pre order
  // TODO: Implement these
  virtual void preorder_walk(ProgramAST *ast) override;
  virtual void preorder_walk(VarDefAST *ast) override;
  virtual void preorder_walk(FuncDefAST *ast) override;
  virtual void preorder_walk(RecordDefAST *ast) override;
  virtual void preorder_walk(ExternAST *ast) override {}
  virtual void preorder_walk(PrototypeAST *ast) override;
  virtual void preorder_walk(CallExprAST *ast) override;
  virtual void preorder_walk(ReturnExprAST *ast) override {}
  virtual void preorder_walk(BinaryExprAST *ast) override;
  virtual void preorder_walk(NumberExprAST *ast) override;
  virtual void preorder_walk(StringExprAST *ast) override;
  virtual void preorder_walk(BoolExprAST *ast) override;
  virtual void preorder_walk(VariableExprAST *ast) override;
  virtual void preorder_walk(BlockAST *ast) override;
  virtual void preorder_walk(IfExprAST *ast) override;
  virtual void preorder_walk(TypedVarAST *ast) override;

  // post order
  // TODO: Implement these?
  virtual void postorder_walk(ProgramAST *ast) override {}
  virtual void postorder_walk(VarDefAST *ast) override;
  virtual void postorder_walk(ExternAST *ast) override {}
  virtual void postorder_walk(FuncDefAST *ast) override;
  virtual void postorder_walk(RecordDefAST *ast) override;
  virtual void postorder_walk(PrototypeAST *ast) override {}
  virtual void postorder_walk(CallExprAST *ast) override {}
  virtual void postorder_walk(ReturnExprAST *ast) override;
  virtual void postorder_walk(BinaryExprAST *ast) override;
  virtual void postorder_walk(NumberExprAST *ast) override {}
  virtual void postorder_walk(StringExprAST *ast) override {}
  virtual void postorder_walk(BoolExprAST *ast) override {}
  virtual void postorder_walk(VariableExprAST *ast) override {}
  virtual void postorder_walk(BlockAST *ast) override;
  virtual void postorder_walk(IfExprAST *ast) override {}
  virtual void postorder_walk(TypedVarAST *ast) override {}
};
} // namespace sammine_lang::AST
