#include <jni.h>
#include <stdlib.h>
#include <cstring>

#ifndef NDKDEMO_UTILS_H
#define NDKDEMO_UTILS_H

char *jstringToChar(JNIEnv *env, jstring jstr);

jstring charToJstring(JNIEnv *env, char *pat);

char *jbyteArrayToChar(JNIEnv *env, jbyteArray bytearray);

jbyteArray charToByteArray(JNIEnv *env, char *in_data);

#endif //NDKDEMO_UTILS_H