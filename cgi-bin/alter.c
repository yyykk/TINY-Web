#include "../yk.h"

void BodyHtml(char *content){
	sprintf(content, "%s <!DOCTYPE html>\n", content);
	sprintf(content, "%s <html lang='en'>\n", content);
	sprintf(content, "%s <head>\n", content);
	sprintf(content, "%s <meta charset='utf-8'>\n", content);
	sprintf(content, "%s <title>MYSQL</title>\n", content);
	sprintf(content, "%s <link href='../static/css/font-awesome.min.css' rel='stylesheet'>\n", content);
	sprintf(content, "%s <link href='../static/css/bootstrap.min.css' rel='stylesheet'>\n", content);
	sprintf(content, "%s <link href='../static/css/templatemo-style.css' rel='stylesheet'>\n", content);
	sprintf(content, "%s </head>\n", content);
	sprintf(content, "%s <body>\n", content);
	sprintf(content, "%s <div class='templatemo-content-container'>\n", content);
	sprintf(content, "%s <div class='templatemo-flex-row flex-content-row'>\n", content);
	sprintf(content, "%s <div class='templatemo-content-widget white-bg col-2'>\n", content);
	sprintf(content, "%s <i class='fa fa-times'></i>\n", content);
	sprintf(content, "%s <div class='square'></div>\n", content);
	sprintf(content, "%s <h2 class='templatemo-inline-block'>Tiny Web Server (mysql)</h2><hr>\n", content);
}


void TableHtml(char *content){
	sprintf(content, "%s <div class='templatemo-content-container'>\n", content);
	sprintf(content, "%s <div class='templatemo-content-widget no-padding'>\n", content);
	sprintf(content, "%s <div class='panel panel-default table-responsive'>\n", content);
}


int main(){
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	int t, flag;
	char content[MAXLINE], buf[MAXLINE], code[MAXLINE];
	BodyHtml(content);	
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql, "localhost", "root", "mysql", "test", 0, NULL, 0)){
		sprintf(content, "%sError connecting to MySql\n", content);
	}else{
		printf(content, "%s<p>Connected MySql Successful<p>\n", content);
	}
	if((strcpy(code, getenv("QUERY_STRING"))) != 0){
		flag = mysql_real_query(&mysql, code, (unsigned int)strlen(code));
		if(flag){
			sprintf(content, "%s<p>[%s]...failed<p>\n", content, code);
		}else{			
			sprintf(content, "%s<p>[%s]...success<p>\n", content, code);
			sprintf(content, "%s</div></div></div>\n", content);
			TableHtml(content);
			strcpy(code, "select * from testData");
			mysql_real_query(&mysql, code, (unsigned int)strlen(code));
			res = mysql_store_result(&mysql);
			field = mysql_fetch_fields(res);
			sprintf(content, "%s <table id = 'myTable' class='table table-striped table-bordered templatemo-user-table'>\n", content);
			sprintf(content, "%s<thead><tr>", content);
			for(t = 0; t < mysql_num_fields(res); t++){
				sprintf(content, "%s<th>%s</th>\t", content, field[t].name);
			}
			sprintf(content, "%s</tr></thead>\n", content);
			while(row = mysql_fetch_row(res)){
				sprintf(content, "%s<tr>", content);
				for(t = 0; t < mysql_num_fields(res); t++){
					sprintf(content, "%s<td>%s</td>\t", content, row[t]);
				}
				sprintf(content, "%s</tr>\n", content);
			}
			sprintf(content, "%s</table></div></div></div></body></html>\n", content);
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




















