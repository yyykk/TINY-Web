#include "../yk.h"
int main(){
	char content[MAXLINE], buf[MAXLINE], argv[32][MAXLINE];
	char *p, *temp;
	int result, argc = 0;
	sprintf(content, "%s<center><p>Server: Tiny Web Server (CGI)</p>\r\n", content);
	sprintf(content, "%s<p></p>\r\n", content);
	if((temp = getenv("QUERY_STRING")) != NULL){
		while((p = strchr(temp, '&')) != NULL){
			*p = '\0';
			strcpy(argv[argc], temp);
			temp = p + 1;
			argc += 1;
		}
		strcpy(argv[argc], temp);
		argc += 1;
		for(; argc >= 0; argc--){
			result += atoi(argv[argc]);
		}
		sprintf(content, "%s<p>result == %d</p>\n", content, result); 
	}else{
		sprintf(content, "%s<p>variable error</p>\n", content);
	}
	sprintf(content, "%s</center>\r\n", content);
	sprintf(buf, "%sContent-legth: %d\r\n", buf, (int)strlen(content));
	sprintf(buf, "%sContent-type: text/html\r\n\r\n", buf);
	printf("%s", buf);
	fflush(stdout);
	printf("%s", content);
	fflush(stdout);
	return 0;
}
