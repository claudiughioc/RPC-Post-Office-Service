#include <stdio.h> 
#include <time.h> 
#include <rpc/rpc.h> 

#include "po.h" 
#define RMACHINE "localhost"

int main(int argc, char *argv[]){
    int lat, lon;
    char *file;

    if (argc != 4) {
        printf("Use lat long filename as command line arguments\n");
        return 1;
    }
    lat = atoi(argv[1]);
    lon = atoi(argv[2]);
    file = argv[3];

	/* variabila clientului */
	CLIENT *handle;

	handle=clnt_create(
		RMACHINE,		/* numele masinii unde se afla server-ul */
		LOAD_PROG,		/* numele programului disponibil pe server */
		LOAD_VERS,		/* versiunea programului */
		"tcp");			/* tipul conexiunii client-server */
	
	if(handle == NULL) {
		perror("");
		return -1;
	}

    printf("Ies din client\n");

    /* call to RPC server
    struct data date;
    struct data* res;
    date.text = calloc(1000, 1);
    printf("Introduceti commanda:\n");
    gets(date.text);
    res = get_load_1(&date, handle); 
    printf("%s\n", res->text);
    */
	
	return 0;
}
