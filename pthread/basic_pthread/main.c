#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define LOCK(x) pthread_mutex_lock(x)
#define UNLOCK(x) pthread_mutex_unlock(x)

static pthread_mutex_t mt = PTHREAD_MUTEX_INITIALIZER;
static volatile int count = 0;
static int mod;

struct Obj{
	int loop;
	int index;
	int size;
	int *buf;
};

static void initial(struct Obj *obj){
	memset(obj , 0 , sizeof(struct Obj));
}

static void remalloc(struct Obj *obj){
	if( obj->index > ((obj->size) >> 2)){
		obj->size <<= 1;
		obj->buf = realloc(obj->buf , obj->size);
		printf("obj size doubled : %d\n" , obj->size);
	}
	return;
}

static void display(struct Obj *obj){
	for(int i=0 ; i<(obj->index) ; i++){
		printf("i:%d , %d\n" , i , obj->buf[i]);
	}
	printf("loop:%d\nindex:%d\nsize:%d\n" , obj->loop , obj->index , obj->size);
}

static void *t1_func(void *arg){
	struct Obj *obj = (struct Obj *)arg;
	for(int i=0 ; i<(obj->loop) ; i++){
		//pthread_mutex_lock(&mt);
		LOCK(&mt);
		count++;
		UNLOCK(&mt);
		//pthread_mutex_unlock(&mt);
		if(count != 0 && count % mod == 0){
			(obj->buf)[(obj->index)] = count;
			obj->index += 1;
			remalloc(obj);
		}
	}
	return NULL;
}



int main(int argc , char *argv[]){
	pthread_t t1;
	int err;
	struct Obj obj;
	if(argc != 3 || strcmp(argv[1] , "--help") == 0 ){
		perror("input error\n");
		exit(1);
	}
	else{
		mod = strtol(argv[2] , NULL , 10);
		initial(&obj);
		obj.loop = strtol(argv[1] , NULL , 10);
		obj.index = 0;
		obj.size = 10;
		obj.buf = malloc( obj.size * sizeof(int));

		err = pthread_create(&t1 , NULL , t1_func , (void *)&obj);
		if(err != 0){
			perror("pthread_create error\n");
			exit(1);
		}

		err = pthread_join(t1 , NULL);
		if(err != 0){
			perror("pthread_join error\n");
			exit(1);
		}
	}
	display(&obj);
	exit(EXIT_SUCCESS);

}