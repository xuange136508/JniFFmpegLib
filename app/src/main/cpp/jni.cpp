#define TAG "fs_jni"
#include "jniRegisiter.h"

#include "ffmpeg/call_ffmpeg.h"
#include "ffmpeg/excute_ffmpeg.h"

//日志
#include<android/log.h>
#define LOG_TAG "System.out.c"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

static const char* const kClassPathName = "jni/demo/com/jnidemo/jni/JniUtils";


/******************************JNI 注册函数************************************/

static JNINativeMethod gMethods[] = {

{"execute",      "()Ljava/lang/String;",  (void *)Java_jni_demo_com_jnidemo_jni_JniUtils_execute},

{"getRotation",      "(Ljava/lang/String;)I",  (void *)Java_jni_demo_com_jnidemo_jni_JniUtils_getRotation},
{"ffmpegcode",      "(I[Ljava/lang/String;)I",  (void *)Java_jni_demo_com_jnidemo_jni_JniUtils_ffmpegcode},


};

//注册函数的方法，JNI_LOAD
int register_jni_method(JNIEnv *env) {
    return jniRegisterNativeMethods(env, kClassPathName, gMethods, sizeof(gMethods) / sizeof(gMethods[0]));
}

