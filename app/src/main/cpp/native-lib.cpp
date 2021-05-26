#include <jni.h>
#include <stdlib.h>
#include <cstring>
#include "mylog.cpp"
#include "include/native-lib.h"
#include "include/test.h"
#include "include/utils.h"

extern "C"
jstring Java_com_wmdming_ndkdemo_JavaCallC_stringFromJNI(
        JNIEnv *env, jobject instance) {

    char *string = "helloworld";
    return env->NewStringUTF(string);
}

extern "C"
jint Java_com_wmdming_ndkdemo_JavaCallC_addNum(JNIEnv *env, jobject instance, jint a, jint b) {

    return a + b;
}


extern "C"
jstring Java_com_wmdming_ndkdemo_JavaCallC_sayHello(JNIEnv *env, jobject instance, jstring str1_) {

    char *str1 = jstringToChar(env, str1_);
    const char *str2 = "---c++";

    // 字符串拼接
    strcat(str1, str2);

//    jstring data = env->NewStringUTF(str1);
    jstring data = charToJstring(env, str1);

    return data;
}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_wmdming_ndkdemo_JavaCallC_increaseArrayEles(JNIEnv *env, jobject instance,
                                                     jintArray jArray) {

    int size = env->GetArrayLength(jArray);

    jint *intArray = env->GetIntArrayElements(jArray, JNI_FALSE);

    for (int i = 0; i < size; ++i) {
        *(intArray + i) += 10;
    }
    return jArray;
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_wmdming_ndkdemo_JavaCallC_checkPassword(JNIEnv *env, jobject instance, jstring pwd_) {
    const char *str = "123";
    char *str1 = jstringToChar(env, pwd_);

    // 比较字符串是否相同
    return strcmp(str, str1);
}




extern "C"
JNIEXPORT jint JNICALL
Java_com_wmdming_ndkdemo_CCallJava_callbackAdd(JNIEnv *env, jobject instance) {

    LOGE("Java_com_wmdming_ndkdemo_CCallJava_callbackAdd");

    // 反射得到字节码
    jclass jclazz = env->FindClass("com/wmdming/ndkdemo/CCallJava");
    // 得到方法，jclass clazz, const char* name, const char* sig
    // 第三个参数为签名，到class 文件中，使用 javap -s 类名 取得
    jmethodID jId = env->GetMethodID(jclazz, "add", "(II)I");
    // 实例化该类
    jobject job = env->AllocObject(jclazz);
    // 调用方法
    return env->CallIntMethod(job, jId, 1, 99);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wmdming_ndkdemo_CCallJava_callbackMessage(JNIEnv *env, jobject instance) {

    LOGE("Java_com_wmdming_ndkdemo_CCallJava_callbackMessage");

    // 反射得到字节码
    jclass jclazz = env->FindClass("com/wmdming/ndkdemo/CCallJava");
    // 得到方法，jclass clazz, const char* name, const char* sig
    // 第三个参数为签名，到class 文件中，使用 javap -s 类名 取得
    jmethodID jId = env->GetMethodID(jclazz, "message", "()V");
    // 实例化该类
    jobject job = env->AllocObject(jclazz);
    // 调用方法
    env->CallVoidMethod(job, jId);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_wmdming_ndkdemo_CCallJava_callbackSayHello(JNIEnv *env, jobject instance) {

    LOGE("Java_com_wmdming_ndkdemo_CCallJava_callbackSayHello");

    // 反射得到字节码
    jclass jclazz = env->FindClass("com/wmdming/ndkdemo/CCallJava");
    // 得到方法，jclass clazz, const char* name, const char* sig
    // 第三个参数为签名，到class 文件中，使用 javap -s 类名 取得
    jmethodID jId = env->GetStaticMethodID(jclazz, "sayHello",
                                           "(Ljava/lang/String;)V");
    // 调用方法
    jstring jstr = env->NewStringUTF("--我是c中来的--");
    env->CallStaticVoidMethod(jclazz, jId, jstr);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_wmdming_ndkdemo_JavaCallC_getUser(JNIEnv *env, jobject thiz, jint age, jstring name) {

    jclass jclazz = env->FindClass("com/wmdming/ndkdemo/User");
    jmethodID jId = env->GetMethodID(jclazz, "<init>", "(ILjava/lang/String;)V");
    jobject object = env->NewObject(jclazz, jId, age, name);
    return object;
}


extern "C"
JNIEXPORT jobject JNICALL
Java_com_wmdming_ndkdemo_JavaCallC_getUser2(JNIEnv *env, jobject thiz, jint age, jstring name) {

    jclass jclazz = env->FindClass("com/wmdming/ndkdemo/User");
    jmethodID jId = env->GetMethodID(jclazz, "<init>", "(ILjava/lang/String;[B)V");

    // 先将 jstring 转为 char
    char *c_data = jstringToChar(env, name);
    uint32_t data_length = (env)->GetStringLength(name);

    // 再将 char 转为 jbyteArray（byte）
    jbyteArray data = env->NewByteArray(data_length);
    env->SetByteArrayRegion(data, 0, data_length, (jbyte *) c_data);
    env->ReleaseByteArrayElements(data, env->GetByteArrayElements(data, JNI_FALSE), 0);

    jobject object = env->NewObject(jclazz, jId, age, name, data);
    return object;
}


extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_wmdming_ndkdemo_JavaCallC_getByte(JNIEnv *env, jobject thiz, jstring name) {
    char *c_data = jstringToChar(env, name);
    uint32_t data_length = (env)->GetStringLength(name);

    jbyteArray data = env->NewByteArray(data_length);
    env->SetByteArrayRegion(data, 0, data_length, (jbyte *) c_data);
    env->ReleaseByteArrayElements(data, env->GetByteArrayElements(data, JNI_FALSE), 0);

    return data;
}




extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_wmdming_ndkdemo_JavaCallC_getByte2(JNIEnv *env, jobject thiz, jbyteArray name) {

    char *c_name = jbyteArrayToChar(env, name);
    char *c_data = "hhaha";

    // char 拼接
    strcat(c_name, c_data);

    // char 转 byte
    jbyteArray data = charToByteArray(env, c_name);
    return data;
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_wmdming_ndkdemo_JavaCallC_add(JNIEnv *env, jobject thiz, jint a, jint b) {
    int sum = 0;
    add(&a, &b, &sum);
    return sum;
}



