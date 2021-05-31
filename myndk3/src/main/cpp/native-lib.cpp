#include <jni.h>
#include <string>
#include "include/my.h"

extern "C" JNIEXPORT jint JNICALL
Java_com_wmding_myndk2_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    return add(1,2);
}
