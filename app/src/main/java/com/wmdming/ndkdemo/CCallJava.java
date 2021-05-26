package com.wmdming.ndkdemo;

import com.orhanobut.logger.Logger;

/**
 * @author wmding
 * @date 2020/8/1
 * @describe
 */
public class CCallJava {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }


    public int add(int x, int y) {
        Logger.i("x=%s", x);
        Logger.i("y=%s", y);
        return x + y;
    }

    public void message() {
        Logger.i("message");
    }


    public static void sayHello(String str1) {
        Logger.i("str1=%s", str1);
    }

    public native int callbackAdd();

    public native void callbackMessage();

    public native void callbackSayHello();
}
