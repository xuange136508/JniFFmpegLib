//
// Created by Administrator on 2017/10/11.
//
#include <jni.h>

#ifndef JNIDEMO_EXUCTE_FFMPEG_H
#define JNIDEMO_EXUCTE_FFMPEG_H


JNIEXPORT jint JNICALL Java_jni_demo_com_jnidemo_jni_JniUtils_getRotation
  (JNIEnv *, jclass, jstring);

JNIEXPORT jint JNICALL Java_jni_demo_com_jnidemo_jni_JniUtils_ffmpegcode
  (JNIEnv *, jclass, jint, jobjectArray);




#endif //JNIDEMO_EXUCTE_FFMPEG_H
