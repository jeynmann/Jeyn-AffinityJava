package jeyn.affinity;

import java.util.BitSet;

public interface ThreadAffinity {
    int numaNum();
    int getNuma(int cpuid);
    boolean setNuma(int nodeid);

    BitSet getThreadAffinity();
    boolean setThreadAffinity(BitSet affinity);
    boolean setThreadGroupAffinity(BitSet affinity);

    int getCpu();
    int getPid();
    int getTid();
}
