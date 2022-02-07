package com.wmdming.ndkdemo;

/**
 * @author wmding
 * @date 2020/8/1
 * @describe
 */
public class JavaCallC {


    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int addNum(int a, int b);

    public native String sayHello(String str1);

    public native int[] increaseArrayEles(int[] intArray);

    public native int checkPassword(String pwd);

    public native User getUser(int age, String name);

    public native User getUser2(int age, String name);

    public native byte[] getByte(String name);

    public native byte[] getByte2(byte[] name);

    public native int add(int a,int b);

    public native CmdResult getCmdResult();

    public native CmdResult sendCmd(byte[] data);
}
