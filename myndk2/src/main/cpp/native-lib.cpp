#include <jni.h>
#include <string>
#include "include/my.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_wmding_myndk3_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    jint sum = add(1, 2);

    char *string_int = (char *) malloc(sizeof(char) * 16);
    sprintf(string_int, "%d", sum);

    return env->NewStringUTF(string_int);
}
