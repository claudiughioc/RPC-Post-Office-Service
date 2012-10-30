#include <stdio.h> 
#include <time.h> 
#include <rpc/rpc.h> 

#include "po.h"

struct data* get_path_1_svc(struct colet *colet, struct svc_req *cl){
    printf("Something, something.... Dark side\n");
    printf("Ce primesc: %d, %f, %f\n", colet->id, colet->lat, colet->lon);
    static struct data ret;
    ret.id_source = 2;
    ret.id_dest = 3;
    ret.dist = 4;
    return &ret;
}
