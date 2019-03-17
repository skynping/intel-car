#include "bsp_usart.h"

static void USART_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// �����ж���Ϊ1 USART1 PA9,PA10
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ ;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE; // ���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; // ���� �������ֳ�
	USART_InitStructure.USART_StopBits = USART_StopBits_1; // ����ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;  // ����У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ����Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // ���ù���ģʽ���շ�һ��
	USART_Init(DEBUG_USARTx, &USART_InitStructure); // ��ɴ��ڵĳ�ʼ������
	
	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);//�����ж�
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USARTx, ENABLE);	
	
	USART_NVIC_Config();
}

// USART2�ж����ȼ�����
static void USART2_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		
	NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART2_IRQ ;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_USART2_GPIO_APBxClkCmd(DEBUG_USART2_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_USART2_APBxClkCmd(DEBUG_USART2_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART2_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	USART_InitStructure.USART_BaudRate = DEBUG_USART2_BAUDRATE; // ���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; // ���� �������ֳ�
	USART_InitStructure.USART_StopBits = USART_StopBits_1; // ����ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;  // ����У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ����Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // ���ù���ģʽ���շ�һ��
	USART_Init(DEBUG_USART2, &USART_InitStructure); // ��ɴ��ڵĳ�ʼ������
	
	USART_ITConfig(DEBUG_USART2, USART_IT_RXNE, ENABLE);//�����ж�
	
	USART_ClearITPendingBit(DEBUG_USART2, USART_IT_RXNE);
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USART2, ENABLE);	
	
	USART2_NVIC_Config();
}


/* ����һ���ֽ� */
void Usart_SendByte(USART_TypeDef* pUSARTx, uint8_t data)
{
	USART_SendData(pUSARTx, data);
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET );
}


/* ���������ֽڵ����� */
void Usart_SendHalfWord(USART_TypeDef* pUSARTx, uint16_t data)
{
	uint8_t temp_h,temp_l;
	
	temp_h = (data&0xff00) >> 8 ;
	temp_l = data&0xff;
	
	USART_SendData(pUSARTx, temp_h);
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET );
	
	USART_SendData(pUSARTx, temp_l);
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET );
}

/* ����8λ���ݵ����� */
void Usart_SendArray(USART_TypeDef* pUSARTx, uint8_t *array,uint8_t num)
{
	uint8_t i;
	for( i=0; i<num; i++ )
  {
		Usart_SendByte(pUSARTx, array[i]);
	}
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET );
}

/* �����ַ��� */
void Usart_SendStr(USART_TypeDef* pUSARTx, uint8_t *str)
{
	uint8_t i=0;
	do
  {
		Usart_SendByte(pUSARTx, *(str+i));
		i++;
	}while(*(str+i) != '\0');
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET );
}

///�ض���c�⺯��printf�����ڣ��ض����USART1��ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д���USART2��ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}



