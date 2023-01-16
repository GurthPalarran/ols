//
// Created by gurth on 1/2/23.
//

#ifndef OLS_STDAFX_H
#define OLS_STDAFX_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <climits>

struct base_atom_t
{
    unsigned int pos_i;  // position i,j in latin square
    unsigned int pos_j;
    unsigned int value;  // value in C(i,j)
};

typedef struct atom_t : base_atom_t  // create an atom type
{
    long mappedVal; // mapped value
}Atom;

typedef std::vector<Atom> clause;    // clause containing a set of the above
typedef std::vector<clause> cnf;     // vector containing a cnf set

#endif //OLS_STDAFX_H
