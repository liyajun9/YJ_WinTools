Win32下常用的工具代码。字符串多使用std::string和std::wstring。


CYexception 方便Win32 API调用异常的统一处理，避免大量if else
 *CYexception 

 *CYwin32Exception: Win32异常类.包装了GetLastError()的翻译.

 *CYwsaException: WinSock异常类.包装了WSAGetLastError()的翻译.

  用法：
  try{
	...
	throw CYxxxException(类名，方法名，API名);
  }catch(CYxxxException& e){
	cout<<e.GetMsg()<<endl;
  }


 *Trace: Trace类.支持ansi和unicode.输出格式为 "2019-04-24 11:15:00 formatString\r\n"
  用法：YTRACE(fmt,...);

 *CYencodings:编码转换工具.目前支持GBK,UNICODE,UTF-8的转换，容器可以是字符数组或者std::string

 *CYsocketUtils:socket辅助工具.如地址结构的获取，转换等.

 *CYstringUtils:string辅助工具.如格式化字符串等.

 *CYbuffer: 一个方便使用buffer的


