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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Limits and keywords */
const int CHARLIMIT = 80;
const int BOXMSGLIMIT = 100;
const int USERMSGLIMIT = 20;

/* Stores users and length of users array */
static str * users;
int usersl = 0;
int usersinit = 0;


/* Stores messages and length of messages array */
static message ** mailbox;
int mailboxl = 0;
int mailboxinit = 0;

/***
	Begin functions
***/

/* Adds `*s` to the end of the user list and increments the usersl (length)*/
void *
start1_1_svc(char* *argp, struct svc_req *rqstp)
{
	pthread_mutex_lock(&mutex);
	
	str s = strdup(*argp);
	str * username = &s;

	printf("Trying to add a user now");	
	if (usersinit == 0)
	{
		users = calloc(1, sizeof(str *));
		usersinit = 1;
	}
	else if (index_of_user(username) == -1)
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
	pthread_mutex_lock(&mutex);	
	
	str s = strdup(*argp);
	str * username = &s;


	/* Remove user from users array and decrement array length */
	printf("Removing user '%s' from all databases\n", *username);
	remove_user(username);
	remove_messages(username);

	static char * result;
	
	pthread_mutex_unlock(&mutex);

	return (void *) &result;
}

/* Remove user from users array and decrement array length. 
	Leaves users array in contigous state. */
int remove_user(str * username) 
{
	printf("Trying to delete user '%s'", *username);
	
	int index = index_of_user(username);
	
	if (index == -1)
	{
		printf("but user '%s' doesn't exist\n", *username);
		return 0;
	}
 	
	// Shift left from index -> end of array
	int i;
	for (i = index; i < usersl-1; i++)
	{
		users[i] = users[i+1];
	}
	
	// set this pointer value to null and deallocate it, decrement usersl
	users[--usersl] = (void *) 0;
	free(users[usersl]);	
	
	printf(" ... deleted user '%s'\n", *username);

	return 1;	
}

/* Remove all messages associated with user from messages array. 
	Leaves messages array in contigous state.  */
int remove_messages(str * username)
{
	printf("Removing messages for '%s' ..\n", *username);
	int i;
	for (i = 0; i < mailboxl; i++)
	{
		if (strcmp(*username, mailbox[i]->user) == 0)
		{
			mailboxpop_at(i);
		}
	}
	
	printf("\n");

	return 1;	
}


/* Adds *s to the end of the message list and increments the mailboxl (length) */
void *
insert_message1_1_svc(struct message *argp, struct svc_req *rqstp)
{
	pthread_mutex_lock(&mutex);

	message * m = argp;

	printf("Trying to add message '%.7s... to mailbox ", m->msg);

	// Make space for new message
	if (mailboxinit == 0)
	{
		mailbox = calloc(1, sizeof(message *));
		mailboxinit = 1;
	}
	if (mailboxl + 1 > BOXMSGLIMIT)
	{
		mailboxpop(); 	// decremenets length of mailbox (mailboxl)
	}
	else
	{
		mailbox[mailboxl] = (message*) calloc(1, sizeof(message*));
	}

	// Add new message	
	mailbox[mailboxl++] = m;

	printf(" .. successfully added message '%.25s'(cntd)\n", mailbox[mailboxl-1]->msg);
		
	static char * result;
	
	pthread_mutex_unlock(&mutex);

	return (void *) &result;
}

/* Simple message lookup */
char **
retrieve_message_1_svc(struct usermsgid *argp, struct svc_req *rqstp)
{
	pthread_mutex_lock(&mutex);	

	usermsgid * o = argp;

	printf("Trying to retrieve message %s : %d .. ", o->user, o->msgid);
	
	int i;
	for (i = 0; i < mailboxl; i++)
	{	
		if (o->msgid == mailbox[i]->msgid)
		{
			
			if (strcmp(o->user, mailbox[i]->user) == 0)
			{
				printf("found it!\n");
				
				pthread_mutex_unlock(&mutex);
				return &mailbox[i]->msg;
			} 
		} 	
	}	
	
	printf("couldn't find it..\n");
	
	pthread_mutex_unlock(&mutex);	

	return calloc(1, sizeof(str));
}

/* Finds all messages for a specific user and packages it into a listmessages struct */
struct listmessages *
list_all_messages_1_svc(char* *argp, struct svc_req *rqstp)
{
	pthread_mutex_lock(&mutex);

	static struct listmessages result = {0};
	
	printf("User: %s\n", *argp);

	str s = strdup(*argp);
	str * username = &s;

	printf("Printing %s's messages .. ", *username);

	str * temp = calloc(1, sizeof(str*));

	int k = 0;
	int i;
	for (i = 0; i < mailboxl; i++)
	{
		if (strcmp(*username, mailbox[i]->user) == 0)
		{	
			temp[k] = calloc(1, sizeof(str));
			temp[k++] = mailbox[i]->msg;	
		}
	}	

	printf("there are %d of them:\n", k);

	result.list = calloc(1, sizeof(str *));
	for (i = 0; i < k; i++)
	{
		result.list[i] = calloc(1, sizeof(str));
		result.list[i] = temp[i];
		printf("\t%s\n", temp[i]);
	}
	
	printf("\n");	

	pthread_mutex_unlock(&mutex);

	return &result;
}

void *
delete_message_1_svc(struct usermsgid *argp, struct svc_req *rqstp)
{
	pthread_mutex_lock(&mutex);

	usermsgid * o = argp;

	printf("Trying to delete message (id: %d) .. ", o->msgid);
	
	int i;
	for (i = 0; i < mailboxl; i++)
	{
		if (o->msgid == mailbox[i]->msgid)
		{
			if (strcmp(o->user, mailbox[i]->user) == 0)
			{
				printf(" .. deleting message '%.8s...i\n", mailbox[i]->msg);
				mailboxpop_at(i);	
			}
		} 	
	}
	
	printf("\n");

	static char * result;

	pthread_mutex_unlock(&mutex);

	return (void *) &result;
}


/* Shifts all the elements in this array to the left by 1 popping off the oldest element */
int mailboxpop()
{
	int i;
	for (i = 0; i < mailboxl-1; i++)
	{
		mailbox[i] = mailbox[i+1];
	}
	mailboxl--;
}

/* deletes the element at the `index` and 
	shifts the mailbox[i+1..n] to mailbox[i..n-1] and decrements n */  
int mailboxpop_at(int index)
{		
	printf(" \t.. deleting message '%.8s...\n", mailbox[index]->msg); 

	for (; index < mailboxl-1; index++)
	{
		mailbox[index] = mailbox[index+1];	
	} 
	
	// set this pointer value to null and deallocate it, decrement mailboxl
	mailbox[--mailboxl] = (void *) 0;
	free(mailbox[mailboxl]);

	return 1;
}
