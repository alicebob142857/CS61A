#include "zigbee.h"
volatile uint8_t zigbeeReceive[ZIGBEE_MESSAGE_LENTH];	//ʵʱ��¼�յ�����Ϣ
volatile uint8_t zigbeeMessage[ZIGBEE_MESSAGE_LENTH];//��������˳���õ�����Ϣ
volatile int message_index = 0;
volatile int message_head = -1;
uint8_t zigbeeBuffer[1];

UART_HandleTypeDef* zigbee_huart;


volatile struct BasicInfo Game;//�������״̬��ʱ�䡢й�����Ϣ
volatile struct CarInfo Car;//���泵����Ϣ
volatile struct PassengerInfo Passenger;//������Ա����Ϣ��λ�ú��ʹ�λ��
volatile struct PackageInfo Package[6];//�����Ѵ���ʵ���Ϣ
volatile struct FloodInfo Flood[5];//����й���λ����Ϣ
volatile struct ObstacleInfo Obstacle[8];//���������ϰ���Ϣ
/***********************�ӿ�****************************/
void zigbee_Init(UART_HandleTypeDef *huart)
{
	zigbee_huart = huart;
	HAL_UART_Receive_IT(zigbee_huart, zigbeeBuffer, 1);
}
void zigbeeMessageRecord(void)
{
	zigbeeMessage[message_index] = zigbeeBuffer[0];
	message_index = receiveIndexAdd(message_index, 1);    //һ���򵥵����������Ӻ���

	if (zigbeeMessage[receiveIndexMinus(message_index, 2)] == 0x0D
		&& zigbeeMessage[receiveIndexMinus(message_index, 1)] == 0x0A)//һ����Ϣ�Ľ�β
	{
		if (receiveIndexMinus(message_index, message_head) == 0)
		{

			int index = message_head;
			for (int i = 0; i < 70; i++)
			{
				zigbeeReceive[i] = zigbeeMessage[index];
				index = receiveIndexAdd(index, 1);
			}
			Decode();
		}
		else
		{
			message_head = message_index;
		}
	}
	HAL_UART_Receive_IT(zigbee_huart, zigbeeBuffer, 1);
}
enum GameStateEnum getGameState(void)
{
	uint8_t state = Game.GameState;
	if (state == 0)
	{
		return GameNotStart;
	}
	else if (state == 1)
	{
		return GameGoing;
	}
	else if (state == 2)
	{
		return GamePause;
	}
	else if (state == 3)
	{
		return GameOver;
	}

	return GameNotStart;
}
uint16_t getGameTime(void)
{
	return Game.Time;
}
uint16_t getGameFlood(void)
{
    return (uint16_t)Game.stop;
}
uint16_t getPassengerstartposX(void)
{
    return Passenger.startpos.X;
}
uint16_t getPassengerstartposY(void)
{
    return Passenger.startpos.Y;
}
struct Position getPassengerstartpos(void)
{
    return Passenger.startpos;
}
uint16_t getPassengerfinalposX(void)
{
    return Passenger.finalpos.X;
}
uint16_t getPassengerfinalposY(void)
{
    return Passenger.finalpos.Y;
}
struct Position getPassengerfinalpos(void)
{
    return Passenger.finalpos;
}
uint16_t getFloodposX(int FloodNo)
{
    return Flood[FloodNo].pos.X;
}
uint16_t getFloodposY(int FloodNo)
{
    return Flood[FloodNo].pos.Y;
}
struct Position getFloodpos(int FloodNo)
{
    return Flood[FloodNo].pos;
}
uint16_t getCarposX()
{
		return (uint16_t)Car.pos.X;

}
uint16_t getCarposY()
{
		return (uint16_t)Car.pos.Y;
}
struct Position getCarpos()
{
		return Car.pos;
}
uint16_t getCarWhetherRightPos()
{
    return (uint16_t)Car.WhetherRightPos;
}

uint16_t getPackageposX(int PackNo)
{
    if (PackNo != 0 && PackNo != 1 && PackNo != 2 && PackNo != 3 && PackNo != 4 && PackNo != 5)
		return (uint16_t)INVALID_ARG;
	else
		return (uint16_t)Package[PackNo].pos.X;
}
uint16_t getPackageposY(int PackNo)
{
    if (PackNo != 0 && PackNo != 1 && PackNo != 2 && PackNo != 3 && PackNo != 4 && PackNo != 5)
		return (uint16_t)INVALID_ARG;
	else
		return (uint16_t)Package[PackNo].pos.Y;
}
uint16_t getPackagewhetherpicked(int PackNo)
{
	if (PackNo != 0 && PackNo != 1 && PackNo != 2 && PackNo != 3 && PackNo != 4 && PackNo != 5)
		return (uint16_t)INVALID_ARG;
	else
		return (uint16_t)Package[PackNo].whetherpicked;
}
struct Position getPackagepos(int PackNo)
{
		return Package[PackNo].pos;
}
uint16_t getCarpicknum()
{
		return (uint16_t)Car.picknum;
}
uint16_t getCartransportnum()
{
		return (uint16_t)Car.transportnum;
}
uint16_t getCartransport()
{
		return (uint16_t)Car.transport;
}
uint16_t getCarscore()
{
		return (uint16_t)Car.score;
}
uint16_t getCartask()
{
    return (uint16_t)Car.task;
}
uint16_t getCararea()
{
		return (uint16_t)Car.area;
}
uint16_t getObstacleAposX(int ObstacleNo)		    //�����ϰ�Ax����
{	
	  return (uint16_t)Obstacle[ObstacleNo].posA.X;
}
uint16_t getObstacleAposY(int ObstacleNo)		    //�����ϰ�Ax����
{
    return (uint16_t)Obstacle[ObstacleNo].posA.Y;
}
uint16_t getObstacleBposX(int ObstacleNo)		    //�����ϰ�Ax����
{
    return (uint16_t)Obstacle[ObstacleNo].posB.X;
}
uint16_t getObstacleBposY(int ObstacleNo)	    //�����ϰ�Ax����
{
    return (uint16_t)Obstacle[ObstacleNo].posB.Y;
}
struct Position getObstacleApos(int ObstacleNo)
{
    return Obstacle[ObstacleNo].posA;
}
struct Position getObstacleBpos(int ObstacleNo)
{
    return Obstacle[ObstacleNo].posB;
}
/***************************************************/

void DecodeBasicInfo()
{
	Game.Time = (zigbeeReceive[0] << 8) + zigbeeReceive[1];
	Game.GameState = (zigbeeReceive[2] & 0xC0) >> 6;
	Game.stop=(zigbeeReceive[2]& 0x07);
}
void DecodeCarInfo()
{
    Car.pos.X=(zigbeeReceive[3]);
    Car.pos.Y=(zigbeeReceive[4]);
    Car.score=(zigbeeReceive[32]<<8)+zigbeeReceive[33];
    Car.picknum=zigbeeReceive[35];
    Car.task=((zigbeeReceive[2] & 0x20)>>5);
    Car.transport=((zigbeeReceive[2] & 0x08)>>3);
    Car.transportnum=(zigbeeReceive[34]);
    Car.area=((zigbeeReceive[19] & 0x02)>>1);
    Car.WhetherRightPos = (zigbeeReceive[19] & 0x01);
}

void DecodePassengerInfo()
{
    Passenger.startpos.X=(zigbeeReceive[15]);
    Passenger.startpos.Y=(zigbeeReceive[16]);
    Passenger.finalpos.X=(zigbeeReceive[17]);
    Passenger.finalpos.Y=(zigbeeReceive[18]);
}
void DecodePackageAInfo()
{
    Package[0].pos.X=(zigbeeReceive[20]);
    Package[0].pos.Y=(zigbeeReceive[21]);
    Package[0].whetherpicked=((zigbeeReceive[19] & 0x80)>>7);
}
void DecodePackageBInfo()
{
    Package[1].pos.X=(zigbeeReceive[22]);
    Package[1].pos.Y=(zigbeeReceive[23]);
    Package[1].whetherpicked=((zigbeeReceive[19] & 0x40)>>6);
}
void DecodePackageCInfo()
{
    Package[2].pos.X=(zigbeeReceive[24]);
    Package[2].pos.Y=(zigbeeReceive[25]);
    Package[2].whetherpicked=((zigbeeReceive[19] & 0x20)>>5);
}
void DecodePackageDInfo()
{
    Package[3].pos.X=(zigbeeReceive[26]);
    Package[3].pos.Y=(zigbeeReceive[27]);
    Package[3].whetherpicked=((zigbeeReceive[19] & 0x10)>>4);
}
void DecodePackageEInfo()
{
    Package[4].pos.X=(zigbeeReceive[28]);
    Package[4].pos.Y=(zigbeeReceive[29]);
    Package[4].whetherpicked=((zigbeeReceive[19] & 0x08)>>3);
}
void DecodePackageFInfo()
{
    Package[5].pos.X=(zigbeeReceive[30]);
    Package[5].pos.Y=(zigbeeReceive[31]);
    Package[5].whetherpicked=((zigbeeReceive[19] & 0x04)>>2);
}
void DecodeFloodInfo()
{
    Flood[0].pos.X=(zigbeeReceive[5]);
    Flood[0].pos.Y=(zigbeeReceive[6]);
	  Flood[1].pos.X=(zigbeeReceive[7]);
    Flood[1].pos.Y=(zigbeeReceive[8]);
    Flood[2].pos.X=(zigbeeReceive[9]);
    Flood[2].pos.Y=(zigbeeReceive[10]);
    Flood[3].pos.X=(zigbeeReceive[11]);
    Flood[3].pos.Y=(zigbeeReceive[12]);
    Flood[4].pos.X=(zigbeeReceive[13]);
    Flood[4].pos.Y=(zigbeeReceive[14]);
}
void DecodeObstacle()
{
    int i;
    for(i=0;i<8;i++)
    {
    	  Obstacle[i].posA.X=(zigbeeReceive[36+i*4]);
        Obstacle[i].posA.Y=(zigbeeReceive[37+i*4]);
        Obstacle[i].posB.X=(zigbeeReceive[38+i*4]);
        Obstacle[i].posB.Y=(zigbeeReceive[39+i*4]);
	  }


}
void Decode()
{
	DecodeBasicInfo();
	DecodeCarInfo();
	DecodePassengerInfo();
	DecodePackageAInfo();
	DecodePackageBInfo();
	DecodePackageCInfo();
	DecodePackageDInfo();
	DecodePackageEInfo();
	DecodePackageFInfo();
	DecodeFloodInfo();
	DecodeObstacle();
}
int receiveIndexMinus(int index_h, int num)
{
	if (index_h - num >= 0)
	{
		return index_h - num;
	}
	else
	{
		return index_h - num + ZIGBEE_MESSAGE_LENTH;
	}
}

int receiveIndexAdd(int index_h, int num)
{
	if (index_h + num < ZIGBEE_MESSAGE_LENTH)
	{
		return index_h + num;
	}
	else
	{
		return index_h + num - ZIGBEE_MESSAGE_LENTH;
	}
}

