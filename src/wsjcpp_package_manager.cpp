#include "wsjcpp_package_manager.h"
#include <iostream>
#include <wsjcpp_core.h>
#include <fstream>
#include <iomanip>
#include <wsjcpp_hashes.h>
#include <wsjcpp_core.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <regex>
#include <wsjcpp_safe_scripting.h>

// ---------------------------------------------------------------------
// WsjcppPackageManagerOrigin - server info class

WsjcppPackageManagerOrigin::WsjcppPackageManagerOrigin() {
    TAG = "WsjcppPackageManagerOrigin";
    m_pYamlOrigin = nullptr;
}

// ---------------------------------------------------------------------

WsjcppYamlItem *WsjcppPackageManagerOrigin::toYAML() {
    m_pYamlOrigin->setValue(m_sAddress, true);
    return m_pYamlOrigin;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManagerOrigin::fromYAML(WsjcppYamlItem *pYaml) {
    m_pYamlOrigin = pYaml;
    if (!m_pYamlOrigin->hasElement("address")) {
        WsjcppLog::err(TAG, "Missing required field 'address' in " + m_pYamlOrigin->getForLogFormat());
        return false; 
    } else {
        m_sAddress = m_pYamlOrigin->getElement("address")->getValue();
    }

    if (!m_pYamlOrigin->hasElement("type")) {
        WsjcppLog::err(TAG, "Missing required field 'type' in " + m_pYamlOrigin->getForLogFormat());
        return false; 
    } else {
        m_sType = m_pYamlOrigin->getElement("type")->getValue();
    }

    return true;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerOrigin::getAddress() {
    return m_sAddress;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerOrigin::getType() {
    return m_sType;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerOrigin::setAddress(const std::string &sAddress) {
    m_sAddress = sAddress;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerOrigin::setType(const std::string &sType) {
    m_sType = sType;
}

// ---------------------------------------------------------------------
// WsjcppPackageManagerRepository - repository struct

WsjcppPackageManagerRepository::WsjcppPackageManagerRepository() {
    TAG = "WsjcppPackageManagerRepository";
}

// ---------------------------------------------------------------------

WsjcppYamlItem *WsjcppPackageManagerRepository::toYAML() {
    m_pYamlRepository->getElement("url")->setValue(m_sUrl, true);
    m_pYamlRepository->getElement("type")->setValue(m_sType, true);
    return m_pYamlRepository;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManagerRepository::fromYAML(WsjcppYamlItem *pYaml) {
    m_pYamlRepository = pYaml;
    if (!m_pYamlRepository->hasElement("type")) {
        WsjcppLog::err(TAG, "Missing required field 'type' in " + m_pYamlRepository->getForLogFormat());
        return false; 
    } else {
        m_sType = m_pYamlRepository->getElement("type")->getValue();
    }

    if (!m_pYamlRepository->hasElement("url")) {
        // TODO prepare in yaml getOriginalLineForError()
        WsjcppLog::err(TAG, "Missing required field 'url' in " + m_pYamlRepository->getForLogFormat());
        return false; 
    } else {
        m_sUrl = m_pYamlRepository->getElement("url")->getValue();
    }
    return true;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerRepository::getType() {
    return m_sType;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerRepository::getUrl() {
    return m_sUrl;
}

// ---------------------------------------------------------------------
// WsjcppPackageManagerUnitTest - main class

WsjcppPackageManagerUnitTest::WsjcppPackageManagerUnitTest() {
    TAG = "WsjcppPackageManagerUnitTest";
    m_bEnabled = true; // default enbaled 
}

// ---------------------------------------------------------------------

WsjcppYamlItem *WsjcppPackageManagerUnitTest::toYAML() {
    m_pYamlUnitTest->getElement("url")->setValue(m_sName, true);
    m_pYamlUnitTest->getElement("type")->setValue(m_sDescription, true);
    m_pYamlUnitTest->getElement("enabled")->setValue(m_bEnabled ? "yes" : "no", true);
    return m_pYamlUnitTest;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManagerUnitTest::fromYAML(WsjcppYamlItem *pYaml) {
    m_pYamlUnitTest = pYaml;
    std::vector<std::string> vKeys = m_pYamlUnitTest->getKeys();
    for (int i = 0; i < vKeys.size(); i++) {
        std::string sKey = vKeys[i];
        if (sKey == "name") {
            m_sName = m_pYamlUnitTest->getElement("name")->getValue();
        } else if (sKey == "description") {
            m_sDescription = m_pYamlUnitTest->getElement("description")->getValue();
        } else if (sKey == "enabled") {
            m_bEnabled = m_pYamlUnitTest->getElement("enabled")->getValue() == "yes";
        } else {
            WsjcppLog::warn(TAG, "Excess field '" + sKey + "' in " + m_pYamlUnitTest->getForLogFormat());
        }
    }

    // default values
    if (!m_pYamlUnitTest->hasElement("enabled")) {
        m_bEnabled = true;
    }

    // TODO move to yaml some validate function
    std::vector<std::string> vRequiredKeys;
    vRequiredKeys.push_back("name");
    vRequiredKeys.push_back("description");
    bool bHasError = false;
    for (int i = 0; i < vRequiredKeys.size(); i++) {
        std::string sKey = vRequiredKeys[i];
        if (!m_pYamlUnitTest->hasElement(sKey)) {
            WsjcppLog::err(TAG, "Missing required field '" + sKey + "' in " + m_pYamlUnitTest->getForLogFormat());
            bHasError = true;
        }
    }
    return !bHasError;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerUnitTest::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManagerUnitTest::getDescription() {
    return m_sDescription;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManagerUnitTest::isEnabled() {
    return m_bEnabled;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerUnitTest::setName(const std::string &sName) {
    m_sName = sName;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerUnitTest::setDescription(const std::string &sDescription) {
    m_sDescription = sDescription;
}

// ---------------------------------------------------------------------

void WsjcppPackageManagerUnitTest::setEnabled(bool bEnabled) {
    m_bEnabled = bEnabled;
}

// ---------------------------------------------------------------------
// WsjcppPackageManager - main class

WsjcppPackageManager::WsjcppPackageManager(const std::string &sDir) {
    TAG = "WsjcppPackageManager";
    if (sDir.length() > 0 && sDir[0] != '/') { // if not absolute path
        m_sDir = WsjcppCore::getCurrentDirectory() + "/" + sDir;
    } else {
        m_sDir = sDir;
    }
    m_sDir = WsjcppCore::doNormalizePath(m_sDir);
    

    m_sDirnameResources = "src-resources.wsjcpp";
    m_sDirResources = WsjcppCore::doNormalizePath(m_sDir + "/" + m_sDirnameResources);
    m_sDirWithSources = WsjcppCore::doNormalizePath(m_sDir + "/src.wsjcpp");
    // TODO m_sGithubPrefix = "git@";  // try clone project to cache directory
    
    m_sYamlFilename = "wsjcpp.yml";
    m_sWsjcppCurrentVersion = std::string(WSJCPP_APP_VERSION);
    m_sWsjcppVersion = m_sWsjcppCurrentVersion;
    m_bHolded = false;
    m_sIssues = "none";
    m_pDownloaders = new WsjcppPackageDownloaders();
}

// ---------------------------------------------------------------------

WsjcppPackageManager::WsjcppPackageManager(const std::string &sDir, const std::string &sParentDir, bool bHolded) 
: WsjcppPackageManager(sDir) {
    m_sDirWithSources = WsjcppCore::doNormalizePath(m_sDir + "/src.wsjcpp");
    m_sYamlFilename = "wsjcpp.hold.yml";
    m_bHolded = true; // must be detect by wsjcpp.hold.yml
    m_bHasDocker = false;
    m_sParentDir = sParentDir; // ???
}

// ---------------------------------------------------------------------

WsjcppPackageManager::~WsjcppPackageManager() {
    delete m_pDownloaders;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManager::getDir() const {
    return m_sDir;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::isHolded() const {
    return m_bHolded;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::init() {
    std::string sCurrentDirectory = WsjcppCore::getCurrentDirectory() + "/" + m_sDir;
    sCurrentDirectory = WsjcppCore::doNormalizePath(sCurrentDirectory);
    if (sCurrentDirectory[sCurrentDirectory.length()-1] == '/') {
        sCurrentDirectory = sCurrentDirectory.substr(0, sCurrentDirectory.size()-1);
    }
    m_sYamlFullpath = "wsjcpp.yml";

    // TODO check wsjcpp.yml

    m_sName = WsjcppCore::extractFilename(sCurrentDirectory);
    m_yamlPackageInfo.getRoot()->setElementValue("name", false, m_sName, true);

    m_sVersion = "v0.0.1";
    m_yamlPackageInfo.getRoot()->setElementValue("version", false, m_sVersion, true);
    
    m_sCMakeMinimumRequired = "3.0";
    m_yamlPackageInfo.getRoot()->setElementValue("cmake_minimum_required", false, m_sCMakeMinimumRequired, true);

    m_sCMakeCxxStandard = "11";
    m_yamlPackageInfo.getRoot()->setElementValue("cmake_cxx_standard", false, m_sCMakeCxxStandard, true);


    std::cout << "Source Package Name: " << m_sName << std::endl;
    std::cout << "Version: " << m_sVersion << std::endl;

    std::cout << "Description: ";
    std::getline(std::cin, m_sDescription);

    m_yamlPackageInfo.getRoot()->setElementValue("description", false, m_sDescription, true);

    std::string sAuthorName = "";
    std::cout << "Author's Name: ";
    std::getline(std::cin, sAuthorName);

    std::string sAuthorEmail = "";
    std::cout << "Author's Email: ";
    std::getline(std::cin, sAuthorEmail);

    addAuthor(sAuthorName, sAuthorEmail);
    addOrigin("https://sea-kg.com/wsjcpp-package-registry/");

    m_yamlPackageInfo.getRoot()->createElementArray("keywords", false);
    m_yamlPackageInfo.getRoot()->getElement("keywords")->appendElementValue("c++", true);

    // addKeyword("wsjcpp");

    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::save() {
    if (m_bHolded) {
        WsjcppLog::throw_err(TAG, "wsjcpp is holded");
        return false;
    }

    if (!WsjcppCore::dirExists(m_sDirWithSources)) {
        WsjcppCore::makeDir(m_sDirWithSources);
    }

    std::string sGitkeepFile = m_sDirWithSources + "/.gitkeep";
    if (!WsjcppCore::fileExists(sGitkeepFile)) {
        WsjcppCore::writeFile(sGitkeepFile, ""); // TODO createEmptyFile
    }
    m_yamlPackageInfo.saveToFile(m_sYamlFullpath);
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::load(/*std::string &sError*/) {
    m_sYamlFullpath = WsjcppCore::doNormalizePath(m_sDir + "/" + m_sYamlFilename);
    if (!WsjcppCore::fileExists(m_sYamlFullpath)) {
        // sError = "File '" + m_sYamlFullpath + "' did not found";
        std::cout << "ERROR: '" << m_sYamlFullpath << "' did not found" << std::endl;
        return false;
    }
    
    if (!m_yamlPackageInfo.loadFromFile(m_sYamlFullpath)) {
        return false;
    }

    std::vector<std::string> vKeys = m_yamlPackageInfo.getRoot()->getKeys();
    for (int i = 0; i < vKeys.size(); i++) {
        std::string sKey = vKeys[i];
        // WsjcppLog::info(TAG, "Process option '" + sKey + "'");
        if (sKey == "version") {
            if (!readFieldVersion()) {
                return false;
            }
        } else if (sKey == "cmake_minimum_required") {
            if (!readFieldCMakeMinimumRequired()) {
                return false;
            }
        } else if (sKey == "cmake_cxx_standard") {
            if (!readFieldCMakeCxxStandard()) {
                return false;
            }
        } else if (sKey == "name") {
            if (!readFieldName()) {
                return false;
            }
        } else if (sKey == "description") {
            if (!readFieldDescription()) {
                return false;
            }
        } else if (sKey == "wsjcpp_version") {
            if (!readFieldWsjcppVersion()) {
                return false;
            }
        } else if (sKey == "issues") {
            if (!readFieldIssues()) {
                return false;
            }
        } else if (sKey == "keywords") {
            if (!readFieldKeywords()) {
                return false;
            }
        } else if (sKey == "authors") {
            if (!readFieldAuthors()) {
                return false;
            }
        } else if (sKey == "distribution") {
            if (!readFieldDistribution()) {
                return false;
            }
        } else if (sKey == "origins") {
            if (!readFieldOrigins()) {
                return false;
            }
        } else if (sKey == "dependencies") {
            if (!readFieldDependencies()) {
                return false;
            }
        } else if (sKey == "repositories") {
            if (!readFieldRepositories()) {
                return false;
            }
        } else if (sKey == "resources") {
            if (!readFieldResources()) {
                return false;
            }
        } else if (sKey == "unit-tests") {
            if (!readFieldUnitTests()) {
                return false;
            }
        } else if (sKey == "required-libraries") {
            if (!readFieldRequiredLibraries()) {
                return false;
            }
        } else if (sKey == "required-pkg-config") {
            if (!readFieldRequiredPkgConfig()) {
                return false;
            }
        } else if (sKey == "docker") {
            m_bHasDocker = true;
            WsjcppLog::warn(TAG, "TODO read docker section");
            // if (!readFieldRequiredPkgConfig()) {
            //    return false;
            // }
        } else {
            WsjcppLog::warn(TAG, "Ignored option '" + sKey + "' in " + m_yamlPackageInfo.getRoot()->getForLogFormat());
        }
    }

    // WsjcppLog::warn(TAG, "Loaded");
    // TODO required-libraries
    // TODO required-pkg-config
    // TODO replace-dependencies
    // TODO check requered fields

    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::addSourceFile(const std::string &sSourceFile, const std::string &sTargetFile, const std::string &sType) {
    if (m_bHolded) {
        WsjcppLog::err(TAG, "wsjcpp is holded");
        return false;
    }

    if (!WsjcppCore::fileExists(sSourceFile)) {
        WsjcppLog::err(TAG, "'" + sSourceFile + "' file does not exists");
        return false;
    }
    std::vector<WsjcppPackageManagerDistributionFile>::iterator it;
    for (it = m_vDistributionFiles.begin(); it != m_vDistributionFiles.end(); ++it) {
        if (it->getSourceFile() == sSourceFile) {
            WsjcppLog::err(TAG, "This package already contained file '" + sSourceFile + "'");
            return false;
        }
    }

    std::string sContent = "";
    if (!WsjcppCore::readTextFile(sSourceFile, sContent)) {
        return false;
    }

    WsjcppPackageManagerDistributionFile file;
    file.setSourceFile(sSourceFile);
    file.setTargetFile(sTargetFile);
    file.setType(sType);
    m_vDistributionFiles.push_back(file);
    
    WsjcppYamlItem *pRoot = m_yamlPackageInfo.getRoot();
    if (!pRoot->hasElement("distribution")) {
        pRoot->createElementArray("distribution", false);
    }

    WsjcppYamlItem *pDist = m_yamlPackageInfo.getRoot()->getElement("distribution");
    WsjcppYamlPlaceInFile pl;
    WsjcppYamlItem *pItem = new WsjcppYamlItem(pDist, pl, WsjcppYamlItemType::WSJCPP_YAML_ITEM_MAP);
    pItem->setElementValue("source-file", false, sSourceFile, true);
    pItem->setElementValue("target-file", false, sTargetFile, true);
    pItem->setElementValue("type", false, sType, true);
    pDist->appendElement(pItem);
    updateAutogeneratedFiles();
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::removeSourceFile(const std::string &sSourceFile) {
    if (m_bHolded) {
        WsjcppLog::err(TAG, "wsjcpp is holded");
        return false;
    }
    bool bResult = false;
    for (auto it = m_vDistributionFiles.begin(); it != m_vDistributionFiles.end(); ++it) {
        if (it->getSourceFile() == sSourceFile) {
            m_vDistributionFiles.erase(it);
            bResult = true;
            break;
        }
    }
    if (bResult) {
        bResult = false;
        WsjcppYamlItem *pDist = m_yamlPackageInfo.getRoot()->getElement("distribution");
        int nLen = pDist->getLength();
        for (int i = nLen-1; i >= 0; i--) {
            WsjcppYamlItem *pItem = pDist->getElement(i);
            if (pItem->getElement("source-file")->getValue() == sSourceFile) {
                pDist->removeElement(i);
                bResult = true;
            }
        }
    }

    if (!bResult) {
        WsjcppLog::err(TAG, "Distribution file '" + sSourceFile + "' cound not found in this package");
    } else {
        updateAutogeneratedFiles();
    }
    
    return bResult;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::updateSourceFile(const std::string &sSourceFile, bool bAutoUpdate = true) {
    if (m_bHolded) {
        WsjcppLog::err(TAG, "wsjcpp is holded");
        return false;
    }
    std::string sFilePath = m_sDir + "/" + sSourceFile;
    if (!WsjcppCore::fileExists(sFilePath)) {
        WsjcppLog::err(TAG, "'" + sSourceFile + "' file does not exists in " + m_sDir);
        return false;
    }

    std::string sContent = "";
    if (!WsjcppCore::readTextFile(sFilePath, sContent)) {
        return false;
    }
    std::string sSha1 = WsjcppHashes::sha1_calc_hex(sContent);

    bool bFound = false;
    std::vector<WsjcppPackageManagerDistributionFile>::iterator it;
    for (it = m_vDistributionFiles.begin(); it != m_vDistributionFiles.end(); ++it) {
        if (it->getSourceFile() == sSourceFile) {
            it->setSha1(sSha1);
            bFound = true;
        }
    }

    if (!bFound) {
        WsjcppLog::err(TAG, "'" + sSourceFile + "' file not found in list. Please add this before");
        return false;
    }

    if (bFound) {
        bFound = false;
        WsjcppYamlItem *pDist = m_yamlPackageInfo.getRoot()->getElement("distribution");
        int nLen = pDist->getLength();
        for (int i = nLen-1; i >= 0; i--) {
            WsjcppYamlItem *pItem = pDist->getElement(i);
            if (pItem->getElement("source-file")->getValue() == sSourceFile) {
                if (!pItem->hasElement("sha1")) {
                    pItem->setElementValue("sha1", false, sSha1, true);
                } else {
                    pItem->getElement("sha1")->setValue(sSha1, true);
                }
                bFound = true;
            }
        }
    }
    if (bAutoUpdate) {
        updateAutogeneratedFiles();
    }
    return bFound;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::createUnitTest(const std::string &sUnitTestName, const std::string &sUnitTestDescription) {
    if (m_bHolded) {
        WsjcppLog::err(TAG, "wsjcpp is holded");
        return false;
    }

    std::string sName = normalizeUnitTestName(sUnitTestName, false);
    if (sName != sUnitTestName) {
        WsjcppLog::warn(TAG, "UnitTest name was normalized '" + sUnitTestName + "' -> '" + sName + "'");
    }

    for (int i = 0; i < m_vUnitTests.size(); i++) {
        if (m_vUnitTests[i].getName() == sName) {
            WsjcppLog::err(TAG, "Unit test with name '" + sName + "' already exists");
            return false;
        }
    }

    // first find generate file by generate.WsjcppUnitTest.wsjcpp-script
    std::string sWsjcppUnitTestScriptFilePath = "";
    std::vector<WsjcppPackageManagerSafeScriptingGenerate> vScripts = getListOfSafeScriptingGenerate();
    for (int i = 0; i < vScripts.size(); i++) {
        if (vScripts[i].getName() == "WsjcppUnitTest") {
            sWsjcppUnitTestScriptFilePath = vScripts[i].getFullPath();
        }
    }

    if (sWsjcppUnitTestScriptFilePath == "") {
        WsjcppLog::err(TAG, "Not found 'generate.WsjcppUnitTest.wsjcpp-script', porabble try install 'wsjcpp-core' package.");
        return false;
    }

    // TODO redesign WsjcppCore::makeDirPath
    std::string sUnitTestsFolder = WsjcppCore::doNormalizePath(m_sDir + "/unit-tests.wsjcpp");
    if (!WsjcppCore::dirExists(sUnitTestsFolder)) {
        if (!WsjcppCore::makeDir(sUnitTestsFolder)) {
            WsjcppLog::err(TAG, "Could not create '" + sUnitTestsFolder + "'");
            return false;
        }
    }
    sUnitTestsFolder = sUnitTestsFolder + "/src";
    if (!WsjcppCore::dirExists(sUnitTestsFolder)) {
        if (!WsjcppCore::makeDir(sUnitTestsFolder)) {
            WsjcppLog::err(TAG, "Could not create '" + sUnitTestsFolder + "'");
            return false;
        }
    }

    if (!WsjcppCore::dirExists("./unit-tests.wsjcpp/src/")) {
        WsjcppLog::err(TAG, "Directory does not exists './unit-tests.wsjcpp/src/'");
        return false;
    }

    std::string sUnitTestFilepathSources = sUnitTestsFolder + "/" + this->generateFilenameForUnitTest(sUnitTestName) + ".cpp";

    WsjcppPackageManagerUnitTest unitTest;
    unitTest.setName(sName);
    unitTest.setDescription(sUnitTestDescription);
    m_vUnitTests.push_back(unitTest);
    
    m_yamlPackageInfo.getRoot()->createElementMap("unit-tests", false);
    WsjcppYamlItem *pUnitTests = m_yamlPackageInfo.getRoot()->getElement("unit-tests");
    pUnitTests->createElementArray("cases", false);
    WsjcppYamlItem *pCases = pUnitTests->getElement("cases");

    WsjcppYamlItem *pNewItem = pCases->createElementMap();
    pNewItem->setElementValue("name", false, sName, true);
    pNewItem->setElementValue("description", false, sUnitTestDescription, true);

    WsjcppSafeScriptingContext scriptContext;
    std::vector<std::string> vScriptArgs;
    vScriptArgs.push_back("UnitTest" + sName);
    vScriptArgs.push_back(sUnitTestFilepathSources);

    std::string sScriptContent;
    if (!WsjcppCore::readTextFile(sWsjcppUnitTestScriptFilePath, sScriptContent)) {
        WsjcppLog::err(TAG, "Could not read file: '" + sWsjcppUnitTestScriptFilePath + "");
        return false;
    }

    int nResult = scriptContext.exec(
        m_sDir, 
        sWsjcppUnitTestScriptFilePath, 
        sScriptContent,
        vScriptArgs
    );

    if (nResult != 0) {
        return false;
    }

    updateAutogeneratedFiles();
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::deleteUnitTest(const std::string &sUnitTestName) {
    if (m_bHolded) {
        WsjcppLog::err(TAG, "Package is holded");
        return false;
    }

    std::string sName = normalizeUnitTestName(sUnitTestName, false);
    if (sName != sUnitTestName) {
        WsjcppLog::warn(TAG, "UnitTest name was normalized '" + sUnitTestName + "' -> '" + sName + "'");
    }

    bool bFound = false;
    std::vector<WsjcppPackageManagerUnitTest>::iterator it; 
    for (it = m_vUnitTests.begin(); it < m_vUnitTests.end(); ++it) {
        if (it->getName() == sName) {
            bFound = true;
            m_vUnitTests.erase(it);
            break;
        }
    }
    if (!bFound) {
        WsjcppLog::err(TAG, "Not found unit-test with name '" + sName + "'");
        return false;    
    }
    WsjcppYamlItem *pItem = m_yamlPackageInfo["unit-tests"].getElement("cases");
    int nLength = pItem->getLength();
    for (int i = 0; i < nLength; i++) {
        if (pItem->getElement(i)->getElement("name")->getValue() == sName) {
            std::string sBaseName = this->generateFilenameForUnitTest(sUnitTestName);
            std::string sFileSource = WsjcppCore::doNormalizePath(m_sDir + "/unit-tests.wsjcpp/src/" + sBaseName + ".cpp");
            if (WsjcppCore::fileExists(sFileSource)) {
                WsjcppCore::removeFile(sFileSource);
            }
            /*if (nLength == 1) {
                return m_yamlPackageInfo.getRoot()->removeElement("unit-tests");
            }*/
            if (pItem->removeElement(i)) {
                updateAutogeneratedFiles();
                return true;
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::enableUnitTest(const std::string &sUnitTestName, bool bEnable) {
    if (m_bHolded) {
        WsjcppLog::err(TAG, "Package is holded");
        return false;
    }

    bool bFound = false;
    std::vector<WsjcppPackageManagerUnitTest>::iterator it; 
    for (it = m_vUnitTests.begin(); it < m_vUnitTests.end(); ++it) {
        if (it->getName() == sUnitTestName) {
            it->setEnabled(bEnable);
            bFound = true;
            break;
        }
    }
    if (!bFound) {
        WsjcppLog::err(TAG, "Not found unit-test with name '" + sUnitTestName + "'");
        return false;    
    }
    WsjcppYamlItem *pItem = m_yamlPackageInfo["unit-tests"].getElement("cases");
    int nLength = pItem->getLength();
    for (int i = 0; i < nLength; i++) {
        if (pItem->getElement(i)->getElement("name")->getValue() == sUnitTestName) {
            pItem->getElement(i)->setElementValue("enabled", false, bEnable ? "yes" : "no", true);
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::addOrigin(const std::string &sAddress) {
    if (m_bHolded) {
        WsjcppLog::err(TAG, "Package is holded");
        return false;
    }
    // TODO check address format
    // TODO request online for type
    for (auto it = m_vOrigins.begin(); it != m_vOrigins.end(); ++it) {
        if (it->getAddress() == sAddress) {
            WsjcppLog::err(TAG, "Error: Origin '" + sAddress + "' already defined.");
            return false;
        }
    }

    std::string sOriginType = "package-registry";
    WsjcppPackageManagerOrigin origin;
    origin.setAddress(sAddress);
    origin.setType(sOriginType);
    m_vOrigins.push_back(origin);

    if (!m_yamlPackageInfo.getRoot()->hasElement("origins")) {
        m_yamlPackageInfo.getRoot()->createElementArray("origins", false);
    }
    
    WsjcppYamlItem *pOrigins = m_yamlPackageInfo.getRoot()->getElement("origins");
    WsjcppYamlPlaceInFile pl;
    WsjcppYamlItem *pNewItemMap = new WsjcppYamlItem(pOrigins, pl, WsjcppYamlItemType::WSJCPP_YAML_ITEM_MAP);
    pNewItemMap->setElementValue("address", false, sAddress, true);
    pNewItemMap->setElementValue("type", false, sOriginType, true);
    pOrigins->appendElement(pNewItemMap);
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::deleteOrigin(const std::string &sAddress) {
    if (m_bHolded) {
        WsjcppLog::err(TAG, "wsjcpp is holded");
        return false;
    }

    std::vector<WsjcppPackageManagerOrigin>::iterator it;
    for (it = m_vOrigins.begin(); it != m_vOrigins.end(); ++it) {
        if (it->getAddress() == sAddress) {
            m_vOrigins.erase(it);
            return true;
        }
    }
    WsjcppLog::err(TAG, "Origin '" + sAddress + "' did not found." );
    return false;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::updateDependencies() {
    if (m_bHolded) {
        std::cout << "ERROR: wsjcpp is holded" << std::endl;
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------

void WsjcppPackageManager::verify() {
    std::vector<std::string> m_vVerified;

    // HERE verify current package
    
    for (auto it = m_vDependencies.begin(); it != m_vDependencies.end(); ++it) {
        if (m_bHolded) {
            WsjcppPackageManager m(m_sParentDir + "/" + it->getName(), m_sParentDir, true);
            if (m.load()) {
                m.verify();
            }
        } else {
            WsjcppPackageManager m(m_sDirWithSources + "/" + it->getName(), m_sDirWithSources, true);
            if (m.load()) {
                m.verify();
            }
        }
        
    }
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::install(const std::string &sPackage, std::string &sError) {
    if (m_bHolded) {
        WsjcppLog::err(TAG, "Could not install package when holded");
        return false;
    }

    if (isInstalled(sPackage)) {
        sError = "Already installed.";
        return false;
    }

    std::cout << "Search package from " << sPackage << " ..." << std::endl;
   
    std::string sWsjcppBaseUrl = sPackage;

    WsjcppPackageManagerDependence dep;
    if (!m_pDownloaders->downloadToCache(sPackage, m_sDir, dep, sError)) {
        return false;
    }

    if (isInstalled(dep.getName())) {
        sError = "Package '" + dep.getName() + "' already installed.";
        return false;
    }

    addDependency(dep);
    return installFromCache(sPackage, dep, sError);
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::checkInstalledPackage(
    const std::string &sPackage, 
    std::vector<std::string> &vFilesInstalled, 
    std::string &sPackageUrl,
    std::string &sError
) {
    
    // find installed package
    std::string sPackageInstallationDir = "";
    std::vector<WsjcppPackageManagerDependence> deps = getListOfDependencies();
    for (int i = 0; i < deps.size(); i++) {
        WsjcppPackageManagerDependence dep = deps[i];
        if (sPackage == dep.getUrl() || sPackage == dep.getName()) {
            sPackageUrl = dep.getUrl();
            sPackageInstallationDir = WsjcppCore::doNormalizePath(m_sDir + "/" + dep.getInstallationDir());
        }
    }

    if (sPackageUrl == "" || sPackageInstallationDir == "") {
        sError = "Not found installed package '" + sPackage + "'";
        return false;
    }

    // prepare old file list for remove before install
    // std::cout << "sPackageInstallationDir = " << sPackageInstallationDir << std::endl;
    WsjcppPackageManager installedPkg(sPackageInstallationDir, m_sDir, true);
    if (!installedPkg.load()) {
        sError = "Could not load " + sPackageInstallationDir;
        return false;
    }

    std::vector<WsjcppPackageManagerDistributionFile> vSources = installedPkg.getListOfDistributionFiles();
    bool bHasChanges = false;
    std::string sFilesHasChanges = "";
    vFilesInstalled.clear();
    vFilesInstalled.push_back(sPackageInstallationDir + "/wsjcpp.hold.yml");
    for (int i = 0; i < vSources.size(); i++) {
        WsjcppPackageManagerDistributionFile src = vSources[i];
        std::string sFilename = sPackageInstallationDir + "/" + src.getTargetFile();
        
        vFilesInstalled.push_back(sFilename);

        // calculate sha1
        if (!WsjcppCore::fileExists(sFilename)) {
            sFilesHasChanges += " - missed: " + sFilename + " (with sha1:'" + src.getSha1() + "')\n";
            bHasChanges = true;
        } else {
            // TODO redesign to WsjcppHashes::getSha1ByFile(sFilename);
            std::string sContent = "";
            if (!WsjcppCore::readTextFile(sFilename, sContent)) {
                sError = "Could not read file '" + sFilename + "'";
                return false;
            }
            std::string sSha1 = WsjcppHashes::sha1_calc_hex(sContent);
            if (sSha1 != src.getSha1()) {
                sFilesHasChanges += " - wrong sha1: " + sFilename + " (expected sha1 '" + sSha1 + "', but got '" + src.getSha1() + "')\n";
                bHasChanges = true;
            }
        }
    }

    std::vector<std::string> vFiles = WsjcppCore::getListOfFiles(sPackageInstallationDir);
    for (int i = 0; i < vFiles.size(); i++) {
        std::string sFilename = sPackageInstallationDir + "/" + vFiles[i];
        std::vector<std::string>::iterator it;
        it = std::find(vFilesInstalled.begin(), vFilesInstalled.end(), sFilename);
        if (it == vFilesInstalled.end()) {
            sFilesHasChanges += " - extra: " + sFilename + " (this file must be not exist)\n";
            bHasChanges = true;
        }
    }

    if (bHasChanges) {
        sError = sFilesHasChanges + "\n\n"
                "  Wsjcpp found some changes in the file(s) after latest installation. \n"
                "  So you can just remove package dir and from wsjcpp.yml by yourself if changes are not important. \n"
                "  Or compare with downloaded latest file(s) from cache\n\n";
        return false;
    }

    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::reinstall(const std::string &sPackage, std::string &sError) {
    if (m_bHolded) {
        sError = "Could not reinstall package when holded";
        return false;
    }

    // check the installed package
    std::vector<std::string> vTodoRemoveFiles;
    std::string sPackageUrl;
    if (!checkInstalledPackage(sPackage, vTodoRemoveFiles, sPackageUrl, sError)) {
        return false;
    }

    // download package to cache
    WsjcppPackageManagerDependence dep;
    if (!m_pDownloaders->downloadToCache(sPackageUrl, m_sDir, dep, sError)) {
        return false;
    }

    // remove old files
    for (int i = 0; i < vTodoRemoveFiles.size(); i++) {
        if (!WsjcppCore::removeFile(vTodoRemoveFiles[i])) {
            sError = "Could not remove '" + vTodoRemoveFiles[i] + "'";
            return false;
        }
    }

    updateDependency(dep);
    return installFromCache(sPackageUrl, dep, sError);
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::uninstall(const std::string &sPackageUrl, std::string &sError) {
    if (m_bHolded) {
        WsjcppLog::err(TAG, "Could not reinstall package when holded");
        return false;
    }

    bool bResult = false;
    std::vector<WsjcppPackageManagerDependence>::iterator it;
    for (it = m_vDependencies.begin(); it != m_vDependencies.end(); ++it) {
        if (it->getUrl() == sPackageUrl || it->getName() == sPackageUrl) {
            WsjcppPackageManagerDependence dep = *it;
            removeDependenciesFilesSafe(dep);
            m_vDependencies.erase(it);
            bResult = true;
            break;
        }
    }
    if (!bResult) {
        WsjcppLog::err(TAG, "Package '" + sPackageUrl + "' did not installed");
        return false;
    }
    WsjcppYamlItem *pDeps = m_yamlPackageInfo.getRoot()->getElement("dependencies");
    int nLen = pDeps->getLength();
    for (int i = nLen-1; i >= 0; i--) {
        WsjcppYamlItem *pItemMap = pDeps->getElement(i);
        if (sPackageUrl == pItemMap->getElement("url")->getValue()) {
            pDeps->removeElement(i);
        } else if (sPackageUrl == pItemMap->getElement("name")->getValue()) {
            pDeps->removeElement(i);
        }
    }

    // TODO remove none defined sub-requirements

    return true;
}

// ---------------------------------------------------------------------

void WsjcppPackageManager::addDependency(WsjcppPackageManagerDependence &dep) {
    m_vDependencies.push_back(dep);
    WsjcppYamlItem *pRoot = m_yamlPackageInfo.getRoot();
    if (!pRoot->hasElement("dependencies")) {
        pRoot->createElementArray("dependencies", false);
    }

    WsjcppYamlItem *pDeps = pRoot->getElement("dependencies");
    WsjcppYamlPlaceInFile pl;
    WsjcppYamlItem *pItem = new WsjcppYamlItem(pDeps, pl, WsjcppYamlItemType::WSJCPP_YAML_ITEM_MAP);
    // TODO add simplyfy method
    pItem->setElementValue("name", false, dep.getName(), true);
    pItem->setElementValue("version", false, dep.getVersion(), true);
    pItem->setElementValue("url", false, dep.getUrl(), true);
    pItem->setElementValue("origin", false, dep.getOrigin(), true);
    pItem->setElementValue("installation-dir", false, dep.getInstallationDir(), true);
    pDeps->appendElement(pItem);
}

// ---------------------------------------------------------------------

void WsjcppPackageManager::updateDependency(WsjcppPackageManagerDependence &dep) {
    WsjcppYamlItem *pDeps = m_yamlPackageInfo.getRoot()->getElement("dependencies");
    int nLen = pDeps->getLength();
    for (int i = 0; i < nLen; i++) {
        WsjcppYamlItem *pItem = pDeps->getElement(i);
        std::string sUrl = pItem->getElement("url")->getValue();
        if (dep.getUrl() == sUrl) {
            pItem->getElement("version")->setValue(dep.getVersion(), true);
            pItem->getElement("name")->setValue(dep.getName(), true);
            // pItem->getElement("url")->setValue(dep.getUrl(), true);
            pItem->getElement("origin")->setValue(dep.getOrigin(), true);
            pItem->getElement("installation-dir")->setValue(dep.getInstallationDir(), true);
        }
    }
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::isInstalled(const std::string &sPackage) {
    // todo check in current dependencies
    for (int i = 0; i < m_vDependencies.size(); i++) {
        WsjcppPackageManagerDependence dep = m_vDependencies[i];
        if (dep.getUrl() == sPackage || dep.getName() == sPackage) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::installFromCache(
    const std::string &sPackageUrl,
    const WsjcppPackageManagerDependence &dep,
    std::string &sError
) {
    std::string sInstallationDir = WsjcppCore::doNormalizePath(m_sDir + "/" + dep.getInstallationDir());

    if (!WsjcppCore::dirExists(sInstallationDir)) {
        WsjcppCore::makeDir(sInstallationDir);
    }
    
    std::string sCacheDir = m_sDir + "/.wsjcpp/cache";
    sCacheDir = sCacheDir + "/" + WsjcppPackageDownloaderBase::prepareCacheSubFolderName(sPackageUrl);
    std::string sCacheWsjcppHoldYml = sCacheDir + "/wsjcpp.hold.yml";
    std::string sCacheWsjcppYml = sCacheDir + "/wsjcpp.yml";

    if (WsjcppCore::fileExists(sCacheWsjcppHoldYml)) {
        // TODO deprecated method
        // TODO redesign to WsjcppCore::recoursiveCopyFiles
        // copy sources to installation dir
        std::vector<std::string> vFiles = WsjcppCore::getListOfFiles(sCacheDir);
        for (int i = 0; i < vFiles.size(); i++) {
            std::string sFrom = sCacheDir + "/" + vFiles[i];
            std::string sTo = sInstallationDir + "/" + vFiles[i];
            if (!WsjcppCore::copyFile(sFrom, sTo)) {
                sError = "Could not copy file '" + sFrom + "' to '" + sTo + "'";
                return false;
            }
        }
        // TODO install all dependencies
        // TODO update src.wsjcpp/
        return true;
    } else if (WsjcppCore::fileExists(sCacheWsjcppYml)) {
        
        WsjcppPackageManager pkg(sCacheDir);
        if (!pkg.load()) {
            sError = "Could not load package from copy '" + sCacheDir + "'";
            return false;
        }

        if (!WsjcppCore::copyFile(sCacheWsjcppYml, sInstallationDir + "/wsjcpp.hold.yml")) {
            sError = "Could not copy " + sCacheWsjcppYml + " -> " + sInstallationDir + "/wsjcpp.hold.yml";
            return false;
        }

        std::vector<WsjcppPackageManagerDistributionFile> vSources = pkg.getListOfDistributionFiles();
        for (int i = 0; i < vSources.size(); i++) {
            WsjcppPackageManagerDistributionFile src = vSources[i];
            std::string sFileFrom = sCacheDir + "/" + src.getSourceFile();
            std::string sFileTo = sInstallationDir + "/" + src.getTargetFile();
            if (!WsjcppCore::copyFile(sFileFrom, sFileTo)) {
                sError = "Could not copy from '" + sFileFrom + "' to '" + sFileTo + "'";
                return false;
            }
        }
        
        // TODO install all dependencies
        // TODO update src.wsjcpp/
        return true;
    }

    sError = "Not found wsjcpp.yml in '" + sCacheDir + "'";
    return false;
}

// ---------------------------------------------------------------------

void WsjcppPackageManager::printAuthors() {
    std::cout << "Authors (" << m_sName << ":" << m_sVersion << "): " << std::endl;
    for (int i = 0; i < m_vAuthors.size(); i++) {
        WsjcppPackageManagerAuthor author = m_vAuthors[i];
        std::cout << " - " << author.getFullAuthor() << std::endl;
    }
    std::cout << std::endl;
}

// ---------------------------------------------------------------------

void WsjcppPackageManager::printAuthorsTree() {
    std::string sAuthors = "";
    for (int i = 0; i < m_vAuthors.size(); i++) {
        if (sAuthors.size() > 0) {
            sAuthors += ", ";
        }
        sAuthors += m_vAuthors[i].getFullAuthor();
    }
    std::cout << "Authors (" << m_sName << ":" << m_sVersion << "): " << sAuthors << std::endl;

    // TODO
    recursive_printAuthorsTree(m_vDependencies);
}

// ---------------------------------------------------------------------

void WsjcppPackageManager::recursive_printAuthorsTree(std::vector<WsjcppPackageManagerDependence> &vDependencies) {
    for (int i = 0; i < vDependencies.size(); i++) {
        WsjcppPackageManagerDependence dep = vDependencies[i];
        std::string sInstalledDir = dep.getInstallationDir(); 

        if (WsjcppCore::dirExists(dep.getInstallationDir())) {
            WsjcppPackageManager subpkg(sInstalledDir, m_sDir, true);
            WsjcppLog::info(TAG, "Loading package '" + sInstalledDir + "'");
            if (subpkg.load()) {
                subpkg.printAuthorsTree();
            } else {
                WsjcppLog::err(TAG, "Could not load package.");
            }
        } else {
            WsjcppLog::err(TAG, "Not found installed dir: '" + sInstalledDir + "' for package: " + dep.getName() + ":" + dep.getVersion());
        }
    }
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::addAuthor(const std::string &sName, const std::string &sEmail) {
    bool bFoundAuthor = false;
    std::string sFullAuthor = sName + " <" + sEmail + ">";
    for (int i = 0; i < m_vAuthors.size(); i++) {
        WsjcppPackageManagerAuthor author = m_vAuthors[i];
        if (author.getFullAuthor() == sFullAuthor) {
            bFoundAuthor = true;
        }
    }
    if (bFoundAuthor) {
        WsjcppLog::err(TAG, "Author already exists");
        return false;
    }

    WsjcppPackageManagerAuthor newAuthor(sName, sEmail);
    m_vAuthors.push_back(newAuthor);

    if (!m_yamlPackageInfo.getRoot()->hasElement("authors")) {
        m_yamlPackageInfo.getRoot()->createElementArray("authors", false);
    }

    WsjcppYamlItem *pItem = m_yamlPackageInfo.getRoot()->getElement("authors");
    WsjcppYamlPlaceInFile pl;
    WsjcppYamlItem *pNewItemMap = new WsjcppYamlItem(pItem, pl, WsjcppYamlItemType::WSJCPP_YAML_ITEM_MAP);
    // pNewItem->setName(sName, false);
    // pItem->setElement(sName, pNewItem);
    pNewItemMap->setElementValue("name", false, sName, true);
    pNewItemMap->setElementValue("email", false, sEmail, true);
    pItem->appendElement(pNewItemMap);
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::removeAuthor(const std::string &sFullAuthor) {
    std::vector<WsjcppPackageManagerAuthor> vNewAuthors;
    for (int i = 0; i < m_vAuthors.size(); i++) {
        WsjcppPackageManagerAuthor author = m_vAuthors[i];
        if (author.getFullAuthor() != sFullAuthor) {
            vNewAuthors.push_back(author);
        }
    }
    if (vNewAuthors.size() != m_vAuthors.size()) {
        m_vAuthors.clear();
        for (int i = 0; i < vNewAuthors.size(); i++) {
            m_vAuthors.push_back(vNewAuthors[i]);
        }
        return true;
    }
    WsjcppLog::err(TAG, "Not found this author");
    return false;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::addResource(const std::string &sFilepath, const std::string &sPackAs) {
    for (int i = 0; i < m_vResourceFiles.size(); i++) {
        if (m_vResourceFiles[i].getFilepath() == sFilepath) {
            WsjcppLog::err(TAG, "Resource already added, '" + sFilepath + "'");
            return false; 
        }
    }

    if (!WsjcppCore::fileExists(sFilepath)) {
        WsjcppLog::err(TAG, "Resource file '" + sFilepath + "' did not found");
        return false;
    }
    WsjcppPackageManagerResourceFile resourceFile;
    resourceFile.setFilepath(sFilepath);
    resourceFile.setPackAs(sPackAs);
    resourceFile.setSha1(""); // TODO sha1 

    struct stat result;
    if (stat(sFilepath.c_str(), &result) == 0) {
        resourceFile.setFilesize(result.st_size);
        resourceFile.setModified(result.st_mtime);
    }

    updateAutogeneratedFiles_Resource(resourceFile);

    m_vResourceFiles.push_back(resourceFile);

    if (!m_yamlPackageInfo.getRoot()->hasElement("resources")) {
        m_yamlPackageInfo.getRoot()->createElementArray("resources", false);
    }
    WsjcppYamlItem *pItem = m_yamlPackageInfo.getRoot()->getElement("resources");

    WsjcppYamlPlaceInFile pl;
    WsjcppYamlItem *pNewItemMap = new WsjcppYamlItem(pItem, pl, WsjcppYamlItemType::WSJCPP_YAML_ITEM_MAP);
    pNewItemMap->setElementValue("filepath", false, resourceFile.getFilepath(), true);
    pNewItemMap->setElementValue("filesize", false, std::to_string(resourceFile.getFilesize()), false); // TODO redesign without std::to_string
    pNewItemMap->setElementValue("pack-as", false, resourceFile.getPackAs(), true);
    pNewItemMap->setElementValue("modified", false, std::to_string(resourceFile.getModified()), false); // TODO redesign without std::to_string
    pNewItemMap->setElementValue("sha1", false, resourceFile.getSha1(), true);
    pItem->appendElement(pNewItemMap);

    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::removeResource(const std::string &sFilepath) {

    if (!m_yamlPackageInfo.getRoot()->hasElement("resources")) {
        WsjcppLog::warn(TAG, "resources not found in wsjcpp.yml");
        return false;
    }
    WsjcppYamlItem *pResources = m_yamlPackageInfo.getRoot()->getElement("resources");
    int nLen = pResources->getLength();
    bool bFound = false;
    for (int i = 0; i < nLen; i++) {
        WsjcppYamlItem *pResource = pResources->getElement(i);
        if (pResource->getElement("filepath")->getValue() == sFilepath) {
            pResources->removeElement(i);
            bFound = true;
            break;
        }
    }
    if (nLen == 1 && bFound) {
        m_yamlPackageInfo.getRoot()->removeElement("resources");
    }

    std::string sRemovedFiles = " Removed files: \n"; 
    std::string sBaseFilename = generateResourceCppFileBasename(sFilepath);
    sBaseFilename = m_sDirResources + "/" + sBaseFilename;
    if (WsjcppCore::fileExists(sBaseFilename + ".h")) {
        WsjcppCore::removeFile(sBaseFilename + ".h");
        sRemovedFiles += "\n - " + sBaseFilename + ".h";
    } else {
        sRemovedFiles += "\n - not found: " + sBaseFilename + ".h";
    }
    if (WsjcppCore::fileExists(sBaseFilename + ".cpp")) {
        WsjcppCore::removeFile(sBaseFilename + ".cpp");
        sRemovedFiles += "\n - " + sBaseFilename + ".cpp";
    } else {
        sRemovedFiles += "\n - not found: " + sBaseFilename + ".cpp";
    }
    sRemovedFiles += "\n\n";
    std::cout << sRemovedFiles;

    std::vector<WsjcppPackageManagerResourceFile>::iterator it;
    for (it = m_vResourceFiles.begin(); it != m_vResourceFiles.end(); ++it) {
        if ((*it).getFilepath() == sFilepath) {
            m_vResourceFiles.erase(it);
            return true;
        }
    }

    WsjcppLog::err(TAG, "Not found this resource");
    return false;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::hasResource(const std::string &sFilepath) {
    if (!m_yamlPackageInfo.getRoot()->hasElement("resources")) {
        WsjcppLog::warn(TAG, "resources not found in wsjcpp.yml");
        return false;
    }
    WsjcppYamlItem *pResources = m_yamlPackageInfo.getRoot()->getElement("resources");
    int nLen = pResources->getLength();
    bool bFound = false;
    // TODO WsjcppYaml findArrayElementWhereHas("filepath", sValue);
    for (int i = 0; i < nLen; i++) {
        WsjcppYamlItem *pResource = pResources->getElement(i);
        if (pResource->getElement("filepath")->getValue() == sFilepath) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManager::detectTypeOfResource(const std::string &sFilepath) {
    std::string arrTextExt[] = {
        "js", "svg", "html", "conf", "sh",
        "yml", "txt", "gitignore", "h", "cpp", "cmake",
        "make", "hpp", "log"
    };
    int arrTextExtSize = sizeof(arrTextExt)/sizeof(arrTextExt[0]);
    std::string sFileExt = sFilepath.substr(sFilepath.find_last_of(".") + 1);
    sFileExt = WsjcppCore::toLower(sFileExt);
    
    for (int i = 0; i < arrTextExtSize; i++) {
        if (sFileExt == arrTextExt[i]) {
            return "text";
        }
    }
    return "binary";
}

// ---------------------------------------------------------------------

std::vector<WsjcppPackageManagerDistributionFile> WsjcppPackageManager::getListOfDistributionFiles() {
    return m_vDistributionFiles;
}

// ---------------------------------------------------------------------

std::vector<WsjcppPackageManagerDependence> WsjcppPackageManager::getListOfDependencies() {
    return m_vDependencies;
}

// ---------------------------------------------------------------------

std::vector<WsjcppPackageManagerUnitTest> WsjcppPackageManager::getListOfUnitTests() {
    return m_vUnitTests;
}

// ---------------------------------------------------------------------

std::vector<WsjcppPackageManagerSafeScriptingGenerate> WsjcppPackageManager::getListOfSafeScriptingGenerate() {
    std::vector<WsjcppPackageManagerSafeScriptingGenerate> vRet;

    // from current package
    std::vector<WsjcppPackageManagerDistributionFile> vFiles = this->getListOfDistributionFiles();
    for (int i = 0; i < vFiles.size(); i++) {
        WsjcppPackageManagerDistributionFile file = vFiles[i];
        // WsjcppLog::warn(TAG, file.getTargetFile());
        if (file.getType() == "safe-scripting-generate") {
            append(vRet, file.getSourceFile(), this->getName(), file.getTargetFile());
        }
    }

    std::vector<WsjcppPackageManagerDependence> vDeps = this->getListOfDependencies();
    for (int i = 0; i < vDeps.size(); i++) {
        WsjcppPackageManagerDependence dep = vDeps[i];
        std::string sInstallationDir = WsjcppCore::doNormalizePath(m_sDir + "/" + dep.getInstallationDir());
        WsjcppPackageManager pkgHold(sInstallationDir, this->getDir(), true);
        if (!pkgHold.load()) {
            WsjcppLog::err(TAG, "Could not load package from '" + sInstallationDir + "'");
            continue;
        }
        std::vector<WsjcppPackageManagerDistributionFile> vFilesDep = pkgHold.getListOfDistributionFiles();
        for (int n = 0; n < vFilesDep.size(); n++) {
            WsjcppPackageManagerDistributionFile file = vFilesDep[n];
            if (file.getType() == "safe-scripting-generate") {
                append(vRet, sInstallationDir + "/" + file.getTargetFile(), pkgHold.getName(), file.getTargetFile());
            }
        }
    }
    return vRet;
}

// ---------------------------------------------------------------------

std::vector<WsjcppPackageManagerOrigin> WsjcppPackageManager::getListOfOrigins() {
    return m_vOrigins;
}

// ---------------------------------------------------------------------

std::vector<WsjcppPackageManagerAuthor> WsjcppPackageManager::getListOfAuthors() {
    return m_vAuthors;
}

// ---------------------------------------------------------------------

std::vector<std::string> WsjcppPackageManager::getListOfKeywords() {
    return m_vKeywords;
}

// ---------------------------------------------------------------------

std::vector<WsjcppPackageManagerRepository> WsjcppPackageManager::getListOfRepositories() {
    return m_vRepositories;
}

// ---------------------------------------------------------------------

std::vector<WsjcppPackageManagerResourceFile> WsjcppPackageManager::getListOfResourceFiles() {
    return m_vResourceFiles;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManager::getName() {
    return m_sName;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManager::getVersion() {
    return m_sVersion;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::setVersion(const std::string& sVersion) {
    if (!this->validateVersionFormat(sVersion)) {
        WsjcppLog::err(TAG, "'version' has invalid format, try change to like 'v0.0.1'");
        return false;
    }
    m_sVersion = sVersion;
    m_yamlPackageInfo.getRoot()->setElementValue("version", false, m_sVersion, false);
    return true;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManager::getWsjcppVersion() {
    return m_sWsjcppVersion;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManager::getDescription() {
    return m_sDescription;
}


// ---------------------------------------------------------------------

std::string WsjcppPackageManager::getCMakeCxxStandard() {
    return m_sCMakeCxxStandard;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManager::getCMakeMinimumRequired() {
    return m_sCMakeMinimumRequired;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManager::getIssues() {
    return m_sIssues;
}

// ---------------------------------------------------------------------
// TODO move to core like convertCammelCaseToSnakCase
std::string WsjcppPackageManager::normalizeUnitTestName(const std::string &sUnitTestName, bool bSilent) {
    std::string sRet = ""; 
    for (int i = 0; i < sUnitTestName.size(); i++) {
        char c = sUnitTestName[i];
        if (i == 0 && c >= '0' && c <= '9') {
            if (!bSilent) {
                WsjcppLog::warn(TAG, std::string("First symbol could not be number"));
            }
        } else if (i == 0 && c >= 'a' && c <= 'z') {
            sRet += char(c - 32); // capitalize first char
        } else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            sRet += c;
        } else {
            if (!bSilent) {
                WsjcppLog::warn(TAG, std::string("Ignored symbol in UnitTest Name '") + c + "'");
            }
        }
    }
    return sRet;
}

// ---------------------------------------------------------------------
// TODO test for this
std::string WsjcppPackageManager::generateFilenameForUnitTest(const std::string &sUnitTestName) {
    std::string sName = normalizeUnitTestName(sUnitTestName, false);
    std::string sRet = "";
    for (int i = 0; i < sName.size(); i++) {
        char c = sUnitTestName[i];
        if (c >= 'A' && c <= 'Z') {
            c = char(c + 32);
            sRet += sRet.length() == 0 ? "" : "_";
            sRet += c;
        } else if (c >= 'a' && c <= 'z') {
            sRet += c;
        } else if (c >= '0' && c <= '9') {
            sRet += c;
        } else {
            WsjcppLog::warn(TAG, std::string("Ignored ") + c);
        }
    }
    return "unit_test_" + sRet;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::updateAutogeneratedFiles() {
    if (m_bHolded) {
        WsjcppLog::err(TAG, "Could not reinstall package when holded");
        return false;
    }

    if (!updateAutogeneratedFiles_CMakeListsTXT()) {
        return false;
    }

    if (!updateAutogeneratedFiles_UnitTests()) {
        return false;
    }

    if (!updateAutogeneratedFiles_Dockerfiles()) {
        return false;
    }

    if (!updateAutogeneratedFiles_Resources()) {
        return false;
    }

    return true;
}

// ---------------------------------------------------------------------

std::string WsjcppPackageManager::generateResourceCppFileBasename(const std::string &sFilepath) {
    std::string sFilenameNormalized = "";
    for (int i = 0; i < sFilepath.size(); i++) {
        char c = sFilepath[i];
        if (
            (c >= 'A' && c <= 'Z') 
            || (c >= 'a' && c <= 'z')
            || (c >= '0' && c <= '9')
        ) {
            sFilenameNormalized += c;
        } else {
            sFilenameNormalized += '_';
        }
    }
    std::string sMd5 = WsjcppHashes::md5_calc_hex(sFilepath);
    sMd5 = sMd5.substr(0,6);
    sFilenameNormalized += "_path" + sMd5;
    return sFilenameNormalized;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldVersion() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("version")) {
        WsjcppLog::err(TAG, "Missing required field 'version' in '" + m_sYamlFullpath + "'");
        return false;
    }
    m_sVersion = m_yamlPackageInfo["version"].getValue();
    if (!this->validateVersionFormat(m_sVersion)) {
        WsjcppLog::err(TAG, "Field 'version' has invalid format, try change to 'v0.0.1'");
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldCMakeMinimumRequired() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("cmake_minimum_required")) {
        WsjcppLog::err(TAG, "Missing required field 'cmake_minimum_required' in '" + m_sYamlFullpath + "'");
        return false;
    }
    // TODO: check cmake_version format
    m_sCMakeMinimumRequired = m_yamlPackageInfo["cmake_minimum_required"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldCMakeCxxStandard() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("cmake_cxx_standard")) {
        WsjcppLog::err(TAG, "Missing required field 'cmake_cxx_standard' in '" + m_sYamlFullpath + "'");
        return false;
    }
    // TODO: check cmake_cxx_standard format
    m_sCMakeCxxStandard = m_yamlPackageInfo["cmake_cxx_standard"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldName() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("name")) {
        WsjcppLog::err(TAG, "Missing required field 'name' in " + m_yamlPackageInfo.getRoot()->getForLogFormat());
        return false;
    }
    // TODO: check name format
    m_sName = m_yamlPackageInfo["name"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldDescription() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("description")) {
        WsjcppLog::err(TAG, "Missing required field 'description' in '" + m_sYamlFullpath + "'");
        return false;
    }
    m_sDescription = m_yamlPackageInfo["description"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldWsjcppVersion() {    
    if (!m_yamlPackageInfo.getRoot()->hasElement("wsjcpp_version")) {
        WsjcppLog::err(TAG, "Missing required field 'wsjcpp_version' in '" + m_sYamlFullpath + "'");
        return false;
    }
    m_sWsjcppVersion = m_yamlPackageInfo["wsjcpp_version"].getValue();
    // TODO version comparator 
    // if (nWsjcppVersion > m_nWsjcppVersion) {
        //   std::cout << "WARN: Please update your 'wsjcpp' to " << nWsjcppVersion << std::endl;
    // }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldIssues() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("issues")) {
        WsjcppLog::err(TAG, "Missing required field 'issues' in '" + m_sYamlFullpath + "'");
        return false;
    }
    m_sIssues = m_yamlPackageInfo["issues"].getValue();
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldKeywords() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("keywords")) {
        WsjcppLog::err(TAG, "Missing required field 'keywords' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WsjcppYamlItem itemKeywords = m_yamlPackageInfo["keywords"];
    int nLength = itemKeywords.getLength();
    for (int i = 0; i < nLength; i++) {
        std::string sKeyword = itemKeywords[i].getValue();
        m_vKeywords.push_back(sKeyword);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldAuthors() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("authors")) {
        WsjcppLog::err(TAG, "Missing required field 'authors' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WsjcppYamlItem itemAuthors = m_yamlPackageInfo["authors"];
    int nLength = itemAuthors.getLength();
    for (int i = 0; i < nLength; i++) {
        WsjcppYamlItem *pYamlAuthor = itemAuthors.getElement(i);
        WsjcppPackageManagerAuthor author;
        author.fromYAML(pYamlAuthor);
        m_vAuthors.push_back(author);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldDistribution() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("distribution")) {
        WsjcppLog::err(TAG, "Missing required field 'distribution' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WsjcppYamlItem itemDistribution = m_yamlPackageInfo["distribution"];
    int nLength = itemDistribution.getLength();
    for (int i = 0; i < nLength; i++) {
        WsjcppYamlItem *pYamlSource = itemDistribution.getElement(i);
        WsjcppPackageManagerDistributionFile source;
        source.fromYAML(pYamlSource, m_bHolded);
        m_vDistributionFiles.push_back(source);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldOrigins() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("origins")) {
        WsjcppLog::err(TAG, "Missing required field 'origins' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WsjcppYamlItem itemOrigins = m_yamlPackageInfo["origins"];
    int nLength = itemOrigins.getLength();
    for (int i = 0; i < nLength; i++) {
        WsjcppYamlItem *pYamlOrigins = itemOrigins.getElement(i);
        WsjcppPackageManagerOrigin origin;
        origin.fromYAML(pYamlOrigins);
        m_vOrigins.push_back(origin);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldDependencies() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("dependencies")) {
        WsjcppLog::err(TAG, "Missing required field 'dependencies' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WsjcppYamlItem itemDependencies = m_yamlPackageInfo["dependencies"];
    int nLength = itemDependencies.getLength();
    for (int i = 0; i < nLength; i++) {
        WsjcppYamlItem *pYamlDependence = itemDependencies.getElement(i);
        WsjcppPackageManagerDependence dependence;
        dependence.fromYAML(pYamlDependence);
        m_vDependencies.push_back(dependence);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldRepositories() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("repositories")) {
        WsjcppLog::err(TAG, "Missing required field 'repositories' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WsjcppYamlItem itemRepositories = m_yamlPackageInfo["repositories"];
    int nLength = itemRepositories.getLength();
    for (int i = 0; i < nLength; i++) {
        WsjcppYamlItem *pYamlRepository = itemRepositories.getElement(i);
        WsjcppPackageManagerRepository repository;
        repository.fromYAML(pYamlRepository);
        m_vRepositories.push_back(repository);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldResources() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("resources")) {
        // skip
        return true;
    }
    WsjcppYamlItem itemResourceFiles = m_yamlPackageInfo["resources"];
    int nLength = itemResourceFiles.getLength();
    for (int i = 0; i < nLength; i++) {
        WsjcppYamlItem *pYamlResourceFile = itemResourceFiles.getElement(i);
        WsjcppPackageManagerResourceFile resource;
        resource.fromYAML(pYamlResourceFile, m_bHolded);
        m_vResourceFiles.push_back(resource);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldUnitTests() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("unit-tests")) {
        WsjcppLog::err(TAG, "Missing required field 'unit-tests' in '" + m_sYamlFullpath + "'");
        return false;
    }

    WsjcppYamlItem itemUnitTests = m_yamlPackageInfo["unit-tests"];
    if (!itemUnitTests.hasElement("cases")) {
        WsjcppLog::err(TAG, "Missing required field 'cases' in '" + m_sYamlFullpath + "' " + itemUnitTests.getForLogFormat());
        return false;
    }
    WsjcppYamlItem itemCases = itemUnitTests["cases"];

    int nLength = itemCases.getLength();
    for (int i = 0; i < nLength; i++) {
        WsjcppYamlItem *pYamlCase = itemCases.getElement(i);
        WsjcppPackageManagerUnitTest unitTest;
        unitTest.fromYAML(pYamlCase);
        m_vUnitTests.push_back(unitTest);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldRequiredLibraries() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("required-libraries")) {
        WsjcppLog::err(TAG, "Missing required field 'required-libraries' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WsjcppYamlItem itemRequiredLibraries = m_yamlPackageInfo["required-libraries"];
    int nLength = itemRequiredLibraries.getLength();
    for (int i = 0; i < nLength; i++) {
        WsjcppYamlItem *pYamlRequredLibrary = itemRequiredLibraries.getElement(i);
        std::string sRequiredLibrary = pYamlRequredLibrary->getValue();
        m_sRequiredLibraries.push_back(sRequiredLibrary);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::readFieldRequiredPkgConfig() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("required-pkg-config")) {
        WsjcppLog::err(TAG, "Missing required field 'required-pkg-config' in '" + m_sYamlFullpath + "'");
        return false;
    }
    WsjcppYamlItem itemRequiredPkgConfig = m_yamlPackageInfo["required-pkg-config"];
    int nLength = itemRequiredPkgConfig.getLength();
    for (int i = 0; i < nLength; i++) {
        WsjcppYamlItem *pYamlRequredPkgConfig = itemRequiredPkgConfig.getElement(i);
        std::string sRequiredPkgConfig = pYamlRequredPkgConfig->getValue();
        m_sRequiredPkgConfig.push_back(sRequiredPkgConfig);
    }
    return true;
}

// ---------------------------------------------------------------------

void WsjcppPackageManager::removeDependenciesFilesSafe(const WsjcppPackageManagerDependence &dep) {
    WsjcppPackageManager pkgDep(dep.getInstallationDir(), m_sDir, true);
    if (pkgDep.load()) {
        std::vector<WsjcppPackageManagerDistributionFile> vFiles = pkgDep.getListOfDistributionFiles();
        int nRemovedFiles = 0;
        for (int i = 0; i < vFiles.size(); i++) {
            WsjcppPackageManagerDistributionFile file = vFiles[i];
            std::string sFilePath = dep.getInstallationDir() + "/" + file.getTargetFile();
            if (!WsjcppCore::fileExists(sFilePath)) {
                WsjcppLog::info(TAG, "Did not found file '" + sFilePath + "'");
            } else {
                std::string sContent;
                WsjcppCore::readTextFile(sFilePath, sContent);
                std::string sSha1 = WsjcppHashes::sha1_calc_hex(sContent);
                if (sSha1 != file.getSha1()) {
                    WsjcppLog::warn(TAG, "Could not remove file '" + sFilePath + "', because maybe has local important changes. "
                        "\r\n  sha1 expected '" + file.getSha1() + "', but got '" + sSha1 + "'");
                } else {
                    if (WsjcppCore::removeFile(sFilePath)) {
                        nRemovedFiles++;
                        WsjcppLog::ok(TAG, "Successfully removed '" + sFilePath + "'");
                    }
                }
            }
        }
        if (nRemovedFiles == vFiles.size()) {
            std::string sFilePath = dep.getInstallationDir() + "/wsjcpp.hold.yml";
            if (WsjcppCore::removeFile(sFilePath)) {
                nRemovedFiles++;
                WsjcppLog::ok(TAG, "Successfully removed '" + sFilePath + "'");
            } else {
                WsjcppLog::warn(TAG, "Could not remove '" + sFilePath + "'");
            }

            if (WsjcppCore::removeFile(dep.getInstallationDir())) {
                WsjcppLog::ok(TAG, "Successfully removed directory '" + dep.getInstallationDir() + "'");
            } else {
                WsjcppLog::warn(TAG, "Could not remove directory '" + dep.getInstallationDir() + "'");
            }
        }
    }
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::updateAutogeneratedFiles_CMakeListsTXT() {
    std::string sCMakeListsTXT = ""
        "# Automaticly generated by wsjcpp@" + m_sWsjcppCurrentVersion + "\n"
        "cmake_minimum_required(VERSION " + m_sCMakeMinimumRequired + ")\n"
        "\n"
        "add_definitions(-DWSJCPP_APP_VERSION=\"" + m_sVersion + "\")\n"
        "add_definitions(-DWSJCPP_APP_NAME=\"" + m_sName + "\")\n"
        "\n"
        "if (${CMAKE_SYSTEM_NAME} MATCHES \"Darwin\")\n"    
        "    set(MACOSX TRUE)\n"
        "endif()\n"
        "\n"
        "set(CMAKE_CXX_STANDARD " + m_sCMakeCxxStandard + ")\n"
        "\n"
        "set (WSJCPP_LIBRARIES \"\")\n"
        "set (WSJCPP_INCLUDE_DIRS \"\")\n"
        "set (WSJCPP_SOURCES \"\")\n"
        "\n"
        "find_package(Threads REQUIRED)\n"
        "list (APPEND WSJCPP_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})\n"
        "\n"
    ;

    for (int i = 0; i < m_vDependencies.size(); i++) {
        WsjcppPackageManagerDependence dep = m_vDependencies[i];
        std::string sInstDir = dep.getInstallationDir();
        WsjcppPackageManager pkg(dep.getInstallationDir(), m_sDir, true);
        if (pkg.load()) {
            sCMakeListsTXT += 
                "# " + pkg.getName() + ":" + pkg.getVersion() + "\n"
                "list (APPEND WSJCPP_INCLUDE_DIRS \"" + sInstDir + "/\")\n";
            std::vector<WsjcppPackageManagerDistributionFile> vFiles = pkg.getListOfDistributionFiles();
            for (int i = 0; i < vFiles.size(); i++) {
                WsjcppPackageManagerDistributionFile file = vFiles[i];
                if (file.getType() == "source-code") {
                    sCMakeListsTXT += "list (APPEND WSJCPP_SOURCES \"" + sInstDir + "/" + file.getTargetFile() + "\")\n";
                }
            }
        }
        sCMakeListsTXT += "\n";
    }
    
    if (m_vResourceFiles.size() > 0) {
        sCMakeListsTXT += 
            "# resources.wsjcpp\n"
            "list (APPEND WSJCPP_INCLUDE_DIRS \"./" + m_sDirnameResources + "/\")\n";

        for (int i = 0; i < m_vResourceFiles.size(); i++) {
            std::string sFilepath = m_vResourceFiles[i].getFilepath();
            std::string sFilepathBase = generateResourceCppFileBasename(sFilepath);
            sCMakeListsTXT += "list (APPEND WSJCPP_SOURCES \"./" + m_sDirnameResources + "/" + sFilepathBase + ".h\")\n";
            sCMakeListsTXT += "list (APPEND WSJCPP_SOURCES \"./" + m_sDirnameResources + "/" + sFilepathBase + ".cpp\")\n";
        }
        sCMakeListsTXT += "\n";
    }

    if (m_sRequiredLibraries.size() > 0) {
        sCMakeListsTXT += "# required-libraries\n";
        for (int i = 0; i < m_sRequiredLibraries.size(); i++) {
            std::string sLibrary = m_sRequiredLibraries[i];
            sCMakeListsTXT += "list (APPEND WSJCPP_LIBRARIES \"-l" + sLibrary + "\")\n";
        }
        sCMakeListsTXT += "\n";
    }
    
    if (m_sRequiredPkgConfig.size() > 0) {
        sCMakeListsTXT += "# required-pkg-config\n";
        for (int i = 0; i < m_sRequiredPkgConfig.size(); i++) {
            std::string sPkgConfig = m_sRequiredPkgConfig[i];
            sCMakeListsTXT += 
                "## " + sPkgConfig + "\n"
                "FIND_PACKAGE(" + sPkgConfig + ")\n"
                "IF(" + sPkgConfig + "_FOUND)\n"
                "   list (APPEND WSJCPP_INCLUDE_DIRS ${" + sPkgConfig + "_INCLUDE_DIR})\n"
                "   list (APPEND WSJCPP_LIBRARIES ${" + sPkgConfig + "_LIBRARIES})\n"
                "ELSE(" + sPkgConfig + "_FOUND)\n"
                "   MESSAGE(FATAL_ERROR \"Could not find the " + sPkgConfig + " library and development files.\")\n"
                "ENDIF(" + sPkgConfig + "_FOUND)\n";
        }
        sCMakeListsTXT += "\n";
    }

    WsjcppCore::writeFile("./src.wsjcpp/CMakeLists.txt", sCMakeListsTXT);
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::updateAutogeneratedFiles_Dockerfiles() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("docker")) {
        // Not need if docker section not defined
        return true;
    }

    if (!updateAutogeneratedFiles_Dockerfile_for_build()) {
        return false;
    }

    if (!updateAutogeneratedFiles_Dockerfile_for_release()) {
        return false;
    }

    if (!updateAutogeneratedFiles_Dockerfile_release()) {
        return false;
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::updateAutogeneratedFiles_Dockerfile_for_build() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("docker")) {
        // Not need if docker section not defined
        return true;
    }

    std::string sContent = 
        "# Automaticly generated by wsjcpp@" + m_sWsjcppCurrentVersion + "\n"
        "# for-build " + m_sName + ":" + m_sVersion + "\n"
        "FROM debian:10\n"
    ;

    std::vector<std::string> vInstallPackagesBuild = {"make", "cmake", "gcc", "g++", "pkg-config" };
    // TODO check equals and from dependencies 
    for (int i = 0; i < m_sDockerPackagesBuild.size(); i++) {
        vInstallPackagesBuild.push_back(m_sDockerPackagesBuild[i]);
    }
    // TODO: packages-build
    sContent += 
        "# install build requiremenets\n"
        "RUN apt-get update && apt-get install -y \\\n";
    for (int i = 0; i < vInstallPackagesBuild.size(); i++) {
        sContent += "  " + vInstallPackagesBuild[i] + "\\\n";
    }
    sContent += 
        "\n"
        "RUN apt-get clean\n"
        "\n"
        "WORKDIR /root/sources\n"
    ;

    if (!WsjcppCore::dirExists("./docker.for-build")) {
        WsjcppCore::makeDir("./docker.for-build");
    }
    WsjcppCore::writeFile("./docker.for-build/Dockerfile", sContent);
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::updateAutogeneratedFiles_Dockerfile_for_release() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("docker")) {
        // Not need if docker section not defined
        return true;
    }

    std::string sContent = 
        "# Automaticly generated by wsjcpp@" + m_sWsjcppCurrentVersion + "\n"
        "# for-release " + m_sName + ":" + m_sVersion + "\n"
        "FROM debian:10\n";

    std::vector<std::string> vInstallPackagesRelease = {"locales", "libpthread-stubs0-dev" };
    // TODO check equals and from dependencies 
    for (int i = 0; i < m_sDockerPackagesRelease.size(); i++) {
        vInstallPackagesRelease.push_back(m_sDockerPackagesRelease[i]);
    }
    // TODO: packages-build
    sContent += 
        "# install release requiremenets\n"
        "RUN apt-get update && apt-get install -y \\\n";
    for (int i = 0; i < vInstallPackagesRelease.size(); i++) {
        sContent += "  " + vInstallPackagesRelease[i] + "\\\n";
    }
    sContent += 
        "\n"
        "RUN sed -i -e \"s/# en_US.UTF-8 UTF-8/en_US.UTF-8 UTF-8/\" /etc/locale.gen && \\\n"
        "  echo 'LANG=\"en_US.UTF-8\"'>/etc/default/locale && \\\n"
        "  dpkg-reconfigure --frontend=noninteractive locales && \\\n"
        "  update-locale LANG=en_US.UTF-8\n"
        "\n"
        "RUN apt-get clean\n"
        "\n"
        "WORKDIR /root/\n";

    if (!WsjcppCore::dirExists("./docker.for-release")) {
        WsjcppCore::makeDir("./docker.for-release");
    }
    WsjcppCore::writeFile("./docker.for-release/Dockerfile", sContent);
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::updateAutogeneratedFiles_Dockerfile_release() {
    if (!m_yamlPackageInfo.getRoot()->hasElement("docker")) {
        // Not need if docker section not defined
        return true;
    }
    WsjcppYamlItem *pItem = m_yamlPackageInfo.getRoot()->getElement("docker");
    if (!pItem->hasElement("release")) {
        // Do nothing if docker/release section not defined
        return true;
    }

    // if has docker/release
    std::string sContent = 
        "# Automaticly generated by wsjcpp@" + m_sWsjcppCurrentVersion + "\n"
        "# for-release " + m_sName + ":" + m_sVersion + "\n"
        "FROM " + m_sName + "-for-build:latest\n"
        "\n"
        "COPY . /root/sources\n"
        "RUN mkdir -p tmp.docker && cd tmp.docker && cmake .. && make\n"
        "\n"
        "FROM " + m_sName + "-for-release:latest\n"
        "\n";

        // TODO labels
        // LABEL "maintainer"="FreeHackQuest Team <freehackquest@gmail.com>"
        // LABEL "repository"="https://github.com/freehackquest/fhq-docker-build"
    sContent += 
        "COPY --from=0 /root/sources/" + m_sName + " /usr/bin/" + m_sName + "\n";
    
    // TODO expose-ports 
    // EXPOSE 1234 4613 7080
    // TODO command
    // CMD wsjcpp start

    WsjcppCore::writeFile("./Dockerfile", sContent);
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::updateAutogeneratedFiles_UnitTests() {
    std::string sUnitTestsDir = "./unit-tests.wsjcpp";
    if (!WsjcppCore::dirExists(sUnitTestsDir)) {
        WsjcppCore::makeDir(sUnitTestsDir);
    }
    if (!WsjcppCore::dirExists(sUnitTestsDir)) {
        WsjcppLog::err(TAG, "Could not create " + sUnitTestsDir + " directory");
        return false;
    }
    
    std::string sCMakeListsCustomTXTPath = sUnitTestsDir + "/CMakeLists.user-custom.txt";
    if (!WsjcppCore::fileExists(sCMakeListsCustomTXTPath)) {
        WsjcppCore::writeFile(sCMakeListsCustomTXTPath, "## You can here write some custom includes\n");
    }

    // TODO from resources
    std::string sGitignore = 
        "tmp/*\n"
        "logs/*\n"
        "unit-tests\n"
        ".wsjcpp/*\n"
        "\n"
        "# Vim temp files\n"
        "*.swp\n"
    ;
        
    WsjcppCore::writeFile(sUnitTestsDir + "/.gitignore", sGitignore);
    WsjcppCore::writeFile(sUnitTestsDir + "/build_simple.sh", this->getSampleForBuildSimpleSh());

    std::string sCMakeListsTXT = ""
        "# Automaticly generated by wsjcpp@" + m_sWsjcppCurrentVersion + "\n"
        "cmake_minimum_required(VERSION " + m_sCMakeMinimumRequired + ")\n"
        "\n"
        "project(unit-tests C CXX)\n"
        "add_definitions(-DWSJCPP_APP_VERSION=\"ut-" + m_sVersion + "\")\n"
        "add_definitions(-DWSJCPP_APP_NAME=\"unit-tests-" + m_sName + "\")\n"
        "\n"
        "if (${CMAKE_SYSTEM_NAME} MATCHES \"Darwin\")\n"    
        "    set(MACOSX TRUE)\n"
        "endif()\n"
        "\n"
        "set(CMAKE_CXX_STANDARD " + m_sCMakeCxxStandard + ")\n"
        "set(EXECUTABLE_OUTPUT_PATH ${unit-tests_SOURCE_DIR})\n"
        "\n"
        "set (WSJCPP_LIBRARIES \"\")\n"
        "set (WSJCPP_INCLUDE_DIRS \"\")\n"
        "set (WSJCPP_SOURCES \"\")\n"
        "\n"
        "find_package(Threads REQUIRED)\n"
        "list (APPEND WSJCPP_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})\n"
        "\n"
    ;

    for (int i = 0; i < m_vDependencies.size(); i++) {
        WsjcppPackageManagerDependence dep = m_vDependencies[i];
        std::string sInstDir = dep.getInstallationDir();
        WsjcppPackageManager pkg(dep.getInstallationDir(), m_sDir, true);
        if (pkg.load()) {
            sCMakeListsTXT += 
                "# " + pkg.getName() + ":" + pkg.getVersion() + "\n"
                "list (APPEND WSJCPP_INCLUDE_DIRS \""
                    + WsjcppCore::doNormalizePath("../" + sInstDir + "/") 
                    + "\")\n";
            std::vector<WsjcppPackageManagerDistributionFile> vFiles = pkg.getListOfDistributionFiles();
            for (int i = 0; i < vFiles.size(); i++) {
                WsjcppPackageManagerDistributionFile file = vFiles[i];
                if (file.getType() == "source-code" || file.getType() == "unit-tests") {
                    sCMakeListsTXT += "list (APPEND WSJCPP_SOURCES \""
                        + WsjcppCore::doNormalizePath("../" + sInstDir + "/" + file.getTargetFile()) 
                        + "\")\n";
                }
            }
        }
        sCMakeListsTXT += "\n";
    }

    sCMakeListsTXT += 
        "# " + m_sName + ":" + m_sVersion + "\n"
        "list (APPEND WSJCPP_INCLUDE_DIRS \"../src\")\n";
    for (int i = 0; i < m_vDistributionFiles.size(); i++) {
        WsjcppPackageManagerDistributionFile file = m_vDistributionFiles[i];
        if (file.getType() == "source-code" || file.getType() == "unit-tests") {
            sCMakeListsTXT += "list (APPEND WSJCPP_SOURCES \""
                + WsjcppCore::doNormalizePath("../" + file.getSourceFile())
                + "\")\n";
        }
    }

    // include resources to unit-tests
    if (m_vResourceFiles.size() > 0) {
        sCMakeListsTXT += 
            "\n# resources.wsjcpp\n"
            "list (APPEND WSJCPP_INCLUDE_DIRS \"../" + m_sDirnameResources + "/\")\n";

        for (int i = 0; i < m_vResourceFiles.size(); i++) {
            std::string sFilepath = m_vResourceFiles[i].getFilepath();
            std::string sFilepathBase = generateResourceCppFileBasename(sFilepath);
            sCMakeListsTXT += "list (APPEND WSJCPP_SOURCES \"../" + m_sDirnameResources + "/" + sFilepathBase + ".h\")\n";
            sCMakeListsTXT += "list (APPEND WSJCPP_SOURCES \"../" + m_sDirnameResources + "/" + sFilepathBase + ".cpp\")\n";
        }
    }

    sCMakeListsTXT += 
        "\n"
        "# unit-tests\n"
        "list (APPEND WSJCPP_INCLUDE_DIRS \"src\")\n";

    // list of unit-tests files
    for (int i = 0; i < m_vUnitTests.size(); i++) {
        WsjcppPackageManagerUnitTest ut = m_vUnitTests[i];
        std::string sUnitTestName = ut.getName();
        if (!ut.isEnabled()) {
            WsjcppLog::warn(TAG, "Ignored '" + sUnitTestName + "' - unit-test disabled");
            continue;
        }
        std::string sName = normalizeUnitTestName(sUnitTestName, false);
        std::string sBaseName = this->generateFilenameForUnitTest(sName);
        std::string sFileSource = "./unit-tests.wsjcpp/src/" + sBaseName + ".cpp";

        if (WsjcppCore::fileExists(sFileSource)) {
            sCMakeListsTXT += "list (APPEND WSJCPP_SOURCES \""
                + WsjcppCore::doNormalizePath("../" + sFileSource)
                + "\")\n";
        } else {
            WsjcppLog::warn(TAG, "Ignored '" + sFileSource + "' - file did not exists");
        }
    }
    sCMakeListsTXT += "\n";

    if (m_sRequiredLibraries.size() > 0) {
        sCMakeListsTXT += "# required-libraries\n";
        for (int i = 0; i < m_sRequiredLibraries.size(); i++) {
            std::string sLibrary = m_sRequiredLibraries[i];
            sCMakeListsTXT += "list (APPEND WSJCPP_LIBRARIES \"-l" + sLibrary + "\")\n";
        }
        sCMakeListsTXT += "\n";
    }
    
    if (m_sRequiredPkgConfig.size() > 0) {
        sCMakeListsTXT += "# required-pkg-config\n";
        for (int i = 0; i < m_sRequiredPkgConfig.size(); i++) {
            std::string sPkgConfig = m_sRequiredPkgConfig[i];
            sCMakeListsTXT += 
                "############################\n"
                "## " + sPkgConfig + "\n"
                "FIND_PACKAGE(" + sPkgConfig + ")\n"
                "IF(" + sPkgConfig + "_FOUND)\n"
                "   list (APPEND WSJCPP_INCLUDE_DIRS ${" + sPkgConfig + "_INCLUDE_DIR})\n"
                "   list (APPEND WSJCPP_LIBRARIES ${" + sPkgConfig + "_LIBRARIES})\n"
                "ELSE(" + sPkgConfig + "_FOUND)\n"
                "   MESSAGE(FATAL_ERROR \"Could not find the " + sPkgConfig + " library and development files.\")\n"
                "ENDIF(" + sPkgConfig + "_FOUND)\n"
                "############################\n\n"
            ;
        }
        sCMakeListsTXT += "\n";
    }

    sCMakeListsTXT += "include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.user-custom.txt)\n\n";

    sCMakeListsTXT += 
        "\n"
        "include_directories(${WSJCPP_INCLUDE_DIRS})\n"
        "\n"
        "add_executable (\"unit-tests\" ${WSJCPP_SOURCES})\n"
        "\n"
        "target_link_libraries(\"unit-tests\" -lpthread ${WSJCPP_LIBRARIES} )\n"
        "\n\n"
    ;

    WsjcppCore::writeFile(sUnitTestsDir + "/CMakeLists.txt", sCMakeListsTXT);
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::updateAutogeneratedFiles_Resource(const WsjcppPackageManagerResourceFile &resFile) {
    if (!WsjcppCore::dirExists(m_sDirResources)) {
        WsjcppCore::makeDir(m_sDirResources);
    }
    std::string sResourcesLog = "Resources files: \n"; 
    std::string sFilenameNormalized = generateResourceCppFileBasename(resFile.getFilepath());
    std::string sClassName = "RES_" + sFilenameNormalized;
    std::string sHeaderContent = 
        "// automaticly generated by wsjcpp:" + getVersion() + "\n"
        "\n"
        "#include <wsjcpp_core.h>\n"
        "\n"
        "class " + sClassName + " : public WsjcppResourceFile { \n"
        "    public:\n"
        "        virtual const std::string &getFilename() const override;\n"
        "        virtual const std::string &getPackAs() const override;\n"
        "        virtual int getBufferSize() const override;\n"
        "        virtual const char *getBuffer() const override;\n"
        "};\n"
        "\n"
    ;
    std::string sHeaderFilepath = m_sDirResources + "/" + sFilenameNormalized + ".h";
    if (WsjcppCore::fileExists(sHeaderFilepath)) {
        sResourcesLog += "\n - updated: " + sHeaderFilepath;
    } else {
        sResourcesLog += "\n - generated: " + sHeaderFilepath;
    }
    
    WsjcppCore::writeFile(sHeaderFilepath, sHeaderContent);

    char *pBuffer = nullptr;
    int nBufferSize = 0;
    if (!WsjcppCore::readFileToBuffer(resFile.getFilepath(), &pBuffer, nBufferSize)) {
        WsjcppLog::err(TAG, "Could not read file '" + resFile.getFilepath() + "'");
        return false;
    }

    std::string sSourceContent = 
        "// automaticly generated by wsjcpp:" + getVersion() + "\n"
        "\n"
        "#include \"" + sFilenameNormalized + ".h\"\n"
        "\n"
        "REGISTRY_WSJCPP_RESOURCE_FILE(" + sClassName + ")\n"
        "\n"
        "const std::string &" + sClassName + "::getFilename() const {\n"
        "    static const std::string s = \"" + resFile.getFilepath() + "\";\n"
        "    return s;\n"
        "}\n"
        "// ---------------------------------------------------------------------\n"
        "\n"
        "const std::string &" + sClassName + "::getPackAs() const {\n"
        "    static const std::string s = \"" + resFile.getPackAs() + "\";\n"
        "    return s;\n"
        "}\n"
        "// ---------------------------------------------------------------------\n"
        "\n"
        "int " + sClassName + "::getBufferSize() const {\n"
        "    return " + std::to_string(nBufferSize) + ";\n"
        "}\n"
        "\n"
        "// ---------------------------------------------------------------------\n"
        "\n"
    ;

    if (resFile.getPackAs() == "binary") {
        sSourceContent += 
            "const char *" + sClassName + "::getBuffer() const {\n"
            "    static const unsigned char b[" + std::to_string(nBufferSize) + "] = {";
        
        char const arrHexChars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
        for (int i = 0; i < nBufferSize; i++) {
            if (i != 0) {
                sSourceContent += ", ";
            }
            if (i % 16 == 0) {
                sSourceContent += "\n        ";
            }
            char c = pBuffer[i];
            sSourceContent += "0x";
            sSourceContent += arrHexChars[(c & 0xF0 ) >> 4];
            sSourceContent += arrHexChars[(c & 0x0F ) >> 0];
        }
        sSourceContent += 
            "\n"
            "    };\n"
            "    return (const char*)b;\n"
            "} //::buffer() \n"
            "\n";
    }
    
    if (resFile.getPackAs() == "text") {
        sSourceContent += 
            "const char *" + sClassName + "::getBuffer() {\n"
            "    static const std::string sRet = \"\" // size: " + std::to_string(nBufferSize) + "\n";
        
        sSourceContent += "        \"";
        for (int i = 0; i < nBufferSize; i++) {
            char c = pBuffer[i];
            if (c == '"') {
                sSourceContent += "\\\"";
            } else if (c == '\\') {
                sSourceContent += "\\\\";
            } else if (c == '\n') {
                sSourceContent += "\\n\"\n        \"";
            } else {
                sSourceContent += c;
            }
        }
        sSourceContent += "\"\n";
        sSourceContent += 
            "    ;\n"
            "    return sRet.c_str();\n"
            "} //::buffer() \n"
            "\n";
    }

    std::string sSourceFilepath = m_sDirResources + "/" + sFilenameNormalized + ".cpp";
    if (WsjcppCore::fileExists(sSourceFilepath)) {
        sResourcesLog += "\n - updated: " + sSourceFilepath;
    } else {
        sResourcesLog += "\n - generated: " + sSourceFilepath;
    }

    WsjcppCore::writeFile(sSourceFilepath, sSourceContent);
    sResourcesLog += "\n\n";
    std::cout << sResourcesLog;
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::updateAutogeneratedFiles_Resources() {
    WsjcppLog::warn(TAG, "updateAutogeneratedFiles_Resources Not implemented"); // TODO
    return true;
}

// ---------------------------------------------------------------------
/*
bool WsjcppPackageManager::updateAutogenerateFileUnitTestHeader(const std::string &sUnitTestName) {
    std::string sName = normalizeUnitTestName(sUnitTestName, false);
    if (sName != sUnitTestName) {
        WsjcppLog::warn(TAG, "UnitTest name was normalized '" + sUnitTestName + "' -> '" + sName + "'");
    }
    if (!WsjcppCore::dirExists("./unit-tests.wsjcpp")) {
        WsjcppCore::makeDir("./unit-tests.wsjcpp");
    }
    if (!WsjcppCore::dirExists("./unit-tests.wsjcpp/src/")) {
        WsjcppCore::makeDir("./unit-tests.wsjcpp/src/");
    }
    if (!WsjcppCore::dirExists("./unit-tests.wsjcpp/src/")) {
        WsjcppLog::err(TAG, "Directory does not exists './unit-tests.wsjcpp/src/'");
        return false;
    }
    std::string sBaseName = this->generateFilenameForUnitTest(sName);
    std::string sFileHeader = "./unit-tests.wsjcpp/src/" + sBaseName + ".h";
    if (WsjcppCore::fileExists(sFileHeader)) {
        WsjcppLog::err(TAG, "File already exists: '" + sFileHeader + "'");
        return false;
    } else {
        std::string sDefine = WsjcppCore::toUpper(sBaseName + "_H");
        std::string sContent = ""
            "#ifndef " + sDefine + "\n"
            "#define " + sDefine + "\n"
            "\n"
            "#include <wsjcpp_unit_tests.h>\n"
            "\n"
            "// Description: TODO\n"
            "class UnitTest" + sName + " : public WsjcppUnitTestBase {\n"
            "    public:\n"
            "        UnitTest" + sName + "();\n"
            "        virtual void init();\n"
            "        virtual bool run();\n"
            "};\n"
            "\n"
            "#endif // " + sDefine + "\n";
        WsjcppCore::writeFile(sFileHeader, sContent);
    }
    return true;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::updateAutogenerateFileUnitTestSource(const std::string &sUnitTestName) {
    std::string sName = normalizeUnitTestName(sUnitTestName, false);
    if (sName != sUnitTestName) {
        WsjcppLog::warn(TAG, "UnitTest name was normalized '" + sUnitTestName + "' -> '" + sName + "'");
    }
    if (!WsjcppCore::dirExists("./unit-tests.wsjcpp")) {
        WsjcppCore::makeDir("./unit-tests.wsjcpp");
    }
    if (!WsjcppCore::dirExists("./unit-tests.wsjcpp/src/")) {
        WsjcppCore::makeDir("./unit-tests.wsjcpp/src/");
    }
    if (!WsjcppCore::dirExists("./unit-tests.wsjcpp/src/")) {
        WsjcppLog::err(TAG, "Directory does not exists './unit-tests.wsjcpp/src/'");
        return false;
    }

    std::string sBaseName = this->generateFilenameForUnitTest(sName);
    std::string sFileSource = "./unit-tests.wsjcpp/src/" + sBaseName + ".cpp";
    if (WsjcppCore::fileExists(sFileSource)) {
        WsjcppLog::err(TAG, "File already exists: '" + sFileSource + "'");
        return false;
    } else {
        std::string sContent = ""
            "#include \"" + sBaseName + ".h\"\n"
            "#include <vector>\n"
            "#include <wsjcpp_core.h>\n"
            // TODO include add current headers
            "\n"
            "REGISTRY_WSJCPP_UNIT_TEST(UnitTest" + sName + ")\n"
            "\n"
            "UnitTest" + sName + "::UnitTest" + sName + "()\n"
            "    : WsjcppUnitTestBase(\"UnitTest" + sName + "\") {\n"
            "}\n"
            "\n"
            "// ---------------------------------------------------------------------\n"
            "\n"
            "void UnitTest" + sName + "::init() {\n"
            "    // nothing\n"
            "}\n"
            "\n"
            "// ---------------------------------------------------------------------\n"
            "\n"
            "bool UnitTest" + sName + "::run() {\n"
            "    bool bTestSuccess = true;\n"
            "    compareB(bTestSuccess, \"Not implemented\", true, false);\n"
            "    return bTestSuccess;\n"
            "}\n";
        
        WsjcppCore::writeFile(sFileSource, sContent);
    }
    return true;
}
*/
// ---------------------------------------------------------------------

std::string WsjcppPackageManager::getSampleForBuildSimpleSh() {
    WsjcppResourceFile *pFile = WsjcppResourcesManager::get("./build_simple.sh");
    if (pFile != nullptr) {
        std::string sBuildSipleSh(pFile->getBuffer(), pFile->getBufferSize());
        return sBuildSipleSh;
    }
    WsjcppLog::err(TAG, "Not found ./build_simple.sh in resources");
    return "";
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::validateVersionFormat(const std::string &sVersion) {
    std::regex rxVersion("v\\d*\\.\\d*\\.\\d*");
    if (std::regex_match(sVersion, rxVersion)) {
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------

bool WsjcppPackageManager::append(
    std::vector<WsjcppPackageManagerSafeScriptingGenerate> &vRet,
    const std::string &sSourceFile,
    const std::string &sModuleFile,
    const std::string &sTargetName
) {
    WsjcppPackageManagerSafeScriptingGenerate gen;
    gen.setModuleName(sModuleFile);
    gen.setFullPath(sSourceFile);
    std::vector<std::string> vSplit = WsjcppCore::split(sTargetName, ".");
    if (vSplit.size() != 3) {
        WsjcppLog::err(TAG, "Wrong script name: '" + sTargetName + "' must like 'generate.ScriptName.wsjcpp-script'");
        return false;
    } else {
        if (vSplit[0] != "generate") {
            WsjcppLog::err(TAG, "Wrong script name: '" + sTargetName + "' (left part must be 'generate.*')");
            return false;
        } else if (vSplit[2] != "wsjcpp-script") {
            WsjcppLog::err(TAG, "Wrong script name: '" + sTargetName + "' (right part must be '*.wsjcpp-script')");
            return false;
        } else {
            gen.setName(vSplit[1]);
            vRet.push_back(gen);
            return true;
        }
    }
    return false;
}