package com.redknot.mmplayer;

public class MMPlayerJNI {
    static {
        System.loadLibrary("MMPlayerJNI");
    }
    public static native int add(int a, int b);
}
