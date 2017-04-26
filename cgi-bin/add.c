#include "../csapp.h"
int main(){
	char content[MAXLINE], buf[MAXLINE], arg1[MAXLINE], arg2[MAXLINE];
	char *p, *temp; 	
	int a, b, c;
	if((temp = getenv("QUERY_STRING")) != NULL){
		p = strchr(temp, '&');
		*p = '\0';
		strcpy(arg1, temp);
		strcpy(arg2, p + 1);
		a = atoi(arg1);
		b = atoi(arg2);
		c = a + b;
		sprintf(content, "%d", c); 
	}else{
		sprintf(content, "variable error");
	}
	
	sprintf(buf, "HTTP/1.0 200 OK\r\n");
	sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
	sprintf(buf, "%sContent-legth: %d\r\n", buf, (int)strlen(content));
	sprintf(buf, "%sContent-type: text/html\r\n\r\n", buf);
	printf("%s", buf);
	fflush(stdout);
	printf("%s", content);
	fflush(stdout);
	return 0;
}
