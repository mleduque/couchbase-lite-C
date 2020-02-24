
#include "CouchbaseLite.h"

#include <errno.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    CBLError error;
    CBLDatabaseConfiguration config = {
        .directory = "/tmp/cbltest/",
        .flags = 1,
        .encryptionKey = {
            .algorithm = 0,
            .bytes = {0}
        }
    };

    struct stat st = {0};
    if (stat("/tmp/cbltest/", &st) == -1) {
        if (mkdir("/tmp/cbltest/", 0777) != 0) {
            printf("mkdir failed, %i\n", errno);
            exit(errno);
        }
    }
    CBL_SetLogLevel(CBLLogWarning, kCBLLogDomainAll);
    uint64_t i = 0;
    while (true) {
        CBLDatabase* db = CBLDatabase_Open("open_close_db",
                                            &config,
                                            &error) CBLAPI;
        if (!db && error.code != 0) {
            printf("open failed, %i %i\n", error.domain, error.code);
            exit(error.code);
        }
        CBLDatabase_Close(db, &error);
        if (i % 100 == 0) {
            printf("%li\n", i);
        }
        i++;
    }
}