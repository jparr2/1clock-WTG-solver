//
// Created by julie on 28/12/22.
//

#include "Owner.h"

/*
 * Enum class : extenal function
 */
Owner getOwner(const string& owner) {
    if (owner == "Min") {return Owner::Min;}
    if (owner == "Max") {return  Owner::Max;}
    if (owner == "Target") {return  Owner::Target;}
    throw "getOwner : bad instruction choose between Min, Max and Target.";
}