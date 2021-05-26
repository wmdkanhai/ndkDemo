#include "include/utils.h"

/**
 * jstring转换为 char*
 * @param env
 * @param jstr
 * @return
 */
char *jstringToChar(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    //这里填写是工作空间的编码，若是默认中文则是GB2312
    jstring strencode = env->NewStringUTF("UTF-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);  //字符串拼接函数...
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}

/**
 * char* 转换为 jstring
 * @param env
 * @param pat
 * @return
 */
jstring charToJstring(JNIEnv *env, char *pat) {
    //定义java String类 strClass
    jclass strClass = (env)->FindClass("java/lang/String");
    //获取String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    //建立byte数组
    jbyteArray bytes = (env)->NewByteArray(strlen(pat));
    //将char* 转换为byte数组
    (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte *) pat);
    env->ReleaseByteArrayElements(bytes, env->GetByteArrayElements(bytes, JNI_FALSE), 0);

    // 设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = (env)->NewStringUTF("utf-8");
    //将byte数组转换为java String,并输出
    return (jstring) (env)->NewObject(strClass, ctorID, bytes, encoding);
}

/**
 * byteArray 转 char*
 * @param env
 * @param bytearray
 * @return
 */
char *jbyteArrayToChar(JNIEnv *env, jbyteArray bytearray) {
    char *chars = NULL;
    jbyte *bytes;
    bytes = env->GetByteArrayElements(bytearray, 0);
    int chars_len = env->GetArrayLength(bytearray);
    chars = new char[chars_len + 1];
    memset(chars, 0, chars_len + 1);
    memcpy(chars, bytes, chars_len);
    chars[chars_len] = 0;
    env->ReleaseByteArrayElements(bytearray, bytes, 0);
    return chars;
}

/**
 * char* 转 byteArray
 * @param env
 * @param in_data
 * @return
 */
jbyteArray charToByteArray(JNIEnv *env, char *in_data) {
    uint32_t data_length = strlen(in_data);

    jbyteArray data = env->NewByteArray(data_length);
    env->SetByteArrayRegion(data, 0, data_length, (jbyte *) in_data);
    env->ReleaseByteArrayElements(data, env->GetByteArrayElements(data, JNI_FALSE), 0);

    return data;
}