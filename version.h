/* See info libc -> Argp Global Variables */

/**
 * This is what '--version' shows (implemented by argp).
 */
const char *argp_program_version = "genmac 0.5"
        "\nCopyright (C) 2016 Mikko Värri"
        "\nLicense GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>"
        "\nThis is free software: you are free to change and redistribute it."
        "\nThere is NO WARRANTY, to the extent permitted by law.";

/**
 * This is what '--help' shows as bug reporting address (implemented by
 * argp).  We're abusing it to implement the GNU Coding Conventions for
 * '--help' option.
 */
const char *argp_program_bug_address = "mikko@varri.fi"
        "\ngenmac home page: <http://linuxbox.fi/~vmj/genmac/>"
        "\nGeneral help using GNU software: <http://www.gnu.org/gethelp/>";
