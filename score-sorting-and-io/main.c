#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_DATA_BUF_SIZE 2048
#define WRITE_DATA_BUF_SIZE 1024
#define LINE_BUF_SIZE 1024
#define FORMAT_BUF 10
#define FORMAT_BUF_SIZE 2048


void display(char *);
int get_line_num(char *);
void line_buf_malloc(char ** , int);
void break_line(char *, char **, int);
void add_total_item_and_sum();
void sorting_with_sum(char ** , int);
void format_buf_malloc(char **);
void format_break_and_concat(char **, char ** , int);
int extract_sum_item(char *line_str);
void output_file(FILE * , char **);

int main(){
	printf("process start\n");
	char data[READ_DATA_BUF_SIZE];
	char *line_buf[50];
	char *format_buf[FORMAT_BUF];
	int line_num = 0;

	FILE *new = fopen("sorted_score.txt" , "w+");
	FILE *raw = fopen("score_ANSI.txt" , "r");
	fread(data , sizeof(char) , READ_DATA_BUF_SIZE , raw);

	/*計算原始成績表有幾行*/
	line_num = get_line_num(data);

	/*以行數來宣告及 malloc char *陣列 */
	line_buf_malloc(line_buf , line_num);

	/*把每一行設定給對應 line_buf[ index ] 中的 char * 指標*/
	break_line(data , line_buf , line_num);

	/*計算每一行的科目分數總分，並加上一個項目 Total*/
	add_total_item_and_sum(line_buf , line_num);

	/*每一行以 qsort 來比較 Total 總分的大小，並作排序，從大排到小*/
	sorting_with_sum(line_buf , line_num);

	/*新格式的 char * 指標陣列 malloc */
	format_buf_malloc(format_buf);

	/*將原排序好的資料轉換成新格式*/
	format_break_and_concat(format_buf , line_buf , line_num);

	/*將新格式資料輸出到 sorted_score.txt 檔案中*/
	output_file(new , format_buf);

	fclose(new);
	fclose(raw);
	//display(read_data);
}


void output_file(FILE *new , char *format_buf[]){
	for(int i=0 ; i<FORMAT_BUF ; i++){
		fwrite(format_buf[i] , sizeof(char) , strlen(format_buf[i]) , new);
	}
}

void format_break_and_concat(char *format_buf[] , char *line_buf[] , int line_num){
	/*
	座號	 姓名	性別	國語	數學	社會	自然	生倫	健教9 個 tiem 加上 
	1 個 Total item
	*/

	char *item[FORMAT_BUF];
	for(int i=0 ; i<FORMAT_BUF ; i++){
		item[i] = malloc(sizeof(char) * 16);
	}
	for(int line=0 ; line<line_num ; line++){
		sscanf(line_buf[line] , "%s %s %s %s %s %s %s %s %s %s" ,\
		 item[0] , item[1] , item[2] , item[3] , item[4] , item[5] , item[6] , item[7] , item[8] , item[9]);
		if(line){
			for(int i=0 ; i<FORMAT_BUF ; i++){
				strcat(format_buf[i] , "\t");
				strcat(format_buf[i] , item[i]);
			}
		}
		else{
			for(int i=0 ; i<FORMAT_BUF ; i++){
				strcpy(format_buf[i] , item[i]);
			}
		}
	}

	for(int i=0 ; i<FORMAT_BUF ; i++){
		strcat(format_buf[i] , "\n");
	}
	free(line_buf);
}


void format_buf_malloc(char *format_buf[]){
	for(int i=0 ; i<FORMAT_BUF ; i++){
		format_buf[i] = malloc(sizeof(char) * FORMAT_BUF_SIZE);
		if( !format_buf[i]){
			exit(1);
		}
		// sprintf(format_buf[i] , "this is line %d" , i);
	}
	// for(int j=0 ; j<FORMAT_BUF ; j++){
	// 	printf("%s\n" , format_buf[j]);
	// }
	return;
}

int extract_sum_item(char *line_str){
	int sum = 0;
	sscanf( line_str , "%*s %*s %*s %*d %*d %*d %*d %*d %*d %d" , &sum);
	//printf("sum : %d\n" , sum);
	return sum;
}

int compar(void const *a , void const *b){
	int int_a = extract_sum_item( *((char **) a));
	int int_b = extract_sum_item( *((char **) b));
	if(int_a > int_b){
		return -1;
	}
	if(int_a < int_b){
		return 1;
	}
	return 0;
}


void sorting_with_sum(char *line_buf[] , int line_num){
	qsort(line_buf+1 , line_num - 1 , sizeof(char **) , compar);

	for(int i=0 ; i<line_num ; i++){
		printf("%s\n" , line_buf[i]);
	}
}

void add_total_item_and_sum(char *line_buf[] , int line_num){
	//國語	數學	社會	自然	生倫	健教
	int chinese;
	int math;
	int social;
	int nature;
	int moral;
	int health;
	for(int i=0 ; i<line_num ; i++){
		if(i != 0){
			char temp[16];
			sscanf(line_buf[i] , "%*s %*s %*s %d %d %d %d %d %d" , &chinese , &math , &social , &nature , &moral , &health );
			int total = (chinese + math + social + nature + moral + health);
			sprintf(temp , "%s%d" , " " , total);
			strcat(line_buf[i] , temp);
		}
		else{
			strcat(line_buf[i] , " Total");
		}
	}
	// for(int i=0 ; i<line_num ; i++){
	// 	printf("%s\n" , line_buf[i]);
	// }
}

void break_line(char *data , char *line_buf[] , int line_num){
	int data_length = strlen(data);
	char str_temp[1024];
	int str_temp_count = 0;
	int count = 0;
	for(int i=0 ; i<data_length ; i++){
		if(data[i] == '\n'){
			//str_temp[str_temp_count++] = data[i];
			str_temp[str_temp_count] = '\0';
			strcpy(line_buf[count++] , str_temp);
			memset(str_temp , sizeof(char) , strlen(str_temp));
			str_temp_count = 0;
			continue;
		}
		str_temp[str_temp_count++] = data[i];
	}
	str_temp[str_temp_count] = '\0';
	strcpy(line_buf[count] , str_temp);
	return;
}


void line_buf_malloc(char *line_buf[] , int line_num){
	char temp[100];
	for(int i=0 ; i<line_num ; i++){
		line_buf[i] = malloc( sizeof(char) * 1024 );
		if(!line_buf){
			exit(1);
		}
		//sprintf(temp , "this is line %d\n" , i);
		strcpy(line_buf[i] , temp);
		memset(temp , sizeof(char) , strlen(temp));
	}
	return;
}

int get_line_num(char *data){
	int length = strlen(data);
	int count = 0;
	for(int i=0 ; i<length ; i++){
		if(data[i] == '\n'){
			count++;
		}
	}
	count++;
	//printf("total %d lines\n" , count);
	/*the last line without '\n' ,  so we need to add 1 for the last line*/
	return count;
}

void display(char *data){
	int length = strlen(data);
	for(int i=0 ; i<length ; i++){
		printf("%c" , data[i]);
	}
	return;
}
