#include "interface.h"
#include <QDebug>

Interface* Interface::instance = nullptr;

Interface::Interface(QObject *parent) : QObject(parent)
{

}

Interface *Interface::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Interface();
    }
    return instance;
}

void Interface::getQtVersion(JNIEnv *env, jobject thiz)
{
    QString version(qVersion());
    QAndroidJniObject javaString = QAndroidJniObject::fromString(version);
    //return javaString.object<jstring>();
}

void Interface::backKeyPress(JNIEnv *env, jobject thiz)
{
    //java监听到按钮事件，调用c++发送信号给qml处理响应
    emit Interface::getInstance()->backPress();
}

bool Interface::registerNativeMethods()
{
    JNINativeMethod methods[]{
        {"GetQtVersion", "()V", (void*)getQtVersion},
        {"BackKeyPress", "()V", (void*)backKeyPress}
    };
    jclass clazz;
    QAndroidJniEnvironment env;
    QAndroidJniObject javaClass("com/simon/ExtendsQtWithNative");
    clazz = env->GetObjectClass(javaClass.object<jobject>());
    bool result = false;
    if(clazz)
    {
        jint ret = env->RegisterNatives(clazz, methods, sizeof (methods) / sizeof (methods[0]));
        env->DeleteLocalRef(clazz);
        result = ret >= 0;
    }
    if(env->ExceptionCheck())
        env->ExceptionClear();
    return  result;
}

void Interface::printVLog(QString log)
{
    QAndroidJniEnvironment env;
    QByteArray ba = log.toLatin1(); // must
    jstring s = env->NewStringUTF(ba.data());
    QAndroidJniObject retStr = QAndroidJniObject::callStaticObjectMethod(
               "com/simon/ExtendsQtWithJava", "printVLog","(Ljava/lang/String;)Ljava/lang/String;", s);
}

void Interface::callJavaNativeChangeIndex(int idx)
{
#ifdef ANDROID

    //返回String类型
    QAndroidJniObject::callStaticObjectMethod("com/simon/ExtendsQtWithJava", "setPageIdx","(I)Ljava/lang/String;", idx);
#endif
}

void Interface::qmlChangeIndex(int idx)
{
    callJavaNativeChangeIndex(idx);
}
