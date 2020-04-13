
#include "argument_processor_resources.h"
#include <wsjcpp_core.h>
#include <wsjcpp_package_manager.h>
#include <wsjcpp_hashes.h>
#include <sys/types.h>
#include <sys/stat.h>

// ---------------------------------------------------------------------
// ArgumentProcessorResources

ArgumentProcessorResources::ArgumentProcessorResources() 
: WsjcppArgumentProcessor({"resources", "res"}, "Pack files to c++ code") {
    TAG = "ArgumentProcessorResources";
    // registrySingleArgument("--single", "What exactly do this single param?");
    // registryParameterArgument("-param", "What need this param?");
    // registryExample("here example of command");
    registryProcessor(new ArgumentProcessorResourcesList());
    registryProcessor(new ArgumentProcessorResourcesAdd());
}

// ---------------------------------------------------------------------

bool ArgumentProcessorResources::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    WsjcppLog::err(TAG, "Not implemented");
    return false;
}

// ---------------------------------------------------------------------

bool ArgumentProcessorResources::applyParameterArgument(
    const std::string &sProgramName, 
    const std::string &sArgumentName, 
    const std::string &sValue
) {
    WsjcppLog::err(TAG, "Not implemented");
    return false;
}

// ---------------------------------------------------------------------

int ArgumentProcessorResources::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppLog::err(TAG, "Not implemented");
    return -1; 
}


// ---------------------------------------------------------------------
// ArgumentProcessorResourcesAdd

ArgumentProcessorResourcesList::ArgumentProcessorResourcesList() 
: WsjcppArgumentProcessor({"list", "ls"}, "Pack files to c++ code") {
    TAG = "ArgumentProcessorResources";
    registrySingleArgument("--more", "More information about resource file");
    m_bMore = false;
}

// ---------------------------------------------------------------------

bool ArgumentProcessorResourcesList::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    if (sArgumentName == "--more") {
        m_bMore = true;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------

int ArgumentProcessorResourcesList::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        std::cout 
            << std::endl
            << "ERROR: Could not load package info from current directory"
            << std::endl
            << std::endl
        ;
        return -1;
    }
    std::vector<WsjcppPackageManagerResourceFile> vList = pkg.getListOfResourceFiles();
    
    if (vList.size() == 0) {
        std::cout
            << "resource not found. "
            << std::endl
            << std::endl
            << "   For add please use a command: "
            << "   " << sProgramName << " resources add <path>"
            << std::endl
            << std::endl;
    } else {
        std::cout 
            << std::endl
            << "resources: "
            << std::endl;
        for (int i = 0; i < vList.size(); i++) {
            WsjcppPackageManagerResourceFile resFile = vList[i];
            // TODO check exists / size / modified / sha1 
            if (!m_bMore) {
                std::cout << " - " << resFile.getFilepath() << " (size: " << resFile.getFilesize() << " bytes)" << std::endl;
            } else {
                std::cout
                    << "  - filepath: " << resFile.getFilepath()
                    << std::endl
                    << "    filesize: " << resFile.getFilesize()
                    << std::endl
                    << "    pack-as: " << resFile.getPackAs()
                    << std::endl
                    << "    sha1: " << resFile.getSha1()
                    << std::endl
                    << "    modified: " << WsjcppCore::formatTimeUTC(resFile.getModified())
                    << std::endl
                ;
            }
        }
        std::cout
            << std::endl;
    }
    return 0;
}

// ---------------------------------------------------------------------
// ArgumentProcessorResourcesAdd

ArgumentProcessorResourcesAdd::ArgumentProcessorResourcesAdd() 
: WsjcppArgumentProcessor({"add"}, "Pack files to c++ code") {
    TAG = "ArgumentProcessorResources";
    registrySingleArgument("--text", "Pack resources like text");
    registrySingleArgument("--binary", "Pack resources like binary");
    m_bText = false;
    m_bBinary = false;
}

// ---------------------------------------------------------------------

bool ArgumentProcessorResourcesAdd::applySingleArgument(const std::string &sProgramName, const std::string &sArgumentName) {
    if (sArgumentName == "--text") {
        m_bText = true;
        return true;
    }
    if (sArgumentName == "--binary") {
        m_bBinary = true;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------

int ArgumentProcessorResourcesAdd::exec(const std::string &sProgramName, const std::vector<std::string> &vSubParams) {
    if (vSubParams.size() != 1) {
        std::cout 
            << std::endl
            << "ERROR: Expected arg1 with path to file" 
            << std::endl
            << std::endl;
        return -1;
    }
    std::string sFilepath = vSubParams[0];

    if (!WsjcppCore::fileExists(sFilepath)) {
        std::cout 
            << std::endl
            << "ERROR: '" << sFilepath << "' - file not exists" 
            << std::endl
            << std::endl;
        return -1; 
    }

    struct stat result;
    if(stat(sFilepath.c_str(), &result)==0)
    {
        auto mod_time = result.st_mtime;
        std::cout << "mod_time: " << mod_time << std::endl;
    }

    std::string sFileExt = sFilepath.substr(sFilepath.find_last_of(".") + 1);
    sFileExt = WsjcppCore::toLower(sFileExt);

    if (!m_bText && !m_bBinary) {
        // if user not specified
        if (sFileExt == "svg" 
            || sFileExt == "js" 
            || sFileExt == "css"
            || sFileExt == "html"
            || sFileExt == "conf"
            || sFileExt == "sh"
        ) {
            m_bText = true;
        } else {
            m_bBinary = true;
        }
    }

    if (m_bText && m_bBinary) {
        std::cout 
            << std::endl
            << "ERROR: File could not be and text and binary please specify only one"
            << std::endl
            << std::endl;
        return -1; 
    }

    WsjcppPackageManager pkg(".");
    if (!pkg.load()) {
        std::cout 
            << std::endl
            << "ERROR: Could not load package info from current directory"
            << std::endl
            << std::endl
        ;
        return -1;
    }

    std::string sDirResources = "./src/resources.wsjcpp";
    if (!WsjcppCore::dirExists(sDirResources)) {
        WsjcppCore::makeDir(sDirResources);
    }

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
    std::cout << sFilenameNormalized << std::endl;
    std::string sClassName = "RES_" + sFilenameNormalized;
    std::string sHeaderContent = 
        "// automaticly generated by wsjcpp:" + pkg.getVersion() + "\n"
        "\n"
        "#include <wsjcpp_resources_manager.h>\n"
        "\n"
        "class " + sClassName + " : public WsjcppResourceFile { \n"
        "    public:\n"
        "        virtual const std::string &getFilename();\n"
        "        virtual const int getBufferSize();\n"
        "        virtual const char *getBuffer();\n"
        "};\n"
        "\n"
    ;
    WsjcppCore::writeFile( sDirResources + "/" + sFilenameNormalized + ".h", sHeaderContent);
    
    char *pBuffer = nullptr;
    int nBufferSize = 0;
    if (!WsjcppCore::readFileToBuffer(sFilepath, &pBuffer, nBufferSize)) {
        std::cout 
            << std::endl
            << "ERROR: Could not read file '" << sFilepath << "'"
            << std::endl
            << std::endl
        ;
    }

    std::string sSourceContent = 
        "// automaticly generated by wsjcpp:" + pkg.getVersion() + "\n"
        "\n"
        "#include <" + sFilenameNormalized + ".h>\n"
        "\n"
        "REGISTRY_WSJCPP_RESOURCE_FILE(" + sClassName + ")\n"
        "\n"
        "const std::string &" + sClassName + "::getFilename() {\n"
        "    static const std::string s = \"" + sFilepath + "\";\n"
        "    return s;\n"
        "}\n"
        "\n"
        "// ---------------------------------------------------------------------\n"
        "\n"
        "const int " + sClassName + "::getBufferSize() {\n"
        "    return " + std::to_string(nBufferSize) + ";\n"
        "}\n"
        "\n"
        "// ---------------------------------------------------------------------\n"
        "\n"
    ;

    if (m_bBinary) {
        sSourceContent += 
            "const char *" + sClassName + "::getBuffer() {\n"
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

    if (m_bText) {
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

        /*with open(filename) as f:
            lines = f.read().splitlines()
            for l in lines:
                l_escaped = short_escape(l)
                _source.write("        \"" + l_escaped + "\\n\"\n")
                i = i + len(l) + 1
        if i != size:
            print("Expected " + str(size) + " got " + str(i))*/

        sSourceContent += 
            "    ;\n"
            "    return sRet.c_str();\n"
            "} //::buffer() \n"
            "\n";
    }

    WsjcppCore::writeFile( sDirResources + "/" + sFilenameNormalized + ".cpp", sSourceContent);

    // TODO add to wsjcpp.yml

    return -1;
}