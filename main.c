#include <getopt.h>
#include <string.h>

#include "common_tao.h"
#include "split.h"

//#define _CRT_SECURE_NO_WARNINGS
#define FILE_LEN 256

/* option */
#define no_argument		0
#define required_argument	1
#define optional_argument	2

static const char *optString = "f:o:n:h";
static struct option long_options[] = {
    {"file",	 	required_argument, 0, 'f'},
    {"out",	 	required_argument, 0, 'o'},
    {"num",	 	required_argument, 0, 'n'},
    {"help",	 	no_argument, 0, 'h'},
    {0,	0,	0,	0}
};

void print_usage()
{
    printf("\nUsage:\n");
    print_opt_help(0, "input file\n");
    print_opt_help(1, "output file\n");
    print_opt_help(2, "how much file do you want to split\n");
    print_opt_help(3, "display this help information\n");
    printf("\n");
}

int loglevel_g = LOG_LEVEL_DEBUG;

void print0(int loglevel, char * format, ...)
{
	if(loglevel <= loglevel_g){
		va_list ap;
		va_start(ap, format);
		vprintf(format, ap);
		va_end(ap);
	}
}

int main(int argc, char *argv[])
{
    char input_file[FILE_LEN]="";
    char output_file[FILE_LEN]="";
    int option_index = 0, ch =0;
    int split_num = 0;

    while ((ch = getopt_long(argc, argv, optString,long_options, &option_index)) != -1) {
    	switch (ch) {
    		case 'f':
    			strcpy(input_file,optarg);
    			LOGI("input file: %s ", optarg,input_file);
    			break;
             case 'o':
    			strcpy(output_file,optarg);
    			LOGI("output file: %s ", optarg,output_file);
    			break;
    		case 'n':
    			split_num= atoi(optarg);
    			LOGI("split_num= %d", split_num);
    			break;
    		case 'h':
    			print_usage();
    			break;
    		default:
                    print_usage();
    			break;
    	}
    }

    if(1 == argc){
        print_usage();
        return 0;
    }

    system("mkdir ./out");

    splitFile(input_file, split_num, "./out/", output_file);

    return 0;
}

