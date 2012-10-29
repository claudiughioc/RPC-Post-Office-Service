/**
	Sisteme de programe pentru retele de calculatoare
	
	Copyright (C) 2008 Ciprian Dobre & Florin Pop
	Univerity Politehnica of Bucharest, Romania

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 */

#include <stdio.h> 
#include <time.h> 
#include <rpc/rpc.h> 

#include "load.h"

char wd[1000];

struct data* get_load_1_svc(struct data *data, struct svc_req *cl){
    printf("Command %s\n", data->text);


    FILE *fp;
    char cddir[1000] = "";
    // Execute cd;
    if (strncmp(wd, "/", 1) == 0) {
        strcpy(cddir, "chdir ");
        strcat(cddir, wd);
        strcat(cddir," ; ");
        printf("Executing cd: %s\n", cddir);
    }

    // Execute command
    strcat(cddir, data->text);
    strcat(cddir, " ; pwd");
    fp = popen(cddir, "r");
    static struct data result;
    result.text = calloc(1000, 1);
    char out[100][255];
    int i = 0;
    while (fgets(out[i], 200, fp) != NULL) {
        printf("Result of command: %s \n", out[i]);
        strcat(result.text, out[i]);
        strncpy(wd, out[i], strlen(out[1]) -1 );
        i++;
    }
    fclose(fp);

    printf("Result.text: %s \n", result.text);
	
	return &result;
}
