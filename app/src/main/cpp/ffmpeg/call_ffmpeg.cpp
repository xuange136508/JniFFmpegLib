//http://blog.csdn.net/leixiaohua1020
#include "call_ffmpeg.h"


//注意了，这里是c++工程
extern "C"
{
#include "../include/libavformat/avformat.h"
#include "../include/libavfilter/avfilter.h"
}

//日志
#include<android/log.h>
#define LOG_TAG "System.out.c"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)



/**
 * Protocol Support Information
 */
jstring urlprotocolinfo(JNIEnv *env, jobject obj){
    LOGD("FFMPEG urlprotocolinfo 协议信息");
    char info[40000]={0};
    av_register_all();

    struct URLProtocol *pup = NULL;
    //Input
    struct URLProtocol **p_temp = &pup;
    avio_enum_protocols((void **)p_temp, 0);
    while ((*p_temp) != NULL){
        sprintf(info, "%s[In ][%10s]\n", info, avio_enum_protocols((void **)p_temp, 0));
    }
    pup = NULL;
    //Output
    avio_enum_protocols((void **)p_temp, 1);
    while ((*p_temp) != NULL){
        sprintf(info, "%s[Out][%10s]\n", info, avio_enum_protocols((void **)p_temp, 1));
    }
    return env->NewStringUTF(info);
}
/**
 * AVFormat Support Information
 */
jstring avformatinfo(JNIEnv *env, jobject obj){
    char info[40000] = { 0 };
    av_register_all();

    AVInputFormat *if_temp = av_iformat_next(NULL);
    AVOutputFormat *of_temp = av_oformat_next(NULL);
    //Input
    while(if_temp!=NULL){
        sprintf(info, "%s[In ][%10s]\n", info, if_temp->name);
        if_temp=if_temp->next;
    }
    //Output
    while (of_temp != NULL){
        sprintf(info, "%s[Out][%10s]\n", info, of_temp->name);
        of_temp = of_temp->next;
    }
    //LOGE("%s", info);
    return env->NewStringUTF(info);
}

/**
 * AVCodec Support Information
 */
jstring avcodecinfo(JNIEnv *env, jobject obj) {
    char info[40000] = { 0 };
    av_register_all();
    AVCodec *c_temp = av_codec_next(NULL);

    while(c_temp!=NULL){
        if (c_temp->decode!=NULL){
            sprintf(info, "%s[Dec]", info);
        }
        else{
            sprintf(info, "%s[Enc]", info);
        }
        switch (c_temp->type){
            case AVMEDIA_TYPE_VIDEO:
                sprintf(info, "%s[Video]", info);
                break;
            case AVMEDIA_TYPE_AUDIO:
                sprintf(info, "%s[Audio]", info);
                break;
            default:
                sprintf(info, "%s[Other]", info);
                break;
        }
        sprintf(info, "%s[%10s]\n", info, c_temp->name);


        c_temp=c_temp->next;
    }
    //LOGE("%s", info);
    return env->NewStringUTF(info);
}

/**
 * AVFilter Support Information
 */
jstring avfilterinfo(JNIEnv *env, jobject obj) {
    char info[40000] = { 0 };
    av_register_all();
    AVFilter *f_temp = (AVFilter *)avfilter_next(NULL);
    while (f_temp != NULL){
        sprintf(info, "%s[%10s]\n", info, f_temp->name);
    }
    //LOGE("%s", info);
    return env->NewStringUTF(info);
}

/**
 * Protocol Support Information
 */
jstring configurationinfo(JNIEnv *env, jobject obj) {
    char info[10000] = { 0 };
    av_register_all();
    sprintf(info, "%s\n", avcodec_configuration());
    //LOGE("%s", info);
    return env->NewStringUTF(info);
}

/*
* 本程序是移植FFmpeg到安卓平台的最简单程序。它可以打印出FFmpeg类库的下列信息：
* Protocol:  FFmpeg类库支持的协议
* AVFormat:  FFmpeg类库支持的封装格式
* AVCodec:   FFmpeg类库支持的编解码器
* AVFilter:  FFmpeg类库支持的滤镜
* Configure: FFmpeg类库的配置信息
*/

jstring Java_jni_demo_com_jnidemo_jni_JniUtils_execute(JNIEnv* env, jobject thiz){
    //return urlprotocolinfo(env,thiz);
    return avformatinfo(env,thiz);
    //return avcodecinfo(env,thiz);
    //return avfilterinfo(env,thiz);
    //return configurationinfo(env,thiz);
}


