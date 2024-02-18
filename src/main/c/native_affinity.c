#include "native_affinity.h"

#include <numa.h>
#include <sched.h>
#include <syscall.h>

JNIEXPORT jint JNICALL Java_org_openucx_jucx_UcxThreadAffinityNative_numaNumNative(JNIEnv *env, jclass c) {
    if (numa_available() < 0) {
        return -1;
    }

    return numa_num_task_nodes();
}

JNIEXPORT jint JNICALL Java_org_openucx_jucx_UcxThreadAffinityNative_getNumaNative(JNIEnv *env, jclass c, jint cpuid) {
    return numa_node_of_cpu(cpuid);
}

JNIEXPORT jint JNICALL Java_org_openucx_jucx_UcxThreadAffinityNative_setNumaNative(JNIEnv *env, jclass c, jint nodeid) {
    return numa_run_on_node(nodeid);
}

JNIEXPORT jbyteArray JNICALL Java_org_openucx_jucx_UcxThreadAffinityNative_getAffinityNative(JNIEnv *env, jclass c, jint pid) {
    const size_t N = sizeof(cpu_set_t);
    cpu_set_t cpuset;

    int res = sched_getaffinity(pid, N, &cpuset);
    if (res < 0) {
        return NULL;
    }

    jbyteArray bytes = env->NewByteArray(N);
    env->SetByteArrayRegion(bytes, 0, N, (const jbyte *)(void *)&cpuset);
    return bytes;
}

JNIEXPORT jint JNICALL Java_org_openucx_jucx_UcxThreadAffinityNative_setAffinityNative(JNIEnv *env, jclass c, jint pid,
                                                                                       jbyteArray bytes) {
    const size_t M = env->GetArrayLength(bytes);
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);

    env->GetByteArrayRegion(bytes, 0, M, (jbyte *)(void *)&cpuset);
    return sched_setaffinity(pid, M, &cpuset);
}

JNIEXPORT jint JNICALL Java_org_openucx_jucx_UcxThreadAffinityNative_getCpuNative(JNIEnv *env, jclass c) {
    return sched_getcpu();
}

JNIEXPORT jint JNICALL Java_org_openucx_jucx_UcxThreadAffinityNative_getPidNative(JNIEnv *env, jclass c) {
    return (jint)syscall(SYS_getpid);
}

JNIEXPORT jint JNICALL Java_org_openucx_jucx_UcxThreadAffinityNative_getTidNative(JNIEnv *env, jclass c) {
    return (jint)syscall(SYS_gettid);
