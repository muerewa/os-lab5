#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void print_start(int proc_num) {
    printf("Процесс %d запущен: мой PID = %d, PID родителя = %d\n", proc_num, getpid(), getppid());
}

void print_exit(int proc_num) {
    printf("Процесс %d с PID = %d и PID родителя = %d завершает работу\n", proc_num, getpid(), getppid());
}

void print_fork(int proc_num, pid_t child_pid) {
    printf("Процесс %d с PID = %d породил процесс с PID = %d\n", proc_num, getpid(), child_pid);
}

int main() {
    print_start(1);
    int pid1 = fork();
    if (pid1 == 0) {
        print_start(2);
        int pid4 = fork();
        if (pid4 == 0) {
            print_start(4);
            print_exit(4);
            exit(0);
        }
        print_fork(2, pid4);
        int pid5 = fork();
        if (pid5 == 0) {
            print_start(5);
            print_exit(5);
            exit(0);
        }
        print_fork(2, pid5);

        waitpid(pid4, NULL, 0);
        waitpid(pid5, NULL, 0);
        print_exit(2);
        exit(0);
    }
    print_fork(1, pid1);

    int pid2 = fork();
    if (pid2 == 0) {
        print_start(3);
        int pid6 = fork();
        if (pid6 == 0) {
            print_start(6);
            print_exit(6);
            exit(0);
        }
        print_fork(3, pid6);

        int pid7 = fork();
        if (pid7 == 0) {
            print_start(7);
            print_exit(7);
            exit(0);
        }
        print_fork(3, pid7);

        waitpid(pid6, NULL, 0);
        waitpid(pid7, NULL, 0);

        execlp("ps", "ps", "aux", NULL);
    }
    print_fork(1, pid2);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    print_exit(1);
    return 0;
}
