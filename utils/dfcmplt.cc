// returns success if stdin or the argument is a complete datafile
#include "utils.hpp"
#include <cerrno>

// from datafile.cc
extern const char *start4;
extern const char *end4;

int main(int argc, char *argv[]) {
	FILE *in = stdin;
	if (argc == 2) {
		in = fopen(argv[1], "r");
		if (!in)
			fatalx(errno, "failed to open %s for reading", argv[1]);
	}

	boost::optional<std::string> l = readline(in);
	if (l && *l != start4)
		return 1;

	std::string prev;
	while (l) {
		prev = *l;
		l = readline(in);
	}

	if (prev != end4)
		return 1;

	return 0;
}