/*
 * Copyright (c) 2020 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_samsung_onert_NativeSessionWrapper */

#ifndef _Included_com_samsung_onert_NativeSessionWrapper
#define _Included_com_samsung_onert_NativeSessionWrapper
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativeCreateSession
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativeCreateSession(JNIEnv *,
                                                                                        jobject);

/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativeCloseSession
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativeCloseSession(JNIEnv *,
                                                                                      jobject,
                                                                                      jlong);

/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativeLoadModelFromFile
 * Signature: (JLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativeLoadModelFromFile(
  JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativePrepare
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativePrepare(JNIEnv *,
                                                                                     jobject,
                                                                                     jlong);

/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativeRun
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativeRun(JNIEnv *, jobject,
                                                                                 jlong);

/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativeSetInput
 * Signature: (JIILjava/nio/ByteBuffer;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativeSetInput(
  JNIEnv *, jobject, jlong, jint, jint, jobject, jint);

/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativeSetOutput
 * Signature: (JIILjava/nio/ByteBuffer;I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativeSetOutput(
  JNIEnv *, jobject, jlong, jint, jint, jobject, jint);

/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativeSetInputLayout
 * Signature: (JII)Z
 */
JNIEXPORT jboolean JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativeSetInputLayout(
  JNIEnv *, jobject, jlong, jint, jint);

/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativeSetOutputLayout
 * Signature: (JII)Z
 */
JNIEXPORT jboolean JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativeSetOutputLayout(
  JNIEnv *, jobject, jlong, jint, jint);

/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativeGetInputSize
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativeGetInputSize(JNIEnv *,
                                                                                      jobject,
                                                                                      jlong);

/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativeGetOutputSize
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativeGetOutputSize(JNIEnv *,
                                                                                       jobject,
                                                                                       jlong);

/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativeGetInputTensorInfo
 * Signature: (JILcom/samsung/onert/NativeSessionWrapper/InternalTensorInfo;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativeGetInputTensorInfo(
  JNIEnv *, jobject, jlong, jint, jobject);

/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativeGetOutputTensorInfo
 * Signature: (JILcom/samsung/onert/NativeSessionWrapper/InternalTensorInfo;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativeGetOutputTensorInfo(
  JNIEnv *, jobject, jlong, jint, jobject);

/*
 * Class:     com_samsung_onert_NativeSessionWrapper
 * Method:    nativeSetAvailableBackends
 * Signature: (JLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_samsung_onert_NativeSessionWrapper_nativeSetAvailableBackends(
  JNIEnv *, jobject, jlong, jstring);

#ifdef __cplusplus
}
#endif
#endif