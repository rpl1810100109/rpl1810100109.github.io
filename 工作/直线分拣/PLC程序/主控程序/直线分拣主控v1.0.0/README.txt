/*落格成功向上位机返回*/
	
//起始符
*(SendToWCSFirstAddress) = 0x02;
//分拣完成
*(SendToWCSFirstAddress+1) = 53;
    
//报文编号
for(int i = 2; i<=9;i++)
{
     *(SendToWCSFirstAddress+i) = *(RCVDateFormLOW+i);
}
//小车号
for(int i =10;i<=13; i++)
{
    *(SendToWCSFirstAddress+i) = *(RCVDateFormLOW+i);
}
//格口
for(int i=14;i<=16;i++)
{  *(SendToWCSFirstAddress+i) = *(RCVDateFormLOW+i);
}
//五位空格
for(int i =17;i<=21;i++)
{
     *(SendToWCSFirstAddress+i) = 32;
}
*(SendToWCSFirstAddress+23) = 0x03;


V1.0.1更新日志：

1.删除了定时中断累计时间去触发相机的操作，改为使用皮带线上的光电信号触发。
2.保留了定时中断累计一个时间用来与皮带线同步，后续将会删除，统一使用光电触发后的定时器。