package com.wmdming.ndkdemo;

/**
 * @author 明月
 * @version 1.0
 * @date 6/30/21 9:50 AM
 * @description:
 */
public class CmdResult {

    private int code;
    private byte[] data;

    public int getCode() {
        return code;
    }

    public byte[] getData() {
        return data;
    }

    public void setCode(int code) {
        this.code = code;
    }

    public void setData(byte[] data) {
        this.data = data;
    }
}
