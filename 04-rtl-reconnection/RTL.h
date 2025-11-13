// === RTL.h (add helper declaration) ===
#ifndef RTL_H
#define RTL_H

#include <string>
#include <vector>
#include <unordered_map>


// Per-module port rename map: oldPort -> newPort
using PortRenameMap = std::unordered_map<std::string, std::string>;

// Map each submodule name to its PortRenameMap
using ScopedPortMap = std::unordered_map<std::string, PortRenameMap>;

// Module-name rename map: oldModule -> newModule
using ModuleRenameMap = std::unordered_map<std::string, std::string>;

// Represents a Verilog module and its raw lines
struct Module {
    std::string name;
    std::vector<std::string> bodyLines;
    std::vector<std::string> ports;
};

// Parse update_information into moduleRename and scopedPorts
void parseUpdateInformation(
    const std::string& filename,
    ModuleRenameMap& moduleRename,
    ScopedPortMap& scopedPorts
);

// Read a Verilog file into a Module struct
// read exactly one (named) module out of a file that may contain many
void readVerilogModule(
    const std::string& filename,
    const std::string& targetModuleName,
    Module& module
);


// Generate new_top_module.v using the parsed maps
void generateNewTopModule(
    const Module& topModule,
    const ModuleRenameMap& moduleRename,
    const ScopedPortMap& scopedPorts,
    const std::string& outputFilename
);

// Debug prints (optional)
void printScopedPortMap(const ScopedPortMap& spm);
void printModuleRenameMap(const ModuleRenameMap& mrm);

// New: fill missing port renames by matching assign statements
void fillPortRenamesByAssigns(
    const Module& oldModule,
    const Module& newModule,
    PortRenameMap& portMap
);

#endif // RTL_H
