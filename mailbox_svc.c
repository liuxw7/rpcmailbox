/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "mailbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
mailbox_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		char *start1_1_arg;
		char *quit1_1_arg;
		struct message insert_message1_1_arg;
		struct usermsgid retrieve_message_1_arg;
		char *list_all_messages_1_arg;
		struct usermsgid delete_message_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case START1:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) start1_1_svc;
		break;

	case QUIT1:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) quit1_1_svc;
		break;

	case INSERT_MESSAGE1:
		_xdr_argument = (xdrproc_t) xdr_message;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) insert_message1_1_svc;
		break;

	case RETRIEVE_MESSAGE:
		_xdr_argument = (xdrproc_t) xdr_usermsgid;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) retrieve_message_1_svc;
		break;

	case LIST_ALL_MESSAGES:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_listmessages;
		local = (char *(*)(char *, struct svc_req *)) list_all_messages_1_svc;
		break;

	case DELETE_MESSAGE:
		_xdr_argument = (xdrproc_t) xdr_usermsgid;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) delete_message_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (MAILBOX, ver);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, MAILBOX, ver, mailbox_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (MAILBOX, ver, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, MAILBOX, ver, mailbox_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (MAILBOX, ver, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
