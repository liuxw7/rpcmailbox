/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "mailbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


typedef char * str;
typedef str * messages; 


/* Adds `*s` to the end of the user list and increments the usersl (length)*/
void *
start1_1_svc(char* *argp, struct svc_req *rqstp)
{
	pthread_mutex_lock(&mutex);
	
	str * username = argp;

	printf("Trying to add a user now");	
	if (index_of_user(username) == -1 || usersl == 0)
	{
		// make space, add the username in, and increment length of users
		users[usersl] = calloc(1, sizeof(char*));
		users[usersl++] = *username;
		
		printf(". Successfully adding user '%s'\n", *username);	
	}
	else
	{
		printf(" but user '%s' already exists .. didn't add user\n", *username);
	}	
 	
 	static char * result;
	
	pthread_mutex_unlock(&mutex);

	return (void *) &result;
}

/* Gets the index of a user in users, -1 if it doesn't exist */
int index_of_user(str *username)
{
	int i;
	for (i = 0; i < usersl; i++)
	{
		//printf("is %s == %s\n", *s, users[i]);

		if (strcmp(*username, users[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}

/* Remove user from users array and decrement array length. 
	Leaves users array in contigous state. */
void *
quit1_1_svc(char* *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}

void *
insert_message1_1_svc(struct message *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}

char **
retrieve_message_1_svc(struct usermsgid *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return &result;
}

struct listmessages *
list_all_messages_1_svc(char* *argp, struct svc_req *rqstp)
{
	static struct listmessages  result;

	/*
	 * insert server code here
	 */

	return &result;
}

void *
delete_message_1_svc(struct usermsgid *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}
