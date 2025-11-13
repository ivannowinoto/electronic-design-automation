#include "RTL.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

// Tokenizes an expression into identifiers and non-identifiers
static void tokenize(const std::string& expr,
    std::vector<bool>& isId,
    std::vector<std::string>& tokens) {
    size_t i = 0, n = expr.size();
    while (i < n) {
        if (std::isalnum(expr[i]) || expr[i] == '_') {
            size_t j = i;
            while (j < n && (std::isalnum(expr[j]) || expr[j] == '_')) j++;
            tokens.push_back(expr.substr(i, j - i));
            isId.push_back(true);
            i = j;
        }
        else {
            tokens.push_back(std::string(1, expr[i]));
            isId.push_back(false);
            i++;
        }
    }
}

// Parses 'assign lhs = rhs;' into lhs and rhs strings
static bool parseAssignLine(const std::string& line,
    std::string& lhs,
    std::string& rhs) {
    std::regex assignPat(R"(\s*assign\s+(\w+)\s*=\s*(.+)\s*;)");
    std::smatch m;
    if (std::regex_match(line, m, assignPat)) {
        lhs = m[1];
        rhs = m[2];
        return true;
    }
    return false;
}

// Fills portMap entries that have empty newName by matching assign statements
void fillPortRenamesByAssigns(const Module& oldModule,
    const Module& newModule,
    PortRenameMap& portMap) {
    std::vector<std::string> oldAssigns, newAssigns;
    // collect assign lines
    for (auto& line : oldModule.bodyLines) {
        std::string lhs, rhs;
        if (parseAssignLine(line, lhs, rhs))
            oldAssigns.push_back(line);
    }
    for (auto& line : newModule.bodyLines) {
        std::string lhs, rhs;
        if (parseAssignLine(line, lhs, rhs))
            newAssigns.push_back(line);
    }

    if (oldAssigns.size() != newAssigns.size()) {
        std::cerr << "Warning: assign count mismatch old/new modules\n";
    }
    size_t count = std::min(oldAssigns.size(), newAssigns.size());
    for (size_t i = 0; i < count; ++i) {
        std::string oldLhs, oldRhs, newLhs, newRhs;
        parseAssignLine(oldAssigns[i], oldLhs, oldRhs);
        parseAssignLine(newAssigns[i], newLhs, newRhs);
        // map LHS if missing
        auto pitL = portMap.find(oldLhs);
        if (pitL != portMap.end() && pitL->second.empty()) {
            pitL->second = newLhs;
        }
        // tokenize RHS and map identifiers
        std::vector<bool> isIdOld, isIdNew;
        std::vector<std::string> tokOld, tokNew;
        tokenize(oldRhs, isIdOld, tokOld);
        tokenize(newRhs, isIdNew, tokNew);
        if (tokOld.size() == tokNew.size()) {
            for (size_t j = 0; j < tokOld.size(); ++j) {
                if (isIdOld[j] && isIdNew[j]) {
                    auto pit = portMap.find(tokOld[j]);
                    if (pit != portMap.end() && pit->second.empty()) {
                        pit->second = tokNew[j];
                    }
                }
            }
        }
    }
}