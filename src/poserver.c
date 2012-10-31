#include <stdio.h> 
#include <time.h> 
#include <rpc/rpc.h> 

#include "po.h"
#define INPUT_FILE  "po.dat"

struct op {
    int id;
    float lat, lon;
};

static int N;
static struct op *offices;

void *read_1_svc(void * ret, struct svc_req *cl)
{
    int i;
    printf("Reading from file\n");

    FILE *in = fopen(INPUT_FILE, "rb");
    if (in == NULL) {
        printf("Error on opening file\n");
        return NULL;
    }
    fread(&N, sizeof(int), 1, in);

    offices = (struct op*) malloc(N * sizeof(struct op));
    if (offices == NULL) {
        printf("Error on allocating space for offices\n");
        return NULL;
    }

    for (i = 0; i < N; i++) {
        fread(&offices[i].lat, sizeof(float), 1, in);
        fread(&offices[i].lon, sizeof(float), 1, in);
        offices[i].id = i + 1;
    }
    fclose(in);
    printf("Reading completed\n");
}


struct data* get_path_1_svc(struct colet *colet, struct svc_req *cl)
{
    printf("Something, something.... Dark side\n");
    printf("Ce primesc: %d, %f, %f\n", colet->id, colet->lat_d, colet->lon_d);
    static struct data ret;
    ret.id_source = 2;
    ret.id_dest = 3;
    ret.dist = 4;
    return &ret;
}
