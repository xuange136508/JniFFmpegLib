package jni.demo.com.jnidemo.jni;



public class JniUtils {

    static
    {
        //jni库
        System.loadLibrary("avutil-54");
        System.loadLibrary("swresample-1");
        System.loadLibrary("avcodec-56");
        System.loadLibrary("avformat-56");
        System.loadLibrary("swscale-3");
        System.loadLibrary("postproc-53");
        System.loadLibrary("avfilter-5");
        System.loadLibrary("avdevice-56");
        System.loadLibrary("jni_demo");
    }

    //ffmpeg获取信息
    //编译只需要ffmpeg_so和include的头文件
    public native String execute();

    //执行命令行，编译就需要command里的c文件和头文件,还有include里的compat
    public static native int getRotation(String path);
    public static native int ffmpegcode(int argc,String[] argv);


}