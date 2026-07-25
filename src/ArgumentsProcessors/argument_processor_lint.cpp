/*
 * MIT License
 *
 * Copyright (c) 2019-2026 Evgenii Sopov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

// original source-code: https://github.com/wsjcpp/wsjcpp


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

  std::vector<std::string> vDirs = wsjcpp::directory_list("./");
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
    std::vector<std::string> vTmpDirs = wsjcpp::directory_list(sPath);
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

    std::vector<std::string> vLines = wsjcpp::split(sOutputContent, "\n");
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