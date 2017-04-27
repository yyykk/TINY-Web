#include "../csapp.h"
int main(){
	char content[MAXLINE], buf[MAXLINE], argv[32][MAXLINE];
	char *p, *temp;
	int result, argc = 0;
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
		sprintf(content, "%d", result); 
	}else{
		sprintf(content, "variable error");
	}
	
	sprintf(buf, "%sContent-legth: %d\r\n", buf, (int)strlen(content));
	sprintf(buf, "%sContent-type: text/html\r\n\r\n", buf);
	printf("%s", buf);
	fflush(stdout);
	printf("%s", content);
	fflush(stdout);
	return 0;
}
