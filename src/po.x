#define MAX 1024

struct data {
    int id_source;
    int id_dest;
    float dist;
};

struct colet {
    int id;
    float lat;
    float lon;
};

program PO_PROG {
	version PO_VERS {
		 struct data GET_PATH(struct colet) = 1;
         int INIT(struct colet) = 2;
	} = 1;
} = 123456789;
