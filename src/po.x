#define MAX 1024

struct data {
    int id_source;
    int id_dest;
    float dist;
};

struct colet {
    int id;
    float lat_d;
    float lon_d;
    float lat_s;
    float lon_s;
};

program PO_PROG {
	version PO_VERS {
		 struct data GET_PATH(struct colet) = 1;
	} = 1;
} = 123456789;
