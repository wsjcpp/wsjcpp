#include "argument_processor_lint.h"
#include "wsjcpp_package_manager.h"
#include "wsjcpp_core.h"

// ---------------------------------------------------------------------
// ArgumentProcessorLint

ArgumentProcessorLint::ArgumentProcessorLint() 
  : WsjcppArgumentProcessor({"lint"}, "Linter for files", "Run linter") {

}

int ArgumentProcessorLint::exec(const std::vector<std::string> &vRoutes, const std::vector<std::string> &vSubParams) {
  std::vector<std::string> vFiles = WsjcppCore::getListOfFiles("./");

  std::vector<std::string> vDirs = WsjcppCore::getListOfDirs("./");
  while (!vDirs.empty()) {
    std::string sPath = vDirs.back();
    vDirs.pop_back();
    if (
      sPath == ".git"
      || sPath == ".vscode"
      || sPath == ".github"
      || sPath == ".wsjcpp"
    ) {
      continue;
    }
    std::vector<std::string> vTmpFiles = WsjcppCore::getListOfFiles(sPath);
    for (int i = 0; i < vTmpFiles.size(); i++) {
      std::string sFilepath = sPath + "/" + vTmpFiles[i];
      vFiles.push_back(sFilepath);
      
    }
    std::vector<std::string> vTmpDirs = WsjcppCore::getListOfDirs(sPath);
    for (int i = 0; i < vTmpDirs.size(); i++) {
      std::string sDirpath = sPath + "/" + vTmpDirs[i];
      vDirs.push_back(sDirpath);
    }
  }
  int nRet = 0;
  for (int i = 0; i < vFiles.size(); i++) {
    std::string sFilepath = vFiles[i];
    if (
      !isEndsWith(sFilepath, ".cpp")
      && !isEndsWith(sFilepath, ".h")
      && !isEndsWith(sFilepath, ".hpp")
      && !isEndsWith(sFilepath, ".c")
    ) {
      continue;
    }
    std::string sOutputContent;
    if (!WsjcppCore::readTextFile(sFilepath, sOutputContent)) {
      std::cout << "Could not read file: " << sFilepath << std::endl;
      continue;
    }

    std::vector<std::string> vLines = WsjcppCore::split(sOutputContent, "\n");   
    for (int l = 0; l < vLines.size(); l++) {
      std::string sLine = vLines[l];
      if (
        sLine.length() > 0
        && (
            sLine[sLine.length()-1] == ' '
            || sLine[sLine.length()-1] == '\t'
        )
      ) {
        std::cout << sFilepath << ":" << (l + 1) << " - trailing spaces on end of line" << std::endl;
        nRet = -1;
      }
    }
  }
  return nRet;
}


bool ArgumentProcessorLint::isEndsWith(std::string const &sValue, std::string const &sEnding) {
  if (sEnding.size() > sValue.size()) return false;
  return std::equal(sEnding.rbegin(), sEnding.rend(), sValue.rbegin());
}