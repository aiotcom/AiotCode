#include ""

/* ��ʱ���� */

void Delay(uint32_t delay)   
{
    int i=0;
    for(i = 0;i<delay;i++)
    {;}
}

/*  1��  850ns�ߵ�ƽ  400ns�͵�ƽ*/
void RGB_Set_UP()
{
    GPIOB->BSRR = GPIO_Pin_10;
    Delay(4);
    
    GPIOB->BRR = GPIO_Pin_10;
    Delay(0);
}

/*  0��  400ns�ߵ�ƽ  850ns�͵�ƽ*/
void RGB_Set_Down()
{
    GPIOB->BSRR = GPIO_Pin_10;
    Delay(0);

    GPIOB->BRR = GPIO_Pin_10;
    Delay(4);
}

/*  ������ɫ  */
void bottom_rgb_led_set_colour(uint32_t G8R8B8)
{
	int byte = 0;
	int i = 0;
	for(i = 23;i>=0;i--)
	{
		byte = ((G8R8B8 >> i) & 0x01);
		if(byte == 1)
		{
			RGB_Set_UP();//1
		}
		else
		{
			RGB_Set_Down(); //0
		}
	}
}

/*  ���͵�ƽ�ȴ���һ������   */
void RGB_REST(void)
{
	bottom_rgb_led_pin_table[0].GPIOx->BRR = bottom_rgb_led_pin_table[0].pin;
	Delay(8000);  //��ʱ58us
    bottom_rgb_led_set_colour(0xFF00);
}
/*
��ʼ���ײ�rgb led��
*/
void bottom_rgb_led_init(void)
{
    _lib_io_init_output(&bottom_rgb_led_pin_table[0],1);
    RGB_REST();
}