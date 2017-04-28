#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "mysql/mysql.h"
#include "../csapp.h"

char* conver(char *code){
	int i;		
	for(i = 0; i < strlen(code); ++i){
		if(code[i] == '%'){
			code[i] = ' ';
			code[++i] = ' ';
			code[++i] = ' ';
		}
	}
	return code;
}


int main(){
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int t, flag;
	char *code;
	char content[MAXLINE], buf[MAXLINE];
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql, "localhost", "root", "mysql", "test", 0, NULL, 0)){
		printf("Error connecting to MySql\n");
	}else{
		printf("Connected MySql Successful\n");
	}
	if((code = getenv("QUERY_STRING")) != NULL){
		code = conver(code);
		flag = mysql_real_query(&mysql, code, (unsigned int)strlen(code));
		if(flag){
			sprintf(content, "[%s]...failed\n", code);
		}else{			
			sprintf(content, "[%s]...success\n", code);
			res = mysql_store_result(&mysql);
			while(row = mysql_fetch_row(res)){
				for(t = 0; t < mysql_num_fields(res); t++){
					sprintf(content, "%s\t", row[t]);
				}
				sprintf(content, "\n");
			}
		}
		
	}else{
		sprintf(content, "variable error");
	}
	sprintf(buf, "%sContent-legth: %d\r\n", buf, (int)strlen(content));
	sprintf(buf, "%sContent-type: text/html\r\n\r\n", buf);
	printf("%s", buf);
	fflush(stdout);
	printf("%s", content);
	fflush(stdout);
	mysql_close(&mysql);
	return 0;	
}




















