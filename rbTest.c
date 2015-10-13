#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

#include "err_handle/err_handle.h" /* error functions */
#include "get_num/get_num.h"       /* conversion functions */
#include "red_black.h"             /* red black tree we are testing */


                /* prototypes */

/* arg1 = # of inserts, arg 2 = # of removals arg3 = mod */
int32_t main(int32_t argc, char *argv[])
{
    /* rb tree to test */
    rbTree rbTest;

    uint32_t insertions = 0;   /* argv[1] */
    uint32_t removals = 0;     /* argv[2] */
    uint32_t modVal = 0;       /* argv[3] */
    uint32_t toSend = 0;       /* number to add/remove */
    uint32_t resultCheck = 0;  /* proper ammount of nodes remaining */
    uint32_t totalData = 0;    /* total data count */
    
    uint32_t i = 0;

    /* seed random for insertion/removal testing. Using time for convenience */
    srandom(time((time_t*)NULL));

    /* check main args */
    if(argc != 4){
        noerrExit("Usage: $ program #inserts #removals modValue");}
    
    /* convert main args */
    insertions = getu32_t(argv[1], 0, (char*)NULL); /* # of insertions */
    removals   = getu32_t(argv[2], 0, (char*)NULL); /* # of removals */
    modVal     = getu32_t(argv[3], 0, (char*)NULL); /* mod value */
    
    if(insertions < removals){
        noerr_msg("Warning, more removals than insertions");}

    /* initialize rbTree for testing */
    rbTree_init(&rbTest);
        
    /* insert */
    for(/*i=0*/; i < insertions; ++i)
    {
        toSend = random() % modVal;

        if(give_data(&rbTest, toSend) == 0){
            noerrExit("inserting data into tree");}
    } 

    /* remove */
    for(i = 0; i < removals; ++i)
    {
        toSend = random() % modVal;

        resultCheck += remove_first(&rbTest, toSend);
    } 

    /* check results */
    totalData = total_data_count(&rbTest);

    printf("\nResulting node count: %d\n"
           "Resulting node count should be: %d\n"
           "Remove found no value %d times.\n"
           "Remove was attempted %d times.\n",
           totalData, (insertions - resultCheck), resultCheck, removals);

    remove_all(&rbTest);

    exit(EXIT_SUCCESS);
} /* end main */
