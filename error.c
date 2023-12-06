#include "libft/libft.h"
#include <unistd.h>

void error(char *msg, char *subject)
{
	char str[1000];
	char *actual;
	int i;
	
	i = 0;
	actual = str;
	str[0] = '\0';
	while (*msg)
		*actual++ = *msg++;
	while (*subject)
		*actual++ = *subject++;
	*actual++ = '\n';
	*actual = '\0';
	while(str[i])
		write(1,&str[i++],1);
}
