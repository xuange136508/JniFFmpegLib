//http://blog.csdn.net/leixiaohua1020
#include "excute_ffmpeg.h"
#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//注意了，这里是c++工程
extern "C"
{
#include "../command/ffmpeg.h"
#include "../include/libavcodec/avcodec.h"
#include "../include/libavformat/avformat.h"
#include "../include/libswscale/swscale.h"
#include "../include/libswresample/swresample.h"
#include "../include/libavutil/avutil.h"
#include "../include/libavfilter/avfilter.h"
}
#include <android/log.h>
#define LOG_TAG "System.out.c"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO  , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN  , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)

extern "C"{
int ffmpegmain(int argc, char **argv);
}

//命令的方式压缩视频
JNIEXPORT jint JNICALL Java_jni_demo_com_jnidemo_jni_JniUtils_ffmpegcode
  (JNIEnv *env, jclass clazz, jint cmdNum, jobjectArray cmdLine){
	//jobjectArray -> char** (java的字符数组转换成c的字符串数组)
	char ** argv = (char**)malloc(sizeof(char*)*cmdNum);

	//数组赋值
	int i = 0;
	for (; i<cmdNum;i++) {
		//jobject -> char* (获取数组)
		jstring jstr = (jstring)env->GetObjectArrayElement(cmdLine,i);
		const char* cstr = env->GetStringUTFChars(jstr,0);
		//赋值
		//元素开辟空间
		argv[i] = (char*) malloc(sizeof(char)*1024);
		/**字符串复制。char *strcpy(char *dest,char *src);
			用法：#include <string.h>
			功能：把src所指由NULL结束的字符串复制到dest所指的数组中。
			说明：src和dest所指内存区域不可以重叠且dest必须有足够的空间来容纳src的字符串。**/
		strcpy(argv[i],cstr);
	}
	//调用-->
	int res = ffmpegmain(cmdNum,argv);

	//释放内存
	for(i = 0;i<cmdNum;i++){
		free(argv[i]);
	}
	LOGI("%s","end");
	return res;
}


JNIEXPORT jint JNICALL Java_jni_demo_com_jnidemo_jni_JniUtils_getRotation
  (JNIEnv *env, jclass clazz, jstring videoPath){
	//打开视频文件，读取元数据
	LOGI("%s","getRotation");

	//jstring->char*  (/storage/emulated/0/a.mp4)
	const char* filePath = env->GetStringUTFChars(videoPath,NULL);
	LOGI("视频路径 : %s",filePath);

	//1 注册
	av_register_all();
	//2 解封装
	//AVFormatContext *pFormatCtx  = avformat_alloc_context();
    AVFormatContext *pFormatCtx = NULL;
	//3 打开
	int err_code = 0;
	if((err_code = avformat_open_input(&pFormatCtx,filePath,NULL,NULL))!=0){
		// 在安卓中经常出现无法打开文件的情况,所以可以使用
		// av_strerror打印日志
		//av_strerror(err_code, msg, 1024);
		//jclass exceptionClazz = env->FindClass("java/lang/RuntimeException");
		//env->ThrowNew(env,exceptionClazz, msg);
        LOGI("错误 : %d",err_code);
		LOGI("%s","无法打开视频文件");
		return -1;
	}
	//4 获取信息
	if(avformat_find_stream_info(pFormatCtx,NULL)<0){
		LOGI("%s","无法获取视频文件信息");
		return -2;
	}
	//5 获取视频流索引位置
	int i = 0;
	int v_stream_idx = -1;
	for (i = 0; i < pFormatCtx->nb_streams; ++i) {
		if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){
			v_stream_idx = i;
			break;
		}
	}
	if(v_stream_idx == -1){
		LOGI("%s","无法获取视频流");
		return -3;
	}
	//6 解码器
	//AVCodecContext *pCodecCtx = pFormatCtx->streams[i]->codec;

	//7 获取视频元数据 (rotate表示选择角度)
	AVDictionaryEntry *tag = NULL;
	tag = av_dict_get(pFormatCtx->streams[v_stream_idx]->metadata,"rotate",tag,0);

	int angle = -1;//拿到角度
	if(tag!=NULL){
		angle = atoi(tag->value);//字符串转整数 java Interger.value("");
		LOGI("angle : %d",angle);
	}

	//8 释放资源
	avformat_free_context(pFormatCtx);
	LOGI("释放资源");

	//返回
	return angle;
}

