//
// Created by gurth on 1/2/23.
//

#include "stdafx.h"
#include "encoder.h"

using namespace std;

// property A - each cell of square contains a number in [n]
void propertyA(const unsigned int &order, cnf &subset)
{
    clause c(order);
    Atom atom;
    long numVariables = 0;
    for (int i = 1; i <= order * 2; i++)
    {
        atom.pos_i = i;
        for (int j = 1; j <= order; j++)
        {
            atom.pos_j = j;
            for (int k = 1; k <= order; k++)
            {
                atom.value = k;
                atom.mappedVal = ++numVariables;
                c[k - 1] = atom;
            }

            // push clauses into cnf set
            subset.push_back(c);
        }
    }
}

// property B - no cell contains two distinct numbers
void propertyB(const unsigned int &order, cnf &subset)
{
    clause c(order);
    Atom atom;
    long numVariables = 0;
    for (int i = 1; i <= order * 2; i++)
    {
        atom.pos_i = i;
        for (int j = 1; j <= order; j++)
        {
            atom.pos_j = j;
            for (int k = 1; k <= order; k++)
            {
                atom.value = k;
                atom.mappedVal = -(++numVariables);
                c[k - 1] = atom;
            }

            for (int t = 1; t <= order-1; t++)
            {
                for(int p=t+1;p<=order;p++)
                {
                    clause tmp_c(2);
                    tmp_c[0] = c[t-1];
                    tmp_c[1] = c[p-1];
                    subset.push_back(tmp_c);
                }
            }

            // push clauses into cnf set
            // subset.push_back(c);
        }
    }
}

// property C - no row has two cells containing the same number
void propertyC(const unsigned int &order,
               cnf &subset)
{
    clause c(order);
    Atom atom;
    for (int i = 1; i <= order*2; i++)
    {
        atom.pos_i = i;
        for (int k = 1; k <= order; k++)
        {
            atom.value = k;
            for (int j = 1; j <= order; j++)
            {
                atom.pos_j = j;

                atom.mappedVal = (i-1) * order * order + (j-1) * order + k;
                c[j-1] = atom;
            }

            subset.push_back(c);

            for (int t = 1; t <= order-1; t++)
            {
                for(int p=t+1;p<=order;p++)
                {
                    clause tmp_c(2);
                    tmp_c[0] = c[t-1];
                    tmp_c[0].mappedVal = -tmp_c[0].mappedVal;
                    tmp_c[1] = c[p-1];
                    tmp_c[1].mappedVal = -tmp_c[1].mappedVal;
                    subset.push_back(tmp_c);
                }
            }

            // push clauses into cnf set
            //subset.push_back(c);
        }
    }
}


// property D - no column has two cells containing the same number
void propertyD(const unsigned int &order,
               cnf &subset)
{
    clause c(order);
    Atom atom;
    for (int k = 1; k <= order; k++)
    {
        atom.value = k;
        for (int j = 1; j <= order; j++)
        {
            atom.pos_j = j;
            for (int i = 1; i <= order; i++)
            {
                atom.pos_i = i;

                atom.mappedVal = (i-1) * order * order + (j-1) * order + k;
                c[i-1] = atom;
            }

            subset.push_back(c);

            for (int t = 1; t <= order-1; t++)
            {
                for(int p=t+1;p<=order;p++)
                {
                    clause tmp_c(2);
                    tmp_c[0] = c[t-1];
                    tmp_c[0].mappedVal = -tmp_c[0].mappedVal;
                    tmp_c[1] = c[p-1];
                    tmp_c[1].mappedVal = -tmp_c[1].mappedVal;
                    subset.push_back(tmp_c);
                }
            }

            unsigned int offset = order* order*order;

            for (int i = 1; i <= order; i++)
            {
                atom.pos_i = i + offset;

                atom.mappedVal = offset + (i-1) * order * order + (j-1) * order + k;
                c[i-1] = atom;
            }

            subset.push_back(c);

            for (int t = 1; t <= order-1; t++)
            {
                for(int p=t+1;p<=order;p++)
                {
                    clause tmp_c(2);
                    tmp_c[0] = c[t-1];
                    tmp_c[0].mappedVal = -tmp_c[0].mappedVal;
                    tmp_c[1] = c[p-1];
                    tmp_c[1].mappedVal = -tmp_c[1].mappedVal;
                    subset.push_back(tmp_c);
                }
            }

            // push clauses into cnf set
            //subset.push_back(c);
        }
    }
}


// property E - Make sure the squares orthogonal
void propertyE(const unsigned int &order, cnf &subset)
{
    clause c(2);
    Atom atom1, atom2;
    long numVariables = 0;
    unsigned int offset = order * order * order;

    for (int i = 1; i <= order; i++)
    {
        atom1.pos_i = i;
        atom2.pos_i = i + offset;
        for (int j = 1; j <= order; j++)
        {
            atom1.pos_j = j;
            atom2.pos_j = j;
            for (int k = 1; k <= order; k++)
            {
                atom1.value = k;
                atom2.value = k;
                atom1.mappedVal = -(++numVariables);
                atom2.mappedVal = -(numVariables + offset);

                c[0] = atom1;
                c[1] = atom2;

                subset.push_back(c);
            }
        }
    }
}

// property F -
void propertyF(const unsigned int &order,
               cnf &subset,
               const map<string, unsigned long> &Map)
{

}

void outputData(const char* fileOut,
                const unsigned int &order,
                const cnf &subset1,
                const cnf &subset2,
                const cnf &subset3,
                const cnf &subset4,
                const cnf &subset5,
                const cnf &subset6)
{
    unsigned long numClause =  (subset1.size() + subset2.size() +
            subset3.size() +subset4.size() + subset5.size() + subset6.size());
    ofstream output;

    output.open(fileOut);
    if (!output)
    {
        cerr << "failed to write to output.txt" << endl;
        exit(1);
    }

    output << "c" << endl;
    output << "c Instance of order " << order << " in DIMACS format" << endl;
    output << "c" << endl;
    // maximum number of variables = order^3
    output << "p cnf " << order * order * order * 2 << " " << numClause << endl;


    for (int i = 0; i < subset1.size(); i++)
    {
        for (int j = 0; j < subset1[i].size(); j++)
            output << subset1[i][j].mappedVal << " ";

        output << "0" << endl;
    }

    for (int i = 0; i < subset2.size(); i++)
    {
        for (int j = 0; j < subset2[i].size(); j++)
            output << subset2[i][j].mappedVal << " ";

        output << "0" << endl;
    }

    for (int i = 0; i < subset3.size(); i++)
    {
        for (int j = 0; j < subset3[i].size(); j++)
            output << subset3[i][j].mappedVal << " ";

        output << "0" << endl;
    }


    for (int i = 0; i < subset4.size(); i++)
    {
        for (int j = 0; j < subset4[i].size(); j++)
            output << subset4[i][j].mappedVal << " ";

        output << "0" << endl;
    }


    for (int i = 0; i < subset5.size(); i++)
    {
        for (int j = 0; j < subset5[i].size(); j++)
            output << subset5[i][j].mappedVal << " ";

        output << "0" << endl;
    }

    for (int i = 0; i < subset6.size(); i++)
    {
        for (int j = 0; j < subset6[i].size(); j++)
            output << subset6[i][j].mappedVal << " ";

        output << "0" << endl;
    }

    output.close(); // close file
}


bool encoder(const char* cnf_path, unsigned int order)
{
    map<string, unsigned long> Map;
    cnf subsetA, subsetB, subsetC, subsetD, subsetE, subsetF;

    //init_map(order, Map);

    propertyA(order, subsetA);
    propertyB(order, subsetB);
    propertyC(order, subsetC);
    propertyD(order, subsetD);
    propertyE(order, subsetE);
    //propertyF(order, subsetF, Map);

    outputData(cnf_path, order,
               subsetA,subsetB, subsetC,
               subsetD, subsetE, subsetF);

    return true;
}