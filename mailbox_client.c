/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "mailbox.h"
#include <rpc/rpc.h>


void
mailbox_1(char *host)
{
	CLIENT *clnt;
	void  *result_1;
	char * start1_1_arg;
	void  *result_2;
	char * quit1_1_arg;
	void  *result_3;
	struct message  insert_message1_1_arg;
	char * *result_4;
	struct usermsgid  retrieve_message_1_arg;
	struct listmessages  *result_5;
	char * list_all_messages_1_arg;
	void  *result_6;
	struct usermsgid  delete_message_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, MAILBOX, ver, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = start1_1(&start1_1_arg, clnt);
	if (result_1 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = quit1_1(&quit1_1_arg, clnt);
	if (result_2 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_3 = insert_message1_1(&insert_message1_1_arg, clnt);
	if (result_3 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_4 = retrieve_message_1(&retrieve_message_1_arg, clnt);
	if (result_4 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_5 = list_all_messages_1(&list_all_messages_1_arg, clnt);
	if (result_5 == (struct listmessages *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_6 = delete_message_1(&delete_message_1_arg, clnt);
	if (result_6 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}



void
mailbox_2(char *host)
{
	CLIENT *clnt;

	void  *result_1;
	str start1_1_arg = strdup("ishaan");

	void  *result_2;
	str quit1_1_arg = strdup("ishaan");
	
	void  *result_3;
	message  insert_message1_1_arg = {"ishaan\n", 0, "hello world\n"};

	str *result_4;
	usermsgid  retrieve_message_1_arg = {"ishaan\n", 0};

	struct listmessages  *result_5;
	str list_all_messages_1_arg = strdup("ishaan\n");

	void  *result_6;
	struct usermsgid  delete_message_1_arg = {"ishaan\n", 0};
	
	clnt = clnt_create (host, MAILBOX, ver, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

	printf("result1 starting.. \n");
	result_1 = start1_1(&start1_1_arg, clnt);

	if (result_1 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	
	printf("result2 starting\n");
	result_2 = quit1_1(&quit1_1_arg, clnt);
	if (result_2 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	printf("result3 starting\n");
	fflush(0);
	result_3 = insert_message1_1(&insert_message1_1_arg, clnt);
	if (result_3 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	printf("trying to retrieve message");

	result_4 = retrieve_message_1(&retrieve_message_1_arg, clnt);
	if (result_4 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("retrieved message: %s", *result_4);
	fflush(0);
	
	result_5 = list_all_messages_1(&list_all_messages_1_arg, clnt);
	if (result_5 == (struct listmessages *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("first messages\n\t%s", result_5->list[0]);
	fflush(0);
	
	result_6 = delete_message_1(&delete_message_1_arg, clnt);
	if (result_6 == (void *) NULL) {
		clnt_perror (clnt, "call failed");
	}
		
	printf("done?");
	fflush(0);
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}




int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	mailbox_2 (host);
exit (0);
}
