#include <iostream>


#define __STDC_FORMAT_MACROS
#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#if defined _MSC_VER
#pragma warning( push )
#pragma warning(disable : 4244 4267 4146 4141 4291)
#endif

#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecordLayout.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Basic/Version.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Lex/Lexer.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <llvm/Support/raw_ostream.h>

#if defined _MSC_VER
#pragma warning( pop ) 
#endif


class FindNamedClassVisitor
    : public clang::RecursiveASTVisitor<FindNamedClassVisitor> {
 public:
  explicit FindNamedClassVisitor(clang::ASTContext* context)
      : context_{context} {}

  bool VisitCXXRecordDecl(clang::CXXRecordDecl* declaration) {
    if (declaration->getQualifiedNameAsString() == "n::m::C") {
      clang::FullSourceLoc full_location =
          context_->getFullLoc(declaration->getBeginLoc());
      if (full_location.isValid()) {
        llvm::outs() << "Found declaration at "
                     << full_location.getSpellingLineNumber() << ":"
                     << full_location.getSpellingColumnNumber() << '\n';
      }
    }

    return true;
  }

 private:
  clang::ASTContext* context_;
};

class FindNamedClassConsumer : public clang::ASTConsumer {
 public:
  explicit FindNamedClassConsumer(clang::ASTContext* context)
      : visitor_{context} {}

  void HandleTranslationUnit(clang::ASTContext& context) override {
    visitor_.TraverseDecl(context.getTranslationUnitDecl());
  }

 private:
  FindNamedClassVisitor visitor_;
};

class FindNamedClassAction : public clang::ASTFrontendAction {
 public:
  std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
      clang::CompilerInstance& compiler, llvm::StringRef in_file) override {
    return std::unique_ptr<clang::ASTConsumer>(
        new FindNamedClassConsumer(&compiler.getASTContext()));
  }
};

int main(int argc, const char** argv) {
  std::string v = clang::getClangFullVersion();
  std::cout << "Using Clang Version: " << v << '\n';



  if (argc > 1) {
    clang::tooling::runToolOnCode(new FindNamedClassAction, argv[1]);
  }
  return 0;
}

