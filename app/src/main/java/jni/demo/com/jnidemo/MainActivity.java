package jni.demo.com.jnidemo;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;
import java.io.File;
import jni.demo.com.jnidemo.jni.JniUtils;

public class MainActivity extends AppCompatActivity {


    private JniUtils mJniUtils;

    private String dir = Environment.getExternalStorageDirectory().getAbsolutePath();
    private File inputfile;
    private File outfile;

    //http://blog.csdn.net/glouds/article/details/50937266

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mJniUtils = new JniUtils();
        inputfile = new File(dir,"a.mp4");
        outfile = new File(dir, "out.mp4");

        findViewById(R.id.btn_test1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getRotateInfo();
            }
        });
        findViewById(R.id.btn_test2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                excuteCmd();
            }
        });
        findViewById(R.id.btn_test3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                toast(mJniUtils.execute());
            }
        });


    }

    private void excuteCmd() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                //也就是视频压缩
                StringBuffer cmdLine = new StringBuffer("ffmpeg -i ");
                cmdLine.append(inputfile.getAbsolutePath());

                cmdLine.append(" -b:v 640k");//比特率
                cmdLine.append(" -s 640*480 ");//大小

                cmdLine.append(outfile.getAbsolutePath());

                toast("信息:"+ cmdLine.toString());
                String[] argv = cmdLine.toString().split(" ");
                int argc = argv.length;

                toast("开始转码");
                mJniUtils.ffmpegcode(argc, argv);
                toast("结束转码");
            }
        }).start();
    }

    private void getRotateInfo() {
        if(inputfile.exists()){
            int res = mJniUtils.getRotation(inputfile.getAbsolutePath());
            toast(res+"");//结果为90
        }else{
            toast("文件不存在");
        }
    }


    private void toast(final String mDemo){
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(MainActivity.this, mDemo,Toast.LENGTH_SHORT).show();
            }
        });
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
    }



}
