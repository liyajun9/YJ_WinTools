Win32下常用的工具代码。命名空间统一为YJ_Tools。字符串多使用标准库字符串。


YJ_WinTools.h: 声明命名空间，包含库内常用头文件.



YJ_Exception 方便Win32 API调用异常的统一处理，避免大量if else
 *CException 

 *CWin32Exception: Win32异常类.包装了GetLastError()的翻译.

 *CWSAException: WinSock异常类.包装了WSAGetLastError()的翻译.

  用法：
  try{
	...
	throw CxxxException(类名，方法名，API名);
  }catch(CxxxException& e){
	cout<<e.GetMsg()<<endl;
  }



YJ_Utils 常用工具类
 *Trace: Trace类.支持ansi和unicode.输出格式为 "2019-04-24 11:15:00 formatString\r\n"
  用法：YTRACE(fmt,...);

 *Encodings:编码转换工具.目前支持GBK,UNICODE,UTF-8的转换，容器可以是字符数组或者std::string

 *CSocketUtils:socket辅助工具.如地址结构的获取，转换等.


