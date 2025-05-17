#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <sys/stat.h>

using namespace std;

int main() {
    const char* filename = "data.txt";

    int file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (file < 0) {
        perror("Error creating file");
        return 1;
    }
    close(file);

    pid_t pid_
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <sys/stat.h>

using namespace std;

int main() {
    const char* filename = "data.txt";

    int file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (file < 0) {
        perror("Error creating file");
        return 1;
    }
    close(file);

    pid_t pid2 = fork();

    if (pid2 < 0) {
        perror("Failed to fork P2");
        return 1;
    }

    if (pid2 == 0) {
        const char* full_name = "John Doe";
        int fd = open(filename, O_WRONLY);
        if (fd < 0) {
            perror("P2: Failed to open file");
            return 1;
        }
        write(fd, full_name, strlen(full_name));
        close(fd);
        _exit(0);
    } else {
        waitpid(pid2, nullptr, 0);

        pid_t pid3 = fork();
        if (pid3 < 0) {
            perror("Failed to fork P3");
            return 1;
        }

        if (pid3 == 0) {
            int fd = open(filename, O_RDONLY);
            if (fd < 0) {
                perror("P3: Failed to open file");
                return 1;
            }

            char buffer[100] = {0};
            read(fd, buffer, sizeof(buffer) - 1);
            close(fd);

            char* space = strchr(buffer, ' ');
            if (space != nullptr) {
                *space = '\0';
            }

            cout << "First Name: " << buffer << endl;

            struct stat file_stat;
            if (stat(filename, &file_stat) == 0) {
                cout << "File Size: " << file_stat.st_size << " bytes" << endl;
            } else {
                perror("P3: stat failed");
            }

            _exit(0);
        } else {
            waitpid(pid3, nullptr, 0);
        }
    }

    return 0;
}
