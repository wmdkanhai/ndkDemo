package com.wmdming.ndkdemo;


/**
 * @author 明月
 * @date 5/26/21 12:13 PM
 * @version 1.0
 * @description:
 */
public class User {
    private int age;
    private String name;
    private byte[] data;

    public User() {
    }

    public User(int age, String name) {
        this.age = age;
        this.name = name;
    }

    public User(int age, String name, byte[] data) {
        this.age = age;
        this.name = name;
        this.data = data;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public byte[] getData() {
        return data;
    }

    public void setData(byte[] data) {
        this.data = data;
    }

    @Override
    public String toString() {
        return "User{" +
                "age=" + age +
                ", name='" + name + '\'' +
                '}';
    }
}
