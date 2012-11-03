#include <stdio.h> 
#include <time.h> 
#include <math.h>
#include <rpc/rpc.h> 

#include                "po.h"
#define INPUT_FILE      "po.dat"
#define EARTH_RADIUS    6380

struct post_office {
    int id;
    float lat, lon;
};

static int N;                       // Number of post offices
static struct post_office *offices; // All the post offices
static struct colet source;         // The position of the client

// Function which calculates the x in the distance formula
static float formula(float lat1, float lon1, float lat2, float lon2)
{
    float s1, s2;

    // Transform angles in radians
    lat1 = lat1 * M_PI / 180;
    lon1 = lon1 * M_PI / 180;
    lat2 = lat2 * M_PI / 180;
    lon2 = lon2 * M_PI / 180;

    s1 = sin((double)(lat1 - lat2) / 2);
    s1 *= s1;
    s2 = sin((double)(lon1 - lon2) / 2);
    s2 *= s2;
    return s1 + cos(lat1) * cos(lat2) * s2;
}

// Function which calculates the distance between two points,
// given their coordinates
static float distance(float lat1, float lon1, float lat2, float lon2)
{
    double x = formula(lat1, lon1, lat2, lon2);
    return 2 * EARTH_RADIUS * atan2(sqrt(x), sqrt(1 - x));
}

// Initiates client data and reads the post offices information from file
int *init_1_svc(struct colet *client, struct svc_req *cl)
{
    int i;
    static int ret = 0;
    source = *client;

    printf("Reading from file\n");
    FILE *in = fopen(INPUT_FILE, "rb");
    if (in == NULL) {
        printf("Error on opening file\n");
        return &ret;
    }
    fread(&N, sizeof(int), 1, in);

    // Allocate memory for all the post offices
    offices = (struct post_office*) malloc(N * sizeof(struct post_office));
    if (offices == NULL) {
        printf("Error on allocating space for offices\n");
        return &ret;
    }

    for (i = 0; i < N; i++) {
        fread(&offices[i].lat, sizeof(float), 1, in);
        fread(&offices[i].lon, sizeof(float), 1, in);
        offices[i].id = i + 1;
    }
    fclose(in);
    return &ret;
}

// Calculates the path (source and destination post office) for a package
struct data* get_path_1_svc(struct colet *colet, struct svc_req *cl)
{
    static struct data ret;
    int i;
    float dist1, dist2, min_dist_s, min_dist_d;
    struct post_office best_source, best_dest, curr_op;

    for (i = 0; i < N; i++) {
        curr_op = offices[i];

        // Distance between client and a post office
        dist1 = distance(source.lat, source.lon,
                    curr_op.lat, curr_op.lon);
        // Distance between destination and a post office
        dist2 = distance(colet->lat, colet->lon,
                    curr_op.lat, curr_op.lon);

        if (i == 0) {
            // Initialize minimum distances
            min_dist_s = dist1;
            min_dist_d = dist2;
        } else {
            // Find the minimum distance and the closest post office
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

    // Send the result back to the client
    ret.id_source = best_source.id;
    ret.id_dest = best_dest.id;
    ret.dist = min_dist_s + min_dist_d +
                distance(best_source.lat, best_source.lon,
                            best_dest.lat, best_dest.lon);
    return &ret;
}
