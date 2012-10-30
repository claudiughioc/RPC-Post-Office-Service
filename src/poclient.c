#include <stdio.h> 
#include <time.h> 
#include <rpc/rpc.h> 

#include "po.h" 
#define RMACHINE "localhost"
#define MAX_COLETS  1024

int main(int argc, char *argv[]){
    float lat, lon;
    int i = 0;
    char *file;
    struct colet colets[MAX_COLETS];

    if (argc != 4) {
        printf("Use lat long filename as command line arguments\n");
        return 1;
    }
    lat = atof(argv[1]);
    lon = atof(argv[2]);
    file = argv[3];

    FILE *in = fopen(file, "r");
    while (fscanf(in, "%d %f %f",
                &colets[i].id,
                &colets[i].lat,
                &colets[i].lon) != EOF)
        i++;

	/* variabila clientului */
	CLIENT *handle;
	handle=clnt_create(
		RMACHINE,		/* numele masinii unde se afla server-ul */
		PO_PROG,		/* numele programului disponibil pe server */
		PO_VERS,		/* versiunea programului */
		"tcp");			/* tipul conexiunii client-server */
	if(handle == NULL)
		return -1;

    struct data* res;
    res = get_path_1(&colets[0], handle);
    printf("Returned %d, %d, %f\n", res->id_source, res->id_dest, res->dist);
	
	return 0;
}
