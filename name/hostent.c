#include	"../lib/unp.h"

int
main(int argc, char **argv)
{
	char			*ptr, **pptr;
	char			str[INET_ADDRSTRLEN];
	struct hostent	*hptr;

	while (--argc > 0) {
		ptr = *++argv;  // 输入的每个参数都是一个主机名
		if ( (hptr = gethostbyname(ptr)) == NULL) {
			err_msg("gethostbyname error for host: %s: %s",
					ptr, hstrerror(h_errno));
			continue;
		}
		printf("official hostname: %s\n", hptr->h_name);
        // 打印所有别名
		for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
			printf("\talias: %s\n", *pptr);

		switch (hptr->h_addrtype) {
		case AF_INET:
			pptr = hptr->h_addr_list;   // 打印所有ipv4地址
			for ( ; *pptr != NULL; pptr++)
				printf("\taddress: %s\n",
					Inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
			break;

		default:
			err_ret("unknown address type");
			break;
		}
	}
	exit(0);
}
