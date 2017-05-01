#include "mysql/mysql.h"
#include "../csapp.h"

int main(){
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	int t, flag;
	char content[MAXLINE], buf[MAXLINE], code[MAXLINE];	
	mysql_init(&mysql);
	sprintf(content, "%s<center><p>Server: Tiny Web Server (connect to mysql)</p>\r\n", content);
	if(!mysql_real_connect(&mysql, "localhost", "root", "mysql", "test", 0, NULL, 0)){
		sprintf(content, "%sError connecting to MySql\n", content);
	}else{
		printf(content, "%sConnected MySql Successful\n", content);
	}
	if((strcpy(code, getenv("QUERY_STRING"))) != 0){
		flag = mysql_real_query(&mysql, code, (unsigned int)strlen(code));
		if(flag){
			sprintf(content, "%s[%s]...failed\n", content, code);
		}else{			
			sprintf(content, "%s[%s]...success\n", content, code);
			strcpy(code, "select * from testData");
			mysql_real_query(&mysql, code, (unsigned int)strlen(code));
			res = mysql_store_result(&mysql);
			field = mysql_fetch_fields(res);
			sprintf(content, "%s<p>", content);
			for(t = 0; t < mysql_num_fields(res); t++){
				sprintf(content, "%s%s\t", content, field[t].name);
			}
			sprintf(content, "%s</p>", content);
			while(row = mysql_fetch_row(res)){
				sprintf(content, "%s<p>", content);
				for(t = 0; t < mysql_num_fields(res); t++){
					sprintf(content, "%s%s\t\t", content, row[t]);
				}
				sprintf(content, "%s</p>\n", content);
			}
		}
		
	}else{
		sprintf(content, "variable error\n");
	}
	sprintf(content, "%s</center>", content);
	sprintf(buf, "%sContent-legth: %d\r\n", buf, (int)strlen(content));
	sprintf(buf, "%sContent-type: text/html\r\n\r\n", buf);
	printf("%s", buf);
	fflush(stdout);
	printf("%s", content);
	fflush(stdout);
	mysql_close(&mysql);
	return 0;	
}




















