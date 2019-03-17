#include<limits.h> // needs PATH_MAX
#include<libgen.h> // needs dirname()
#include<stdio.h> // needs snprintf()
#include<unistd.h> // needs readlink(), chdir()

/* many `program' need to access files under its directory
 * through relative-path
 * but `program' always run in various directory,
 * so at the very begin of the program,
 * it needs to cd back its file directory
 *
 * a link to the absolute-path of the `program`-file
 * is in "/proc/<pid>/exe".
 * it needs readlink() to get the string and
 * dirname() to extract the dirname.
 * finally, change directory via chdir()
 */

int cd_exe_file_dir(void) {
    int ret;
    char proc_exe_path[PATH_MAX + 1];
    char exe_file_path[PATH_MAX + 1];
    char exe_file_dir[PATH_MAX + 1];

    snprintf(proc_exe_path, PATH_MAX, "/proc/%ld/exe", (long int)getpid());
    ret = readlink(proc_exe_path, exe_file_path, PATH_MAX);
    if(ret < 0)
        return -1;

    exe_file_path[PATH_MAX] = '\0'; // printf("path: %s\n", exe_file_path);

    // Notes: dirname(path) will modified its parameter
    snprintf(exe_file_dir, PATH_MAX, "%s", dirname(exe_file_path));
    exe_file_dir[PATH_MAX] = '\0'; // printf("dir: %s\n", exe_file_dir);
    // now, exe_file_path is equel to exe_file_dir
    ret = chdir(exe_file_dir);
    if(ret < 0)
        return -1;
    return 0;
}

#if 0 /* demo, goto another directory and execuate it */
int main(void) {
    system("pwd");

    if(cd_exe_file_dir() < 0) {
        printf("cd_exe_file_dir() error occurs.\n");
        return -1;
    }

    system("pwd");
}
#endif
