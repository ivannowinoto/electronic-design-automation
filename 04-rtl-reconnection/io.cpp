#include "RTL.h"
#include <fstream>
#include <iostream>
#include <regex>

//-----------------------------------------------------------------------------
// parseUpdateInformation
//   Populates moduleRename and scopedPorts from the update_information file.
//-----------------------------------------------------------------------------
void parseUpdateInformation(
    const std::string& filename,
    ModuleRenameMap& moduleRename,
    ScopedPortMap& scopedPorts
) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: cannot open " << filename << "\n";
        return;
    }

    std::string line;
    std::regex modPat(R"(^\s*(sub_module\d+)\s+is\s+updated\s+to\s+(new_sub_module\d+)\.\s*$)");
    std::regex portFull(R"(^\s*#\d+\s+(\w+)\s+is\s+renamed\s+to\s+(\w+)\.\s*$)");
    std::regex portRemoved(R"(^\s*#\d+\s+(\w+)\s+is\s+renamed\.\s*$)");
    std::smatch m;
    std::string currentMod;

    while (std::getline(file, line)) {
        if (std::regex_match(line, m, modPat)) {
            currentMod = m[1];
            moduleRename[currentMod] = m[2];
            scopedPorts[currentMod] = PortRenameMap{};
        }
        else if (std::regex_match(line, m, portFull)) {
            scopedPorts[currentMod][m[1]] = m[2];
        }
        else if (std::regex_match(line, m, portRemoved)) {
            scopedPorts[currentMod][m[1]] = "";
        }
        // else skip blank or unrelated lines
    }
}

//-----------------------------------------------------------------------------
// readVerilogModule
//   Reads every line into module.bodyLines and extracts module.name.
//-----------------------------------------------------------------------------
void readVerilogModule(
    const std::string& filename,
    const std::string& targetModuleName,
    Module& module
) {
    std::ifstream file(filename);
    std::string line;
    std::regex headerRx(R"(\s*module\s+(\w+)\s*\()");
    bool inTarget = false;

    while (std::getline(file, line)) {
        std::smatch m;
        if (!inTarget) {
            // look for “module <name>(”
            if (std::regex_search(line, m, headerRx) &&
                m[1] == targetModuleName)
            {
                inTarget = true;
                // right after inTarget = true
                std::string accum = line.substr(m.position() + m.length());
                while (accum.find(");") == std::string::npos && std::getline(file, line)) {
                    module.bodyLines.push_back(line);
                    accum += line;
                }
                // now `accum` holds “<port1>, <port2>, … );”
                // split on commas
                std::regex comma(R"(\s*,\s*)");
                std::sregex_token_iterator it(accum.begin(), accum.end(), comma, -1), end;
                for (; it != end; ++it) {
                    auto p = it->str();
                    // strip whitespace and any trailing “);”
                    p = std::regex_replace(p, std::regex(R"([\(\);\s])"), "");
                    if (!p.empty())
                        module.ports.push_back(p);
                }

            }
        }

        if (inTarget) {
            module.bodyLines.push_back(line);
            if (line.find("endmodule") != std::string::npos)
                break;      // we’ve read exactly this one module, stop!
        }
    }
}



//-----------------------------------------------------------------------------
// generateNewTopModule
//   Writes new_top_module.v, renaming the top module, each submodule, and its ports.
//-----------------------------------------------------------------------------

void generateNewTopModule(
    const Module& topModule,
    const ModuleRenameMap& moduleRename,
    const ScopedPortMap& scopedPorts,
    const std::string& outputFilename
) {
    std::ofstream out(outputFilename);
    if (!out) {
        std::cerr << "Error: cannot open " << outputFilename << "\n";
        return;
    }
    out << "module new_top_module (\n";
    // … then let the loop spit out only the ports and closing “);” …


    // match the start of any instantiation: "<modulename> <instname>("
    std::regex instStart(R"(^\s*(\w+)\s+(\w+)\s*\()");
    // match individual ".port(sig)"
    std::regex portPat(R"(\.(\w+)\s*\(\s*([^)]+)\s*\))");

    bool inInst = false;
    bool moduleClosed = false;        // to skip the duplicate ");"
    std::string currentMod;

    for (auto line : topModule.bodyLines) {
        std::smatch m;

        // 2) Detect and print the module-port closing only once,
        //    i.e. the first line that is exactly ");" (with optional spaces).
        if (!inInst && !moduleClosed &&
            std::regex_match(line, std::regex(R"(^\s*\)\s*;\s*$)"))) {
            out << line << "\n";
            moduleClosed = true;
            continue;
        }
        // skip any further ");" outside instantiations
        if (!inInst && moduleClosed &&
            std::regex_match(line, std::regex(R"(^\s*\)\s*;\s*$)"))) {
            continue;
        }

        // 3) Detect the start of a submodule instantiation:
        if (!inInst && std::regex_search(line, m, instStart)) {
            inInst = true;
            currentMod = m[1];  // the old module name

            // look up its replacement (if any)
            auto itMod = moduleRename.find(currentMod);
            std::string newMod = (itMod != moduleRename.end())
                ? itMod->second
                : currentMod;

            // replace only at the very start of the line
            line = std::regex_replace(
                line,
                std::regex("^\\s*" + currentMod),
                newMod
            );
        }

        // 4) If inside an instantiation, rewrite its ports:
        if (inInst) {
            std::string rewritten;
            size_t       lastPos = 0;
            const auto& portMap = scopedPorts.at(currentMod);

            auto begin = std::sregex_iterator(line.begin(), line.end(), portPat);
            auto end = std::sregex_iterator();
            for (auto it = begin; it != end; ++it) {
                auto pm = *it;
                auto oldPort = pm[1].str();
                auto sig = pm[2].str();

                // copy up to this port
                rewritten.append(line.substr(lastPos, pm.position() - lastPos));

                // look up new port name (may be empty)
                auto pit = portMap.find(oldPort);
                if (pit != portMap.end()) {
                    const auto& newPort = pit->second;
                    if (!newPort.empty())
                        rewritten += "." + newPort + "(" + sig + ")";
                    else
                        rewritten += ".(" + sig + ")";
                }
                else {
                    // leave untouched
                    rewritten += pm.str();
                }

                lastPos = pm.position() + pm.length();
            }
            // append the rest of the line
            rewritten.append(line.substr(lastPos));
            line = std::move(rewritten);

            // detect end of this instantiation
            if (line.find(");") != std::string::npos) {
                inInst = false;
            }
        }

        // 5) Emit every other line unchanged
        out << line << "\n";
    }

    out.close();
}


void printModuleRenameMap(const ModuleRenameMap& mrm) {
    std::cout << "Module rename mapping:\n";
    for (const auto& [oldName, newName] : mrm) {
        std::cout << oldName << " -> " << newName << "\n";
    }
    std::cout << "\n";
}

void printScopedPortMap(const ScopedPortMap& spm) {
    std::cout << "Scoped port mappings:\n";
    for (const auto& [modName, portMap] : spm) {
        std::cout << modName << ":\n";
        for (const auto& [oldPort, newPort] : portMap) {
            std::cout << "  " << oldPort << " -> ";
            if (newPort.empty())
                std::cout << "(removed)";
            else
                std::cout << newPort;
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}