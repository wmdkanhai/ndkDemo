
#include <jni.h>

#include "include/test.h"

jstring testString(JNIEnv *env) {

    const char *string = "hello111";

    return env->NewStringUTF(string);
}

void add(int *a, int *b, int *out) {
    *out = *a + *b;
}