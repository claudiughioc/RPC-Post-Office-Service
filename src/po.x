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
	} = 1;
} = 123456789;
