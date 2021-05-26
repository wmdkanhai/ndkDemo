#include <jni.h>
#ifndef NDKDEMO_TEST_H
#define NDKDEMO_TEST_H

jstring testString(JNIEnv *env);

void add(int *a, int *b, int *out);

#endif //NDKDEMO_TEST_H
