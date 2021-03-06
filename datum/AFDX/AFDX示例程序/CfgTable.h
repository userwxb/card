/*****************************************/
/********* Configuration table ***********/
/*****************************************/


/***********ES Partion Configration Table**********/
static ES_PARTIONCfg esPartionCfg=
{
    "ES_1", /*ES 名称 */
    1,      /*由domainId、SideId和LocationId*/
            /*按照协议组成*/
    1,      /*5位二进制代码*/  
    0       /*保证四字节对齐*/   	
};



/***********ES1 Snd Ports Configration Table**********/
static portCfg es1_snd_ports[] = {
     
	{
        1,           /*portID;*/ 
        0x0a0a2501,  /*IP源地址*/
        0xe0e0002d,  /*IP目的地址*/
        1024,        /*UDP源地址*/
        1024,        /*UDP目的地址*/
        45,          /*VL的ID*/
        1,           /*子VL号*/
        AFDX_SAP,    /*端口类型*/
        30,          /*UDP缓冲消息个数，此参数用于队列模式*/
        1471,        /*udp缓冲消息最大长度*/
        0,           /*udp刷新频率    */
        0,           /*分片标志*/                  
    },
    {
        2,             /*portID;*/ 
        0x0a0a2601,    /*IP源地址*/
        0xe0e0002e,    /*IP目的地址*/
        1025,          /*UDP源地址*/
        1025,          /*UDP目的地址*/
        46,            /*VL的ID*/
        1,             /*子VL号*/
        AFDX_QUEUING,  /*端口类型*/
        30,            /*UDP缓冲消息个数，此参数用于队列模式*/
        1471,          /*udp缓冲消息最大长度*/
        0,             /*udp刷新频率    */
        0,             /*分片标志*/          
        
	},
    {
        3,              /*portID;*/ 
        0x0a0a2701,     /*IP源地址*/
        0xe0e0002f,     /*IP目的地址*/
        1026,           /*UDP源地址*/
        1026,           /*UDP目的地址*/
        47,             /*VL的ID*/
        1,              /*子VL号*/
        AFDX_SAMPLING,  /*端口类型*/
        30,             /*UDP缓冲消息个数，此参数用于队列模式*/
        1471,           /*udp缓冲消息最大长度*/
        0,              /*udp刷新频率    */
        0,              /*分片标志*/          
        
    }
};

/*ES1 send virtual link Configration Table*/
static SendVLCfg es1_snd_vls[]={    
    {
        45,         /*VL唯一的ID号*/
        1,          /*子虚拟链路数*/
        0,          /*偏移量*/
        0,          /*带宽分配间隔*/
        1518,       /*最大帧长度*/
        64,         /*最小帧长度*/
        3,         /*网络选择*/
        50,         /*最大允许抖动*/    	
    },
    {
        46,         /*VL唯一的ID号*/
        1,          /*子虚拟链路数*/
        0,          /*偏移量*/
        0,          /*带宽分配间隔*/
        1518,       /*最大帧长度*/
        64,         /*最小帧长度*/
        3,          /*网络选择*/
        50,        /*最大允许抖动*/    	
    },
    {
        47,         /*VL唯一的ID号*/
        1,          /*子虚拟链路数*/
        0,          /*偏移量*/
        0,          /*带宽分配间隔*/
        1518,       /*最大帧长度*/
        64,         /*最小帧长度*/
        3,         /*网络选择*/
        50,        /*最大允许抖动*/    	
    }
        
};

/***********ES2 Snd Ports Configration Table**********/
static portCfg es2_snd_ports[] = {    
	{
        7,           /*portID;*/ 
        0x0a0a2501,  /*IP源地址*/
        0xe0e0002d,  /*IP目的地址*/
        1024,        /*UDP源地址*/
        1024,        /*UDP目的地址*/
        48,          /*VL的ID*/
        1,           /*子VL号*/
        AFDX_SAP,    /*端口类型*/
        30,          /*UDP缓冲消息个数，此参数用于队列模式*/
        1471,        /*udp缓冲消息最大长度*/
        0,           /*udp刷新频率    */
        0,           /*分片标志*/                  
    },
    {
        8,             /*portID;*/ 
        0x0a0a2601,    /*IP源地址*/
        0xe0e0002e,    /*IP目的地址*/
        1025,          /*UDP源地址*/
        1025,          /*UDP目的地址*/
        49,            /*VL的ID*/
        1,             /*子VL号*/
        AFDX_QUEUING,  /*端口类型*/
        30,            /*UDP缓冲消息个数，此参数用于队列模式*/
        1471,          /*udp缓冲消息最大长度*/
        0,             /*udp刷新频率    */
        0,             /*分片标志*/          
	},
    {
        9,              /*portID;*/ 
        0x0a0a2701,     /*IP源地址*/
        0xe0e0002f,     /*IP目的地址*/
        1026,           /*UDP源地址*/
        1026,           /*UDP目的地址*/
        50,             /*VL的ID*/
        1,              /*子VL号*/
        AFDX_SAMPLING,  /*端口类型*/
        30,             /*UDP缓冲消息个数，此参数用于队列模式*/
        1471,           /*udp缓冲消息最大长度*/
        0,              /*udp刷新频率    */
        0,              /*分片标志*/          
    }
};

/*ES2 send virtual link Configration Table*/
static SendVLCfg es2_snd_vls[]={    
    {
        48,         /*VL唯一的ID号*/
        1,          /*子虚拟链路数*/
        0,          /*偏移量*/
        0,          /*带宽分配间隔*/
        1518,       /*最大帧长度*/
        64,         /*最小帧长度*/
        3,         /*网络选择*/
        50,         /*最大允许抖动*/    	
    },
    {
        49,         /*VL唯一的ID号*/
        1,          /*子虚拟链路数*/
        0,          /*偏移量*/
        0,          /*带宽分配间隔*/
        1518,       /*最大帧长度*/
        64,         /*最小帧长度*/
        3,          /*网络选择*/
        50,        /*最大允许抖动*/    	
    },
    {
        50,         /*VL唯一的ID号*/
        1,          /*子虚拟链路数*/
        0,          /*偏移量*/
        0,          /*带宽分配间隔*/
        1518,       /*最大帧长度*/
        64,         /*最小帧长度*/
        3,         /*网络选择*/
        50,        /*最大允许抖动*/    	
    }
        
};


/***********ES1 recv Ports Configration Table**********/
static portCfg es1_rcv_ports[] = {    	
	{

		4,           /*portID;*/ 
		0x0a0a2501,  /*IP源地址*/
		0xe0e0002d,  /*IP目的地址*/
		1024,        /*UDP源地址*/
		1024,        /*UDP目的地址*/
		45,          /*VL的ID*/
		1,           /*子VL号*/
		AFDX_SAP,    /*端口类型*/
		30,          /*UDP缓冲消息个数，此参数用于队列模式*/
		1471,        /*udp缓冲消息最大长度*/
		0,           /*udp刷新频率    */
		0,           /*分片标志*/                  
	},
	{
		5,             /*portID;*/ 
		0x0a0a2601,    /*IP源地址*/
		0xe0e0002e,    /*IP目的地址*/
		1025,          /*UDP源地址*/
		1025,          /*UDP目的地址*/
		46,            /*VL的ID*/
		1,             /*子VL号*/
		AFDX_QUEUING,  /*端口类型*/
		30,            /*UDP缓冲消息个数，此参数用于队列模式*/
		1471,          /*udp缓冲消息最大长度*/
		0,             /*udp刷新频率    */
		0,             /*分片标志*/          
				
	},
	{
		6,              /*portID;*/ 
		0x0a0a2701,     /*IP源地址*/
		0xe0e0002f,     /*IP目的地址*/
		1026,           /*UDP源地址*/
		1026,           /*UDP目的地址*/
		47,             /*VL的ID*/
		1,              /*子VL号*/
		AFDX_SAMPLING,  /*端口类型*/
		30,             /*UDP缓冲消息个数，此参数用于队列模式*/
		1471,           /*udp缓冲消息最大长度*/
		0,              /*udp刷新频率    */
		0,              /*分片标志*/          
					
	}
};

/*ES1 recv virtual link Configration Table*/
static RecVLCfg es1_rcv_vls[]={    
	{
		45,         /*VL唯一的ID号*/
		//      1,          /*子虚拟链路数*/
		0,          /*偏移量*/
		0,          /*带宽分配间隔*/
		1518,       /*最大帧长度*/
		64,         /*最小帧长度*/
		1,         /*完整性检测*/
		1,         /*冗余管理*/    	
	},
	{
		46,         /*VL唯一的ID号*/
		//       1,          /*子虚拟链路数*/
		0,          /*偏移量*/
		0,          /*带宽分配间隔*/
		1518,       /*最大帧长度*/
		64,         /*最小帧长度*/
		1,         /*完整性检测*/
		1,         /*冗余管理*/     	
	},
	{
		47,         /*VL唯一的ID号*/
		//        1,          /*子虚拟链路数*/
		0,          /*偏移量*/
		0,          /*带宽分配间隔*/
		1518,       /*最大帧长度*/
		64,         /*最小帧长度*/
		1,         /*完整性检测*/
		1,         /*冗余管理*/     	
	}
			
};


/***********ES2 recv Ports Configration Table**********/
static portCfg es2_rcv_ports[] = {    	
	{

		10,           /*portID;*/ 
		0x0a0a2501,  /*IP源地址*/
		0xe0e0002d,  /*IP目的地址*/
		1024,        /*UDP源地址*/
		1024,        /*UDP目的地址*/
		48,          /*VL的ID*/
		1,           /*子VL号*/
		AFDX_SAP,    /*端口类型*/
		30,          /*UDP缓冲消息个数，此参数用于队列模式*/
		1471,        /*udp缓冲消息最大长度*/
		0,           /*udp刷新频率    */
		0,           /*分片标志*/                  
	},
	{
		11,             /*portID;*/ 
		0x0a0a2601,    /*IP源地址*/
		0xe0e0002e,    /*IP目的地址*/
		1025,          /*UDP源地址*/
		1025,          /*UDP目的地址*/
		49,            /*VL的ID*/
		1,             /*子VL号*/
		AFDX_QUEUING,  /*端口类型*/
		30,            /*UDP缓冲消息个数，此参数用于队列模式*/
		1471,          /*udp缓冲消息最大长度*/
		0,             /*udp刷新频率    */
		0,             /*分片标志*/          
				
	},
	{
		12,              /*portID;*/ 
		0x0a0a2701,     /*IP源地址*/
		0xe0e0002f,     /*IP目的地址*/
		1026,           /*UDP源地址*/
		1026,           /*UDP目的地址*/
		50,             /*VL的ID*/
		1,              /*子VL号*/
		AFDX_SAMPLING,  /*端口类型*/
		30,             /*UDP缓冲消息个数，此参数用于队列模式*/
		1471,           /*udp缓冲消息最大长度*/
		0,              /*udp刷新频率    */
		0,              /*分片标志*/          
					
	}
};

/*ES2 recv virtual link Configration Table*/
static RecVLCfg es2_rcv_vls[]={    
	{
		48,         /*VL唯一的ID号*/
		//      1,          /*子虚拟链路数*/
		0,          /*偏移量*/
		0,          /*带宽分配间隔*/
		1518,       /*最大帧长度*/
		64,         /*最小帧长度*/
		1,         /*完整性检测*/
		1,         /*冗余管理*/    	
	},
	{
		49,         /*VL唯一的ID号*/
		//       1,          /*子虚拟链路数*/
		0,          /*偏移量*/
		0,          /*带宽分配间隔*/
		1518,       /*最大帧长度*/
		64,         /*最小帧长度*/
		1,         /*完整性检测*/
		1,         /*冗余管理*/     	
	},
	{
		50,         /*VL唯一的ID号*/
		//        1,          /*子虚拟链路数*/
		0,          /*偏移量*/
		0,          /*带宽分配间隔*/
		1518,       /*最大帧长度*/
		64,         /*最小帧长度*/
		1,         /*完整性检测*/
		1,         /*冗余管理*/     	
	}
			
};


/* ES Configuration Table */

static ESCfg escfg[]=
{
	{
		1,               /*es 配置编号*/
		0,               /*速度，100或10Mbps*/
		0x100000,        /*配置文件长度，单位字节*/
		0x20101014,      /*配置表版本号*/
		"ES_1",			 /*端系统名称*/
		1,               /*Domain ID*/
		1,               /*Side ID*/
		4,               /*Location ID*/
		0,               /*保证四字节对齐*/
         
		1,               /*分区数*/
		NULL,	         /*分区配置*/

		3,               /*发送端口个数*/
		&es1_snd_ports[0],   /*发送端口配置*/
        
		3,				 /*接收端口个数*/
		&es1_rcv_ports[0],   /*接收端口配置*/
    
		3,               /*发送VL个数*/
		&es1_snd_vls[0],     /*发送VL配置*/
    
		3,               /*接收VL个数*/
		&es1_rcv_vls[0],     /*接收VL配置*/
    
		NULL,            /*ICMP配置*/
		NULL,            /*RTC*/
		NULL,            /*SNMP配置*/
		NULL            /*ARINC615A配置*/
	}
 	,
	{
		2,               /*es 配置编号*/
		0,               /*速度，100或10Mbps*/
		0x100000,        /*配置文件长度，单位字节*/
		0x20101014,      /*配置表版本号*/
		"ES_2",			 /*端系统名称*/
		1,               /*Domain ID*/
		1,               /*Side ID*/
		4,               /*Location ID*/
		0,               /*保证四字节对齐*/
         
		1,               /*分区数*/
		NULL,	           /*分区配置*/

		3,               /*发送端口个数*/
		&es2_snd_ports[0],   /*发送端口配置*/
        
		3,            /*接收端口个数*/
		&es2_rcv_ports[0],   /*接收端口配置*/
    
		3,               /*发送VL个数*/
		&es2_snd_vls[0],     /*发送VL配置*/
    
		3,               /*接收VL个数*/
		&es2_rcv_vls[0],     /*接收VL配置*/
    
		NULL,            /*ICMP配置*/
		NULL,            /*RTC*/
		NULL,            /*SNMP配置*/
		NULL            /*ARINC615A配置*/
 	}
}   		
;
