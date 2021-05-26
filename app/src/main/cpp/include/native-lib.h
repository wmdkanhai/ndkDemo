
#include <jni.h>
#ifndef NDKDEMO_NATIVE_LIB_H
#define NDKDEMO_NATIVE_LIB_H

extern "C" jstring Java_com_wmdming_ndkdemo_JavaCallC_stringFromJNI(JNIEnv *env, jobject instance);

extern "C" jint Java_com_wmdming_ndkdemo_JavaCallC_addNum(JNIEnv *env, jobject instance, jint a, jint b);




#endif //NDKDEMO_NATIVE_LIB_H
