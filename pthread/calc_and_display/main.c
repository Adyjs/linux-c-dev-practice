#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define LOCK(x) pthread_mutex_lock(x)
#define UNLOCK(x) pthread_mutex_unlock(x)
#define WAIT(a , b) pthread_cond_wait(a , b)
#define SIGNAL(a) pthread_cond_signal(a)

static pthread_mutex_t mt = PTHREAD_MUTEX_INITIALIZER;
//static pthread_mutex_t cond_mt = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static volatile int count = 0;
static int mod;

struct Obj{
	int loop;
	int index;
	int size;
	int num_consume;
	int *buf;
	bool calc_done;
};

static void initial(struct Obj *obj){
	memset(obj , 0 , sizeof(struct Obj));
}

// static void remalloc(struct Obj *obj){
// 	if( obj->index > ((obj->size) >> 2)){
// 		obj->size <<= 1;
// 		obj->buf = realloc(obj->buf , obj->size);
// 		printf("obj size doubled : %d\n" , obj->size);
// 	}
// 	return;
// }

static void display(struct Obj *obj){
	// for(int i=0 ; i<(obj->size) ; i++){
	// 	printf("i:%d , %d\n" , i , obj->buf[i]);
	// }
	printf("\nloop:%d\nindex:%d\nsize:%d\n" , obj->loop , obj->index , obj->size);
}

static void *t1_func(void *arg){
	struct Obj *obj = (struct Obj *)arg;
	while(1){
		LOCK(&mt);
		count++;
		if( count % mod == 0 ){
			if((obj->num_consume) == obj->size){
				WAIT(&cond , &mt);				
			}
			printf("producing : %d\n" , count);
			(obj->buf)[(obj->index)%(obj->size)] = count;		/*circular input num into malloc memory*/
			obj->num_consume +=1;
			obj->index += 1;
		}
		UNLOCK(&mt);
		
		if(count == (obj->loop)){
			obj->calc_done = true;
			break;
		}
	}
	return NULL;
}

static void *t2_func(void *arg){
	struct Obj *obj = (struct Obj *)arg;
	int index = 0;
	while(1){
		sleep(1);
		while((obj->num_consume) > 0){
			printf("consuming buf[%d]: %d\n" , index % (obj->size) , obj->buf[index % (obj->size)]);
			if(obj->num_consume > 0){
				obj->num_consume -= 1;
				index++;
			}
		}
		SIGNAL(&cond);
		if( (obj->calc_done) && (obj->num_consume) == 0){
			break;
		}
	}

	return NULL;
}



int main(int argc , char *argv[]){
	pthread_t t1 , t2;
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
		obj.num_consume = 0;
		obj.size = 10;
		obj.buf = malloc( obj.size * sizeof(int));
		obj.calc_done = false;

		err = pthread_create(&t1 , NULL , t1_func , (void *)&obj);
		if(err != 0){
			perror("pthread_create 1 error\n");
			exit(1);
		}

		err = pthread_create(&t2 , NULL , t2_func , (void *)&obj);
		if(err != 0){
			perror("pthread_create 2 error\n");
			exit(1);
		}

		err = pthread_join(t1 , NULL);
		if(err != 0){
			perror("pthread_join 1 error\n");
			exit(1);
		}

		err = pthread_join(t2 , NULL);
		if(err != 0){
			perror("pthread_join 2 error\n");
			exit(1);
		}
	}
	display(&obj);
	exit(EXIT_SUCCESS);

}