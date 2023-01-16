#include "stdafx.h"
#include "encoder.h"
#include "decoder.h"
#include <getopt.h>
#include <ctime>

static struct option long_options[] =
{
        {"help", no_argument,       0,   'h'},
        {"cnf",  required_argument, 0,   'c'},
        {"sat",  required_argument, 0,   's'},
        {"out",  required_argument, 0,   'o'},
        {"msg",  required_argument, 0,   'm'},
        {"order",  required_argument, 0,   'i'},
        {"answer",  required_argument, 0,   'a'},
        {nullptr, 0, nullptr, 0}
};

static void help_info()
{
    printf("Usage: \n\t ols [option]... \n");
    printf("\t-i,--order\t\tOrder of the square\n");
    printf("\t-c,--cnf\t\tCNF file path\n");
    printf("\t-s,--sat\t\tSAT solver path\n");
    printf("\t-o,--out\t\tResult file path of the SAT solver\n");
    printf("\t-m,--msg\t\tSAT solver standard output save path\n");
    printf("\t-a,--answer\t\tAnswer save path\n");
    printf("\t-h,--help\t\tShow this massage\n");
}

using namespace std;

int main(int argc, char* argv[])
{
    help_info();

    unsigned int order = 10;
    string cnf_path = "test.cnf";
    string solver_path = "./glucose";
    string result_path = "test.out";
    string msg_path = "test.log";
    string answer_path = "test.answer";

    int arg, index;

    while((arg = getopt_long(argc, argv, "hc:s:o:m:i:a:", long_options, &index))!=-1) {

        switch (arg) {
            case 'h':
                help_info();
                return 0;
            case 'i':
                if (optarg)
                    order = atoi(optarg);
                else
                {
                    help_info();
                    exit(1);
                }
                break;
            case 'c':
                if (optarg)
                    cnf_path = optarg;
                else
                {
                    help_info();
                    exit(1);
                }
                break;
            case 's':
                if (optarg)
                    solver_path = optarg;
                else
                {
                    help_info();
                    exit(1);
                }
                break;
            case 'o':
                if (optarg)
                    result_path = optarg;
                else
                {
                    help_info();
                    exit(1);
                }
                break;
            case 'm':
                if (optarg)
                    msg_path = optarg;
                else
                {
                    help_info();
                    exit(1);
                }
                break;
            case 'a':
                if (optarg)
                    answer_path = optarg;
                else
                {
                    help_info();
                    exit(1);
                }
                break;
            default:
                printf("Unknown error parsing arg.\n");
                exit(1);
        }
    }

    clock_t start,end;
    string cmd;

    start = clock();

    if (!encoder(cnf_path.c_str(), order))
    {
        printf("Generating CNF file failed!\n");
        exit(1);
    }

    printf("[1] Generated CNF file in DIMACS format. File path: %s\n", realpath(cnf_path.c_str(), nullptr));

    cmd = solver_path + " " + cnf_path + " " + result_path + ">" + msg_path;

    int exit_code = system(cmd.c_str());

    printf("[2] Exit solver with code %d. Command: %s\n", exit_code, cmd.c_str());

    if(!decoder(result_path.c_str(), answer_path.c_str(), order))
    {
        printf("Parsing result failed!\n");
        exit(1);
    }

    printf("[3] Parsed solver output and save an answer. File path: %s\n", realpath(answer_path.c_str(), nullptr));

    end = clock();

    printf("Finished in %fs. \n",(double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}
