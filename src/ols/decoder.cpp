//
// Created by gurth on 1/2/23.
//

#include "stdafx.h"
#include "decoder.h"

using namespace std;


inline int value(const int& index, const unsigned int& order)
{
    return (index-1) % order + 1;
}

bool decoder(const char* result_path, const char* answer_path, unsigned int order)
{
    ifstream fin(result_path, ios::in);
    if(!fin.is_open())
    {
        printf("Cannot open file \"%s\"!\n", result_path);
        exit(1);
    }

    unsigned int cnt =0;
    unsigned int offset = order * order;
    bool tag = true;

    FILE* pf = fopen(answer_path, "w");

    if(pf == nullptr)
    {
        printf("Cannot open file \"%s\"!\n", answer_path);
        exit(1);
    }

    fprintf(pf, "LS1:\n");


    while (!fin.eof())
    {
        int v = 0;
        fin >> v;
        if(!v) break;
        if(v>0)
        {
            fprintf(pf,"%3u ", value(v, order));
            cnt ++;

            if(cnt % order ==0)
            {
                fprintf(pf, "\n");
                if (cnt % offset == 0 && tag)
                {
                    fprintf(pf, "LS2:\n");
                    tag = false;
                }
            }
        }

    }
    // printf("\n%d ", cnt);

    fin.close();

    fclose(pf);

    return true;
}