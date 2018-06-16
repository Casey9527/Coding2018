



const char *
find_command(const char *cmd)
{

	struct stat s;
	
	search = "/bin:/usr/bin:/sbin:/usr/sbin";

	p = search;

	while (*p++) {

		if (*p != ":")
			continue;

		plen = p - search;

		if ((plen + clen) >= sizeof(path))
			continue;

	}



}
