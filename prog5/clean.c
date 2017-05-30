#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>

#define PID_MAX 99999 // had to define my own pidmax

struct Process {
		pid_t pid;
		pid_t ppid;
		char *user;
		char *name;
};

// concatenate two strings together
char *concat(const char *s1, const char *s2) {
		char *result = malloc(strlen(s1)+strlen(s2)+1);
		strcpy(result, s1);
		strcat(result, s2);
		return result;
}

// get the path of a processes directory from its pid number
char *getprocpath(int pid) {
		char pidstr[5];
		sprintf(pidstr, "%d", pid);
		char *prefix = "/proc/";
		char *procPath = concat(prefix, pidstr);
		return procPath;
}

// checks if process exists in the file system 
// returns 1 if it does 0 if it doesn't 
int procexists(int pid) {
		//char *procPath = getprocpath(pid);
		//DIR *proc = opendir(procPath);

//		if(proc)
//				return 1;
//		else
//				return 0;
		if(kill(pid, 0) == 0) 
				return 1;
		else
				return 0;

}

// get name of process running
char *getprocname(int pid) {
		char *procPath = getprocpath(pid);
		char *suffix = "/comm";
		char *commPath = concat(procPath, suffix);
		char *procName;

		FILE *comm = fopen(commPath, "r");
		if(comm) {
			procName = malloc(100 * sizeof(char));

			if(fgets(procName, 100, comm) == NULL) {
					perror("fgets error\n");
			}

			fclose(comm);
		} else return NULL;

		return procName;
}

// get the user id of a process
int getprocuid(int pid) {
		char *buff = malloc(4096 *sizeof(char));
		char *procPath = getprocpath(pid);
		char *suffix = "/status";
		char *statusPath = concat(procPath, suffix);
		int procfd = open(statusPath, O_RDONLY);
		FILE *status = fopen(statusPath, "r");
		char line[100];
		int uid = 0;
		char *temp;

		if(!status) // if file fails to open return error code -1
			return -1;
				
		while(fgets(line, 100, status)) {
				if(strncmp(line,"Uid:",4) != 0)
						continue;
				temp = line + 5;
			   while(isspace(*temp)) ++temp;	

			   sscanf(temp,"%d",&uid);
			   break;
		}


		fclose(status);
		return uid;
}

// get the username of a process
char *getprocuser(int pid) {
		int uid = getprocuid(pid);
		struct passwd *usrInfo = getpwuid(uid);
		char *username = usrInfo->pw_name;
		return username;
}

// get the parent id of a process
pid_t getprocessparentpid(int pid) {
		char buffer[512];
		sprintf(buffer,"/proc/%d/stat",pid);
		FILE *fp = fopen(buffer, "r");
		pid_t ppid;

		if(fp) {
				size_t size = fread(buffer, sizeof(char), sizeof(buffer), fp);
				if(size > 0) {
						strtok(buffer, " ");
						strtok(NULL, " ");
						strtok(NULL, " ");
						char *s_ppid = strtok(NULL, " ");
						ppid = atoi(s_ppid);
				}
				fclose(fp);
		}
		return ppid;
}

// define a new process struct
struct Process *newProc(int pid) {
		struct Process *new = malloc(sizeof(struct Process));
		new->pid = pid;
		new->ppid = getprocessparentpid(pid);
		new->user = getprocuser(pid);
		new->name = getprocname(pid);
		return new;
}

// print all process information
void printProc(struct Process *proc) {
		printf("%d\t%d\t%s\t%s",proc->pid,proc->ppid,proc->user,proc->name);
}

void copyProc(struct Process *dest, struct Process *source) {
		dest->name = strdup(source->name);
		dest->user = strdup(source->user);
		dest->pid = source->pid;
		dest->ppid = source->ppid;
}

int main(void) {
		// save the parent process and current process 
		struct Process *self = newProc(getpid());
		struct Process *parent = newProc(getppid());
		struct Process *sshdProc = malloc(sizeof(struct Process));
		
		// declare an array of struct pointers and allocate them 
		struct Process **savedProcs = malloc(3 * sizeof(struct Process *));
		savedProcs[0] = sshdProc;
		savedProcs[1] = parent;
		savedProcs[2] = self;

		printf("\tPID\tPPID   \tUSER \tNAME\n");
		for(int i = PID_MAX;i > 1;i--) {
				if(procexists(i) == 1) {
					struct Process *curProc = newProc(i);
					//if process is not itself or the parent process
					if(curProc->pid == self->pid || curProc->pid == self->ppid)
							continue;
					
					// keep the sshd process to kill later
					if((strcmp(curProc->name,"sshd\n") == 0) && (strcmp(curProc->user,"bmoor64") == 0)) {
							copyProc(sshdProc,curProc);
							continue;
					}
					//kill(i,SIGKILL);

					if(kill(i,0) == 0) { //if the process was killed print it on screen
						printf("Killed:\t");
						printProc(curProc);
					}
					free(curProc);
				}	
		}

		// kill and print this process, it's parent and the sshd process
		for(int i = 0;i < 3;i++) {
				//kill(savedProcs[i]->pid, SIGKILL);

				if(kill(savedProcs[i]->pid, 0) == 0) {
					printf("Killed:\t");
					printProc(savedProcs[i]);
				}

				free(savedProcs[i]);
		}

		return 0;
}
