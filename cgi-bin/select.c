#include "../yk.h"

void Html(char *content){
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
	sprintf(content, "%s <div class='templatemo-content-widget no-padding'>\n", content);
	sprintf(content, "%s <div class='panel panel-default table-responsive'>\n", content);
}

void script(char *content){
	sprintf(content, "%s <script>\n", content);
	sprintf(content, "%s function insRow(){\n", content);
	sprintf(content, "%s var tab = document.getElementById('myTable');\n", content);
	sprintf(content, "%s var x= tab.insertRow(tab.rows.length);\n", content);
	sprintf(content, "%s for (i = 0; i < tab.rows.item(0).cells.length; i++){\n", content);
	sprintf(content, "%s var y = x.insertCell(i);\n", content);
	sprintf(content, "%s y.innerHTML = 'new';\n", content);
	sprintf(content, "%s }}</script>\n", content);
}

int main(){
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	int t, flag;
	char content[MAXLINE], buf[MAXLINE], code[MAXLINE] = "select * from testData";	
	mysql_init(&mysql);
	Html(content);
	if(!mysql_real_connect(&mysql, "localhost", "root", "mysql", "test", 0, NULL, 0)){
		sprintf(content, "%sError connecting to MySql\n", content);
	}else{
		strcpy(code, getenv("QUERY_STRING"));
		flag = mysql_real_query(&mysql, code, (unsigned int)strlen(code));
		if(flag){
			sprintf(content, "%s[%s]...failed\n", content, code);
		}else{			
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
			sprintf(content, "%s</table></div></div></div>\n", content);
			script(content);
			sprintf(content, "%s</body></html>\n", content);
		}
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




















