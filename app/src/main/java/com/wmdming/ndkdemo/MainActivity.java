package com.wmdming.ndkdemo;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.TextView;

import com.orhanobut.logger.AndroidLogAdapter;
import com.orhanobut.logger.Logger;

public class MainActivity extends AppCompatActivity {

    public static final String TAG = "MainActivity";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        initData();

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
//        JavaCallC javaCallC = new JavaCallC();
//        tv.setText(javaCallC.stringFromJNI());


        // 1、获取百度首页
        // 2、先调用C接口
        // 3、在C接口中调用Java接口访问网络请求


//        int i = javaCallC.addNum(1, 2);
//        Log.e(TAG, "" + i);
//
//
//        String java = javaCallC.sayHello("java");
//        Log.e(TAG, java);
//
//        int[] array = {1, 2, 3};
//
//        int[] ints = javaCallC.increaseArrayEles(array);
//
//        for (int anInt : ints) {
//            Log.e(TAG, "数组中的元素: " + anInt);
//        }
//
//
//        int result = javaCallC.checkPassword("123");
//        if (result == 0) {
//            Log.e(TAG, "密码正确");
//        } else {
//            Log.e(TAG, "密码错误");
//        }
//
//        CCallJava cCallJava = new CCallJava();
//        int i1 = cCallJava.callbackAdd();
//        Logger.e("result = %s", i1);
//
//        cCallJava.callbackMessage();
//
//        cCallJava.callbackSayHello();


        tv.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                test4();
            }


        });
    }

    private void test6() {
        JavaCallC javaCallC = new JavaCallC();
        String data = javaCallC.sayHello("111111");
        Logger.e("data: " + data);
    }

    private void test5() {
        JavaCallC javaCallC = new JavaCallC();
        int add = javaCallC.add(1, 2);
        Logger.e("data: " + add);
    }

    private void test4() {
        JavaCallC javaCallC = new JavaCallC();

        byte[] byte2 = javaCallC.getByte2("wdming你好".getBytes());

        Logger.e("data: " + new String(byte2));

    }

    private void test3() {

        JavaCallC javaCallC = new JavaCallC();
        byte[] data = javaCallC.getByte("wdming{123}");
        Logger.e("data: " + new String(data));

    }


    private void test2() {

        JavaCallC javaCallC = new JavaCallC();
        User user = javaCallC.getUser2(1, "wmding");
        Logger.e("user: " + new String(user.getData()));
    }


    private void test1() {
        JavaCallC javaCallC = new JavaCallC();

        User user = javaCallC.getUser(1, "wmding");
        Logger.e("user: " + user.getAge());
        Logger.e("user: " + user.getName());
    }

    private void initData() {
        Logger.addLogAdapter(new AndroidLogAdapter());
    }


}
