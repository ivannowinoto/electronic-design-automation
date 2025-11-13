#include <iostream>
#include "RTL.h"

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cerr << "Usage: ./<executable> top_module.v sub_module.v new_sub_module.v update_information new_top_module.v\n";
        return 1;
    }

    std::string topFile = argv[1];
    std::string subFile = argv[2];
    std::string newSubFile = argv[3];
    std::string updateInfoFile = argv[4];
    std::string outputFileName = argv[5];

    // Data structures
    ModuleRenameMap moduleRename;
    ScopedPortMap   scopedPorts;
    Module          topModule, subModule, newSubModule;

    // Parse update_information
    parseUpdateInformation(updateInfoFile, moduleRename, scopedPorts);
    // after parseUpdateInformation(updateInfoFile, moduleRename, scopedPorts);

// for every old->new pair in update_information
    for (auto& [oldName, newName] : moduleRename) {
        Module oldMod, newMod;

        // read _only_ the one named module out of each file
        readVerilogModule(subFile, oldName, oldMod);
        readVerilogModule(newSubFile, newName, newMod);

        auto it = scopedPorts.find(oldName);
        if (it != scopedPorts.end()) {
            auto& portMap = it->second;

            // 3a) positional fallback for any still-empty entries
            for (size_t i = 0;
                i < oldMod.ports.size() && i < newMod.ports.size();
                ++i)
            {
                const auto& o = oldMod.ports[i];
                const auto& n = newMod.ports[i];
                if (portMap[o].empty())
                    portMap[o] = n;
            }

            // 3b) then—if you still want—your assign-based refinement
            fillPortRenamesByAssigns(oldMod, newMod, portMap);
        }
    }

    // finally, read the top module once and emit
    readVerilogModule(topFile, "top_module", topModule);
    generateNewTopModule(topModule, moduleRename, scopedPorts, "new_top_module.v");

    // Fill any missing port renames by matching assign statements
    auto it = scopedPorts.find(subModule.name);
    if (it != scopedPorts.end()) {
        fillPortRenamesByAssigns(subModule, newSubModule, it->second);
    }

    // positional fallback for any still‐empty entries
    auto& oldPorts = subModule.ports;
    auto& newPorts = newSubModule.ports;
    auto& portMap = scopedPorts[subModule.name];

    for (size_t i = 0;
        i < oldPorts.size() && i < newPorts.size();
        ++i)
    {
        const auto& oldP = oldPorts[i];
        const auto& newP = newPorts[i];
        auto pit = portMap.find(oldP);
        if (pit != portMap.end() && pit->second.empty()) {
            pit->second = newP;
        }
    }


    // Generate the new_top_module.v
    generateNewTopModule(topModule, moduleRename, scopedPorts, outputFileName);

    return 0;
}
