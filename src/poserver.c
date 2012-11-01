#include <stdio.h> 
#include <time.h> 
#include <math.h>
#include <rpc/rpc.h> 

#include "po.h"
#define INPUT_FILE  "po.dat"
#define EARTH_RADIUS      6380

struct op {
    int id;
    float lat, lon;
};

static int N;
static struct op *offices;
static struct colet source;

static float form(float lat1, float lon1, float lat2, float lon2)
{
    float s1, s2;
    s1 = sin((double)(lat1 - lat2) / 2);
    s1 *= s1;
    s2 = sin((double)(lon1 - lon2) / 2);
    s2 *= s2;
    return s1 + cos(lat1) * cos(lat2) * s2;
}

static float distance(float lat1, float lon1, float lat2, float lon2)
{
    double x = form(lat1, lon1, lat2, lon2);
    return 2 * EARTH_RADIUS * atan2(sqrt(x), sqrt(1 - x));
}

void *init_1_svc(struct colet *client, struct svc_req *cl)
{
    int i;
    source = *client;
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
    printf("Ce primesc: %d, %f, %f\n", colet->id, colet->lat, colet->lon);
    int i, j;
    float dist1, dist2, min_dist_s, min_dist_d;
    struct op best_source, best_dest, curr_op;

    for (i = 0; i < N; i++) {
        curr_op = offices[i];
        dist1 = distance(source.lat, curr_op.lat,
                    source.lon, curr_op.lon);
        dist2 = distance(colet->lat, curr_op.lat,
                    colet->lon, curr_op.lon);

        if (i == 1) {
            min_dist_s = dist1;
            min_dist_d = dist2;
        } else {
            if (dist1 < min_dist_s) {
                min_dist_s = dist1;
                best_source = curr_op;
            }
            if (dist2 < min_dist_d) {
                min_dist_d = dist2;
                best_dest = curr_op;
            }
        }
    }


    static struct data ret;
    ret.id_source = best_source.id;
    ret.id_dest = best_dest.id;
    ret.dist = min_dist_s + min_dist_d +
                distance(best_source.lat, best_dest.lat,
                            best_source.lon, best_dest.lon);
    return &ret;
}
