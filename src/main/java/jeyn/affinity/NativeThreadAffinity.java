package jeyn.affinity;

import java.util.BitSet;
import java.util.Locale;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.net.URL;

public enum NativeThreadAffinity implements ThreadAffinity {
    INSTANCE;

    public static final boolean LOADED;
    public static final int NUMA;

    @Override
    public int numaNum() {
        return numaNumNative();
    }

    @Override
    public int getNuma(int cpuid) {
        return getNumaNative(cpuid);
    }

    @Override
    public boolean setNuma(int nodeid) {
        return setNumaNative(nodeid) == 0;
    }

    @Override
    public BitSet getThreadAffinity() {
        final byte[] buff = getAffinityNative(0);
        if (buff == null) {
            return null;
        }
        return BitSet.valueOf(buff);
    }

    @Override
    public boolean setThreadAffinity(BitSet affinity) {
        return setAffinityNative(0, affinity.toByteArray()) == 0;
    }

    @Override
    public boolean setThreadGroupAffinity(BitSet affinity) {
        return setAffinityNative(getPidNative(), affinity.toByteArray()) == 0;
    }

    @Override
    public int getCpu() {
        return getCpuNative();
    }

    @Override
    public int getPid() {
        return getPidNative();
    }

    @Override
    public int getTid() {
        return getTidNative();
    }

    private static native int numaNumNative();

    private static native int getNumaNative(int cpuid);

    private static native int setNumaNative(int nodeid);

    private static native byte[] getAffinityNative(int pid);

    private static native int setAffinityNative(int pid, byte[] affinity);

    private static native int getCpuNative();

    private static native int getPidNative();

    private static native int getTidNative();

    private static File extractDir = null;
    private static final String NATIVE_RESOURCE_HOME = "META-INF/native/";
    private static final String NAME = "native_affinity";

    static {
        loadNativeLibrary();
        LOADED = loadNumaLibrary();
        NUMA = numaNumNative();
    }

    private static boolean loadNumaLibrary() {
        try {
            System.loadLibrary("numa");
            return true;
        } catch (UnsatisfiedLinkError e) {
            return false;
        }
    }

    protected static void loadNativeLibrary() {
        String name = System.getProperty("os.name").toLowerCase(Locale.US).trim();
        if (!name.startsWith("linux")) {
            throw new IllegalStateException("Only supported on Linux");
        }

        String libName = System.mapLibraryName(NAME);
        String libpath = NATIVE_RESOURCE_HOME + libName;
        URL url = null;

        ClassLoader loader = ThreadAffinity.class.getClassLoader();
        if (loader == null) {
            url = ClassLoader.getSystemResource(libpath);
        } else {
            url = loader.getResource(libpath);
        }

        if (url == null) {
            // If not found in classpath, try to load from java.library.path
            System.loadLibrary(NAME);
            return;
        }

        File file;
        try {
            file = extractResource(url);
        } catch (IOException e) {
            throw new UnsatisfiedLinkError("Failed to load native lib: " + e);
        }

        if (file != null && file.exists()) {
            System.load(file.getAbsolutePath());
            return;
        }

        throw new UnsatisfiedLinkError("Failed to load native lib: " + file.getName());
    }

    protected static File extractResource(URL libPath) throws IOException {
        if (extractDir == null) {
            Path tmp = Files.createTempDirectory(NAME);
            extractDir = tmp.toFile();
            extractDir.deleteOnExit();
        }

        InputStream is = libPath.openStream();
        if (is == null) {
            throw new IOException("Error extracting native library content");
        }

        File file = new File(extractDir, new File(libPath.getPath()).getName());
        file.deleteOnExit();
        FileOutputStream os = null;
        try {
            os = new FileOutputStream(file);
            streamcopy(is, os);
        } finally {
            if (os != null) {
                os.flush();
                os.close();
            }
            is.close();
        }
        return file;
    }

    protected static void streamcopy(InputStream is, OutputStream os)
            throws IOException {
        if (is == null || os == null) {
            return;
        }
        byte[] buffer = new byte[4096];
        int length = 0;
        while ((length = is.read(buffer)) != -1) {
            os.write(buffer, 0, length);
        }
    }
    // public static final int EFAULT = 14;
    // public static final int EINVAL = 22;
    // public static final int ESRCH = 3;
}
