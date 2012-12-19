#if SWIGJAVA

%pragma(java) jniclasscode=%{
    static {
        System.loadLibrary("freequant-java" );
    }
%}

%include "../freequant.i"

#endif // End of Java specific sections
