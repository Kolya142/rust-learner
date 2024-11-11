#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE* File_open(char* name, char* flags) {
    return fopen(name, flags);
}
char* File_read(FILE* fptr) {
    char* result = NULL;
    size_t result_len = 0;
    char chunk[256];

    while (fgets(chunk, sizeof(chunk), fptr)) {
        size_t chunk_len = strlen(chunk);
        char* temp = realloc(result, result_len + chunk_len + 1);
        if (temp == NULL) {
            free(result);
            return NULL;
        }
        result = temp;
        strcpy(result + result_len, chunk);
        result_len += chunk_len;
    }

    if (result == NULL) {
        result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
    }
    
    return result;
}
void File_write(FILE* fptr, char* data) {
    fprintf(fptr, data);
}
void File_close(FILE* fptr) {
    fclose(fptr);
}
char* File_read_and_close(FILE* fptr) {
    char* data = File_read(fptr);
    File_close(fptr);
    return data;
}
void File_copy(char* i, char* o) {
    char* cmd = malloc(1024);
    sprintf(cmd, "cp %s %s", i, o);
    system(cmd);
    free(cmd);
}

int main() {
    FILE* _tmpr = File_open("output.txt", "w");
    File_write(_tmpr, "----");
    File_close(_tmpr);

    char* current_task = File_read_and_close(File_open("./current_task.txt", "r"));

    char* data_input = malloc(512);
    sprintf(data_input, "./tasks/%s/data/input.txt", current_task);

    char* data_output = malloc(512);
    sprintf(data_output, "./tasks/%s/data/output.txt", current_task);

    char* app_cmd = malloc(715);
    sprintf(app_cmd, "cargo run --manifest-path=./tasks/%s/app/Cargo.toml", current_task);

    File_copy(data_input, "input.txt");
    system(app_cmd);

    char* o__ = File_read_and_close(File_open("./output.txt", "r"));
    char* do_ = File_read_and_close(File_open(data_output, "r"));

    if (strcmp(o__, do_) == 0) {
        printf("✅Correct!\n");
    }
    else {
        printf("❌Incorrect.\n");
    }
}