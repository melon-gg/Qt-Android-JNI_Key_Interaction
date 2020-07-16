package com.simon;
import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;
import android.widget.Toast;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import java.io.*;
import java.lang.Thread;
import android.view.KeyEvent;
public class ExtendsQtWithJava extends org.qtproject.qt5.android.bindings.QtActivity
{
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        new HeightProvider(this).init().setHeightListener(new HeightProvider.HeightListener() {
            @Override
            public void onHeightChanged(int height) {
                Log.v("tag", "获取到键盘高度" + height);
            }
        });
    }
    private static int pageIdx = 0;
    public static native String GetQtVersion();
    public boolean onKeyDown(int keyCode, KeyEvent event) {
    if(keyCode == KeyEvent.KEYCODE_BACK && pageIdx == 0){
        moveTaskToBack(true);
        Log.v("vlog","move task to back!");
        return true;
    }
    else
    {
        ExtendsQtWithNative.BackKeyPress();
        Log.v("vlog", "back to home page");
        return true;
    }
    //return super.onKeyDown(keyCode, event);
}
    public static String setPageIdx(int idx) {
            pageIdx = idx;
            Log.v("vlog", "set pageIdx:" + pageIdx);
            return "";
        }
    public static String printVLog(String log){
        Log.v("vlog", log);
        return "";
    }
    public static String printQtVersion(){
        ExtendsQtWithNative.GetQtVersion();
        return "";
        }
};
