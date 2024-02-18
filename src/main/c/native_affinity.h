/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class jeyn_affinity_NativeThreadAffinity */

#ifndef _Included_jeyn_affinity_NativeThreadAffinity
#define _Included_jeyn_affinity_NativeThreadAffinity
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     jeyn_affinity_NativeThreadAffinity
 * Method:    numaNumNative
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_jeyn_affinity_NativeThreadAffinity_numaNumNative(JNIEnv *, jclass);

/*
 * Class:     jeyn_affinity_NativeThreadAffinity
 * Method:    getNumaNative
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_jeyn_affinity_NativeThreadAffinity_getNumaNative(JNIEnv *, jclass, jint);

/*
 * Class:     jeyn_affinity_NativeThreadAffinity
 * Method:    setNumaNative
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_jeyn_affinity_NativeThreadAffinity_setNumaNative(JNIEnv *, jclass, jint);

/*
 * Class:     jeyn_affinity_NativeThreadAffinity
 * Method:    getAffinityNative
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_jeyn_affinity_NativeThreadAffinity_getAffinityNative(JNIEnv *, jclass, jint);

/*
 * Class:     jeyn_affinity_NativeThreadAffinity
 * Method:    setAffinityNative
 * Signature: (I[B)I
 */
JNIEXPORT jint JNICALL Java_jeyn_affinity_NativeThreadAffinity_setAffinityNative(JNIEnv *, jclass, jint, jbyteArray);

/*
 * Class:     jeyn_affinity_NativeThreadAffinity
 * Method:    getCpuNative
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_jeyn_affinity_NativeThreadAffinity_getCpuNative(JNIEnv *, jclass);

/*
 * Class:     jeyn_affinity_NativeThreadAffinity
 * Method:    getPidNative
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_jeyn_affinity_NativeThreadAffinity_getPidNative(JNIEnv *, jclass);

/*
 * Class:     jeyn_affinity_NativeThreadAffinity
 * Method:    getTidNative
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_jeyn_affinity_NativeThreadAffinity_getTidNative(JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
