//
// Created by julie on 28/12/22.
//

#ifndef CODE_OWNER_H
#define CODE_OWNER_H

#include <string>
using namespace std;
/*
 * Enum type Owner
 * To define the membership of the vertex.
 */
enum class Owner {Min, Max, Target};
Owner getOwner(const string& owner);

#endif //CODE_OWNER_H
