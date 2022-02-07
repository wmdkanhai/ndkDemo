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



extern "C"
JNIEXPORT jobject JNICALL
Java_com_wmdming_ndkdemo_JavaCallC_getCmdResult(JNIEnv *env, jobject thiz) {

    //   这两种类型 都可以获得class引用
    jclass jclass = env->FindClass("com/wmdming/ndkdemo/CmdResult");
    jmethodID construct = env->GetMethodID(jclass, "<init>", "()V");
    jobject object = env->NewObject(jclass, construct);
    jmethodID setCodeMethod = env->GetMethodID(jclass, "setCode", "(I)V");
    env->CallVoidMethod(object, setCodeMethod, 0);
    jmethodID setDataMethod = env->GetMethodID(jclass, "setData", "([B)V");

    char *c_data = "hhaha";
    // char 转 byte
    jbyteArray data = charToByteArray(env, c_data);
    env->CallVoidMethod(object, setDataMethod, data);

    return object;
}


int memerycpy(void *dest, uint32_t dest_max_size, void *src, uint32_t src_size) {
    if (NULL == dest || dest_max_size < 1 || NULL == src || src_size < 1) {
        return 1;
    }
    if (dest_max_size < src_size) {
        LOGE("The memcpy dest length is too short, the expected value is %x, the actual value is %x.",
             src_size, dest_max_size);
        return 1;
    }
    memcpy(dest, src, src_size);
    return 0;
}

uint32_t writeBufferData(uint8_t *dest, uint32_t dest_len, uint8_t *src, uint32_t src_len) {
    int ret = memerycpy(dest, dest_len, src, src_len);
    return ret == 0 ? src_len : 0;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_wmdming_ndkdemo_JavaCallC_sendCmd(JNIEnv *env, jobject thiz, jbyteArray data) {

    uint32_t in_data_len = 0;
    uint8_t *in_data = NULL;

    uint32_t out_data_len = 0;
    uint8_t *out_data = NULL;

    uint32_t offset = 0;

    jclass jclass = env->FindClass("com/wmdming/ndkdemo/CmdResult");

    jmethodID construct = env->GetMethodID(jclass, "<init>", "()V");
    jobject object = env->NewObject(jclass, construct);

    jmethodID setCodeMethod = env->GetMethodID(jclass, "setCode", "(I)V");
    env->CallVoidMethod(object, setCodeMethod, 0);


    jmethodID setDataMethod = env->GetMethodID(jclass, "setData", "([B)V");

    if (data != NULL) {
        in_data_len = (env)->GetArrayLength(data);
        in_data = (uint8_t *) malloc(in_data_len);
        if (NULL == in_data) {
            goto RELEASE;
        }
        memset(in_data, 0, in_data_len);
        (env)->GetByteArrayRegion(data, 0, in_data_len, (jbyte *) in_data);
    }

    out_data_len = 0x400;

    out_data = (uint8_t *) malloc(out_data_len);
    if (NULL == out_data) {
        goto RELEASE;
    }
    memset(out_data, 0, out_data_len);

    offset += writeBufferData(out_data, out_data_len, in_data, in_data_len);

    out_data_len = offset;

    if (out_data && out_data_len > 0) {
        jbyteArray jdata = env->NewByteArray(out_data_len);
        env->SetByteArrayRegion(jdata, 0, out_data_len, (const jbyte *) out_data);
        env->CallVoidMethod(object, setDataMethod, jdata);
    }


    RELEASE:
    if (in_data) {
        free(in_data);
    }

    if (jclass) {
        env->DeleteLocalRef(jclass);
    }

    return object;
}


#define TYPE1 0x0001
#define TYPE2 0x0002

extern "C"
JNIEXPORT jobject JNICALL
Java_com_wmdming_ndkdemo_JavaCallC_commonSendCmd(JNIEnv *env, jobject thiz, jint cmd,
                                                 jbyteArray data) {

    uint32_t in_data_len = 0;
    uint8_t *in_data = NULL;

    uint32_t out_data_len = 0;
    uint8_t *out_data = NULL;

    uint32_t offset = 0;

    jclass jclass = env->FindClass("com/wmdming/ndkdemo/CmdResult");

    jmethodID construct = env->GetMethodID(jclass, "<init>", "()V");
    jobject object = env->NewObject(jclass, construct);

    jmethodID setCodeMethod = env->GetMethodID(jclass, "setCode", "(I)V");

    jmethodID setDataMethod = env->GetMethodID(jclass, "setData", "([B)V");

    if (data != NULL) {
        in_data_len = (env)->GetArrayLength(data);
        in_data = (uint8_t *) malloc(in_data_len);
        if (NULL == in_data) {
            goto RELEASE;
        }
        memset(in_data, 0, in_data_len);
        (env)->GetByteArrayRegion(data, 0, in_data_len, (jbyte *) in_data);
    }

    out_data_len = 0x400;

    out_data = (uint8_t *) malloc(out_data_len);
    if (NULL == out_data) {
        goto RELEASE;
    }
    memset(out_data, 0, out_data_len);


    LOGI("cmd: %d", cmd);
    switch (cmd) {

        case TYPE1:
            // 实现字符串追加，test9hello1world

            offset += writeBufferData(out_data, out_data_len, in_data, in_data_len);

            char *str1 = "hello1";

            int str1_len = strlen(str1);

            offset += writeBufferData(out_data + offset, out_data_len - offset,
                                      reinterpret_cast<uint8_t *>(str1), str1_len);
            char *str2 = "world";
            int str2_len = strlen(str2);

            offset += writeBufferData(out_data + offset, out_data_len - offset,
                                      reinterpret_cast<uint8_t *>(str2), str2_len);

            out_data_len = offset;

            break;
    }

    if (out_data && out_data_len > 0) {
        jbyteArray jdata = env->NewByteArray(out_data_len);
        env->SetByteArrayRegion(jdata, 0, out_data_len, (const jbyte *) out_data);
        env->CallVoidMethod(object, setDataMethod, jdata);
    }


    env->CallVoidMethod(object, setCodeMethod, 0);


    RELEASE:
    if (in_data) {
        free(in_data);
    }

    if (jclass) {
        env->DeleteLocalRef(jclass);
    }

    return object;
}