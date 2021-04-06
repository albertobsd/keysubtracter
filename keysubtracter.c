/*
Develop by Luis Alberto
email: alberto.bsd@gmail.com


compile in the keyhunt directory

gcc -o keysubstracter keysubstracter.c -lgmp

*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "util.h"

#include "gmpecc.h"

const char *version = "0.1";
const char *EC_constant_N = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141";
const char *EC_constant_P = "fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f";
const char *EC_constant_Gx = "79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798";
const char *EC_constant_Gy = "483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8";

void showhelp();
void set_bit(char *param);
void set_publickey(char *param);
void set_range(char *param);

char *str_output = NULL;
struct Point target_publickey,base_publickey,sum_publickey,negated_publickey,dst_publickey;

int FLAG_RANGE = 0;
int FLAG_BIT = 0;
int FLAG_RANDOM = 0;
int FLAG_PUBLIC = 0;
int FLAG_N;
uint64_t N = 0,M;

mpz_t min_range,max_range,diff,TWO,base_key,sum_key,dst_key;
gmp_randstate_t state;

int main(int argc, char **argv)  {
	FILE *OUTPUT;
	char c;
	uint64_t i = 0;
	mpz_init_set_str(EC.p, EC_constant_P, 16);
	mpz_init_set_str(EC.n, EC_constant_N, 16);
	mpz_init_set_str(G.x , EC_constant_Gx, 16);
	mpz_init_set_str(G.y , EC_constant_Gy, 16);
	init_doublingG(&G);

	mpz_init(min_range);
	mpz_init(max_range);
	mpz_init(diff);
	mpz_init_set_ui(TWO,2);
	mpz_init(target_publickey.x);
	mpz_init_set_ui(target_publickey.y,0);
	while ((c = getopt(argc, argv, "hvRb:n:o:p:r:")) != -1) {
		switch(c) {
			case 'h':
				showhelp();
				exit(0);
			break;
			case 'b':
				set_bit((char *)optarg);
				FLAG_BIT = 1;
			break;
			case 'n':
				N = strtol((char *)optarg,NULL,10);
				if(N<= 0)	{
					fprintf(stderr,"[E] invalid bit N number %s\n",optarg);
					exit(0);
				}
				FLAG_N = 1;
			break;
			case 'o':
				str_output = (char *)optarg;
			break;
			case 'p':
				set_publickey((char *)optarg);
				FLAG_PUBLIC = 1;
			break;
			case 'r':
				set_range((char *)optarg);
				FLAG_RANGE = 1;
			break;
			case 'R':
				FLAG_RANDOM = 1;
			break;
			case 'v':
				printf("version %s\n",version);
			break;
		}
	}
	if((FLAG_BIT || FLAG_RANGE) && FLAG_PUBLIC && FLAG_N)	{
		if(str_output)	{
			OUTPUT = fopen(str_output,"a");
			if(OUTPUT == NULL)	{
				fprintf(stderr,"can't opent file %s\n",str_output);
				OUTPUT = stdout;
			}
		}
		else	{
			OUTPUT = stdout;
		}
		if(N % 2 == 1)	{
			N++;
		}
		M = N /2;
		mpz_sub(diff,max_range,min_range);
		mpz_init(base_publickey.x);
		mpz_init(base_publickey.y);
		mpz_init(sum_publickey.x);
		mpz_init(sum_publickey.y);
		mpz_init(negated_publickey.x);
		mpz_init(negated_publickey.y);
		mpz_init(dst_publickey.x);
		mpz_init(dst_publickey.y);
		mpz_init(base_key);
		mpz_init(sum_key);
		if(FLAG_RANDOM)	{
			gmp_randinit_mt(state);
			gmp_randseed_ui(state, ((int)clock()) + ((int)time(NULL)) );
			for(i = 0; i < M;i++)	{
				mpz_urandomm(base_key,state,diff);
				Scalar_Multiplication(G,&base_publickey,base_key);
				Point_Negation(&base_publickey,&negated_publickey);
				Point_Addition(&base_publickey,&target_publickey,&dst_publickey);
				if(mpz_tstbit(dst_publickey.y, 0) == 0)	{	// Even
					gmp_fprintf(OUTPUT,"02%0.64Zx # - %Zd\n",dst_publickey.x,base_key);
				}
				else	{
					gmp_fprintf(OUTPUT,"03%0.64Zx # - %Zd\n",dst_publickey.x,base_key);
				}

				Point_Addition(&negated_publickey,&target_publickey,&dst_publickey);
				if(mpz_tstbit(dst_publickey.y, 0) == 0)	{	// Even
					gmp_fprintf(OUTPUT,"02%0.64Zx # + %Zd\n",dst_publickey.x,base_key);
				}
				else	{
					gmp_fprintf(OUTPUT,"03%0.64Zx # + %Zd\n",dst_publickey.x,base_key);
				}
			}
			if(mpz_tstbit(target_publickey.y, 0) == 0)	{	// Even
				gmp_fprintf(OUTPUT,"02%0.64Zx # target\n",target_publickey.x);
			}
			else	{
				gmp_fprintf(OUTPUT,"03%0.64Zx # target\n",target_publickey.x);
			}
		}
		else	{
			mpz_cdiv_q_ui(base_key,diff,M);
			Scalar_Multiplication(G,&base_publickey,base_key);
			mpz_set(sum_publickey.x,base_publickey.x);
			mpz_set(sum_publickey.y,base_publickey.y);
			mpz_set(sum_key,base_key);
			for(i = 0; i < M;i++)	{
				Point_Negation(&sum_publickey,&negated_publickey);

				Point_Addition(&sum_publickey,&target_publickey,&dst_publickey);
				if(mpz_tstbit(dst_publickey.y, 0) == 0)	{	// Even
					gmp_fprintf(OUTPUT,"02%0.64Zx # - %Zd\n",dst_publickey.x,sum_key);
				}
				else	{
					gmp_fprintf(OUTPUT,"03%0.64Zx # - %Zd\n",dst_publickey.x,sum_key);
				}

				Point_Addition(&negated_publickey,&target_publickey,&dst_publickey);
				if(mpz_tstbit(dst_publickey.y, 0) == 0)	{	// Even
					gmp_fprintf(OUTPUT,"02%0.64Zx # + %Zd\n",dst_publickey.x,sum_key);
				}
				else	{
					gmp_fprintf(OUTPUT,"03%0.64Zx # + %Zd\n",dst_publickey.x,sum_key);
				}

				Point_Addition(&sum_publickey,&base_publickey,&dst_publickey);
				mpz_set(sum_publickey.x,dst_publickey.x);
				mpz_set(sum_publickey.y,dst_publickey.y);
				mpz_add(sum_key,sum_key,base_key);
			}
			if(mpz_tstbit(target_publickey.y, 0) == 0)	{	// Even
				gmp_fprintf(OUTPUT,"02%0.64Zx # target\n",target_publickey.x);
			}
			else	{
				gmp_fprintf(OUTPUT,"03%0.64Zx # target\n",target_publickey.x);
			}

		}
		mpz_clear(base_publickey.x);
		mpz_clear(base_publickey.y);
		mpz_clear(sum_publickey.x);
		mpz_clear(sum_publickey.y);
		mpz_clear(negated_publickey.x);
		mpz_clear(negated_publickey.y);
		mpz_clear(dst_publickey.x);
		mpz_clear(dst_publickey.y);
		mpz_clear(base_key);
		mpz_clear(sum_key);
	}
	else	{
		fprintf(stderr,"Version: %s\n",version);
		fprintf(stderr,"[E] there are some missing parameter\n");
		showhelp();
	}
	return 0;
}

void showhelp()	{
	printf("\nUsage:\n-h\t\tshow this help\n");
	printf("-b bits\t\tFor some puzzles you only need a bit range\n");
	printf("-n number\tNumber of publikeys to be geneted, this numbe will be even\n");
	printf("-o file\tOutput file, if you omit this option the out will go to the standar output\n");
	printf("-p key\tPublickey to be substracted compress or uncompress\n");
	printf("-r A:B\t\trange A to B\n");
	printf("-R\t\t\tSet the publickey substraction Random instead of secuential\n");
}


void set_bit(char *param)	{
	mpz_t MPZAUX;
	int bitrange = strtol(param,NULL,10);
	if(bitrange > 0 && bitrange <=256 )	{
		mpz_init(MPZAUX);
		mpz_pow_ui(MPZAUX,TWO,bitrange-1);
		mpz_set(min_range,MPZAUX);
		mpz_pow_ui(MPZAUX,TWO,bitrange);
		mpz_sub_ui(MPZAUX,MPZAUX,1);
		mpz_set(max_range,MPZAUX);
		gmp_fprintf(stderr,"[+] Min range: %Zx\n",min_range);
		gmp_fprintf(stderr,"[+] Max range: %Zx\n",max_range);
		mpz_clear(MPZAUX);
	}
	else	{
		fprintf(stderr,"[E] invalid bit param: %s\n",param);
		exit(0);
	}
}

void set_publickey(char *param)	{
	char hexvalue[65];
	char *dest;
	int len;
	len = strlen(param);
	dest = (char*) calloc(len+1,1);
	if(dest == NULL)	{
		fprintf(stderr,"[E] Error calloc\n");
		exit(0);
	}
	memset(hexvalue,0,65);
	memcpy(dest,param,len);
	trim(dest," \t\n\r");
	len = strlen(dest);
	switch(len)	{
		case 66:
			mpz_set_str(target_publickey.x,dest+2,16);
		break;
		case 130:
			memcpy(hexvalue,dest+2,64);
			mpz_set_str(target_publickey.x,hexvalue,16);
			memcpy(hexvalue,dest+66,64);
			mpz_set_str(target_publickey.y,hexvalue,16);
		break;
	}
	if(mpz_cmp_ui(target_publickey.y,0) == 0)	{
		mpz_t mpz_aux,mpz_aux2,Ysquared;
		mpz_init(mpz_aux);
		mpz_init(mpz_aux2);
		mpz_init(Ysquared);
		mpz_pow_ui(mpz_aux,target_publickey.x,3);
		mpz_add_ui(mpz_aux2,mpz_aux,7);
		mpz_mod(Ysquared,mpz_aux2,EC.p);
		mpz_add_ui(mpz_aux,EC.p,1);
		mpz_fdiv_q_ui(mpz_aux2,mpz_aux,4);
		mpz_powm(target_publickey.y,Ysquared,mpz_aux2,EC.p);
		mpz_sub(mpz_aux, EC.p,target_publickey.y);
		switch(dest[1])	{
			case '2':
				if(mpz_tstbit(target_publickey.y, 0) == 1)	{
					mpz_set(target_publickey.y,mpz_aux);
				}
			break;
			case '3':
				if(mpz_tstbit(target_publickey.y, 0) == 0)	{
					mpz_set(target_publickey.y,mpz_aux);
				}
			break;
			default:
				fprintf(stderr,"[E] Some invalid bit in the publickey: %s\n",dest);
				exit(0);
			break;
		}
		mpz_clear(mpz_aux);
		mpz_clear(mpz_aux2);
		mpz_clear(Ysquared);
	}
	free(dest);
}

void set_range(char *param)	{
	Tokenizer tk;
	char *dest;
	int len;
	len = strlen(param);
	dest = (char*) calloc(len+1,1);
	if(dest == NULL)	{
		fprintf(stderr,"[E] Error calloc\n");
		exit(0);
	}
	memcpy(dest,param,len);
	dest[len] = '\0';
	stringtokenizer(dest,&tk);
	if(tk.n == 2)	{
		mpz_init_set_str(min_range,nextToken(&tk),16);
		mpz_init_set_str(max_range,nextToken(&tk),16);
	}
	else	{
		fprintf(stderr,"%i\n",tk.n);
		fprintf(stderr,"[E] Invalid range expected format A:B\n");
		exit(0);
	}
	freetokenizer(&tk);
	free(dest);
}
