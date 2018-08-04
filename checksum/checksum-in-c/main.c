#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

#define LOCK(x) pthread_mutex_lock(x)
#define UNLOCK(x) pthread_mutex_unlock(x)

static pthread_mutex_t mt = PTHREAD_MUTEX_INITIALIZER;


struct HASH{
	char *path;
	size_t digest_size;
	unsigned char *hash;
};


static void *t_md5_func(void *arg){
	struct HASH *obj = (struct HASH *)arg;
	obj->hash = (unsigned char *) malloc( (obj->digest_size) * sizeof(char) );

	FILE *fp;
	char buf[512];
	size_t numRead;
	MD5_CTX md5;

	if( (fp = fopen(obj->path , "r")) == NULL){
		perror("fopen error\n");
		exit(1);
	}

	MD5_Init(&md5);
	while( (numRead = fread(buf , 1 , 512 , fp) ) != 0){
		MD5_Update(&md5 , buf , (unsigned long int) numRead);
	}
	MD5_Final(obj->hash , &md5);

	LOCK(&mt);
	printf("MD5 \n");
	for(int i=0 ; i<obj->digest_size ; i++){
		printf("%02X" , obj->hash[i]);
	}
	printf("\t%s\n" , obj->path);
	UNLOCK(&mt);

	fclose(fp);
	return NULL;
}

static void *t_sha256_func(void *arg){
	struct HASH *obj = (struct HASH *)arg;
	obj->hash = (unsigned char *) malloc( (obj->digest_size) * sizeof(char) );

	FILE *fp;
	char buf[512];
	size_t numRead;
	SHA256_CTX sha256;

	if( (fp = fopen(obj->path , "r")) == NULL){
		perror("fopen error\n");
		exit(1);
	}

	SHA256_Init(&sha256);
	while( (numRead = fread(buf , 1 , 512 , fp) ) != 0){
		SHA256_Update(&sha256 , buf , (unsigned long int) numRead);
	}
	SHA256_Final(obj->hash , &sha256);

	LOCK(&mt);
	printf("SHA256 \n");
	for(int i=0 ; i<obj->digest_size ; i++){
		printf("%02X" , obj->hash[i]);
	}
	printf("\t%s\n" , obj->path);
	UNLOCK(&mt);

	fclose(fp);
	return NULL;
}

static void *t_sha512_func(void *arg){
	struct HASH *obj = (struct HASH *)arg;
	obj->hash = (unsigned char *) malloc( (obj->digest_size) * sizeof(char) );

	FILE *fp;
	char buf[512];
	size_t numRead;
	SHA512_CTX sha512;

	if( (fp = fopen(obj->path , "r")) == NULL){
		perror("fopen error\n");
		exit(1);
	}

	SHA512_Init(&sha512);
	while( (numRead = fread(buf , 1 , 512 , fp) ) != 0){
		SHA512_Update(&sha512 , buf , (unsigned long int) numRead);
	}
	SHA512_Final(obj->hash , &sha512);

	LOCK(&mt);
	printf("SHA512 \n");
	for(int i=0 ; i<obj->digest_size ; i++){
		printf("%02X" , obj->hash[i]);
	}
	printf("\t%s\n" , obj->path);
	UNLOCK(&mt);

	fclose(fp);
	return NULL;
}


int main(int argc , char *argv[]){
	pthread_t t_md5 , t_sha256 , t_sha512;
	int err;

	if( argc != 2 || strcmp(argv[1] , "--help") == 0){
		perror("input error\n");
		printf("input form : %s [path/file_name]\n" , argv[0]);
		exit(1);
	}

	/*initialize every struct path and digest_size*/
	struct HASH md5;
	md5.path = argv[1];
	md5.digest_size = MD5_DIGEST_LENGTH;

	struct HASH sha256;
	sha256.path = argv[1];
	sha256.digest_size = SHA256_DIGEST_LENGTH;

	struct HASH sha512;
	sha512.path = argv[1];
	sha512.digest_size = SHA512_DIGEST_LENGTH;


	/*pthread_create*/
	err = pthread_create(&t_md5 , NULL , t_md5_func , (void *)&md5);
	if(err != 0){
		perror("pthread_create t_md5 error\n");
		exit(1);
	}

	err = pthread_create(&t_sha256 , NULL , t_sha256_func , (void *)&sha256);
	if(err != 0){
		perror("pthread_create t_sha256 error\n");
		exit(1);
	}

	err = pthread_create(&t_sha512 , NULL , t_sha512_func , (void *)&sha512);
	if(err != 0){
		perror("pthread_create t_sha512 error\n");
		exit(1);
	}

	/*pthread_join*/
	err = pthread_join(t_md5 , NULL);
	if(err != 0){
		perror("pthread_join t_md5 error\n");
		exit(1);
	}

	err = pthread_join(t_sha256 , NULL);
	if(err != 0){
		perror("pthread_join t_sha256 error\n");
		exit(1);
	}

	err = pthread_join(t_sha512 , NULL);
	if(err != 0){
		perror("pthread_join t_sha512 error\n");
		exit(1);
	}

	exit(EXIT_SUCCESS);
}

